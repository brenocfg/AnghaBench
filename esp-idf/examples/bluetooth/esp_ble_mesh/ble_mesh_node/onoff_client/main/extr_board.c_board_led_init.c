#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  previous; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  gpio_pad_select_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* led_state ; 

__attribute__((used)) static void board_led_init(void)
{
    for (int i = 0; i < ARRAY_SIZE(led_state); i++) {
        gpio_pad_select_gpio(led_state[i].pin);
        gpio_set_direction(led_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(led_state[i].pin, LED_OFF);
        led_state[i].previous = LED_OFF;
    }
}