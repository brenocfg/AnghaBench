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
struct TYPE_3__ {int pin_bit_mask; int pull_up_en; int pull_down_en; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_B1 ; 
 int /*<<< orphan*/  GPIO_B2 ; 
 int /*<<< orphan*/  GPIO_B3 ; 
 int /*<<< orphan*/  GPIO_INTR_DISABLE ; 
 int /*<<< orphan*/  GPIO_MODE_DEF_OUTPUT ; 
 int /*<<< orphan*/  SLAVE_PWR_GPIO ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void slave_power_on(void)
{
#ifdef SLAVE_PWR_GPIO
    int level_active;
#ifdef CONFIG_EXAMPLE_SLAVE_PWR_NEGTIVE_ACTIVE
    level_active = 0;
#else
    level_active = 1;
#endif
    gpio_config_t cfg = {
        .pin_bit_mask = BIT(GPIO_B1) | BIT(GPIO_B2) | BIT(GPIO_B3),
        .mode = GPIO_MODE_DEF_OUTPUT,
        .pull_up_en = false,
        .pull_down_en = false,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&cfg);
    gpio_set_level(GPIO_B1, !level_active);
    gpio_set_level(GPIO_B2, !level_active);
    gpio_set_level(GPIO_B3, !level_active);

    vTaskDelay(100);
    gpio_set_level(SLAVE_PWR_GPIO, level_active);
    vTaskDelay(100);

#endif
}