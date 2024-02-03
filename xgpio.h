#ifndef __xgpio_h__
#define __xgpio_h__

#include <xdts.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_DT_SPEC_FOR(_node_label, _idx) GPIO_DT_SPEC_GET_BY_IDX(L(_node_label), gpios, _idx)

#define DEFINE_GPIO_EXTERN(_name) \
    extern const struct gpio_dt_spec _name

#define DEFINE_GPIO_AS(_node_label, _name) \
    const struct gpio_dt_spec _name = GPIO_DT_SPEC_FOR(_node_label, 0)

#define DEFINE_GPIO(_node_label) DEFINE_GPIO_AS(_node_label, _node_label)

#define PIN(x) gpio_pin_get_dt(x)
#define DEFINE_GPIO_CALLBACK(dt_io) struct gpio_callback dt_io##_cb

#define gpio_catch(dt_io, mode, handler)                          \
    {                                                             \
        gpio_pin_interrupt_configure_dt(&dt_io, mode);            \
        gpio_init_callback(&dt_io##_cb, handler, BIT(dt_io.pin)); \
        gpio_add_callback(dt_io.port, &dt_io##_cb);               \
    }

#define DEFINE_PWM(_pwm) const pwm_t _pwm = PWM_DT_SPEC_GET(L(_pwm))

typedef struct
{
    struct gpio_callback gpio_cb;
    void *data;
} gpio_user_callback_t;

#endif