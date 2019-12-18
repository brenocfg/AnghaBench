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
struct TYPE_3__ {int pin_bit_mask; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int BIT (int const) ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT_OD ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_set_level (int const,int) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void reset_slave(void)
{
    const int pin_en = 18;
    const int pin_io0 = 19;
    gpio_config_t gpio_cfg = {
            .pin_bit_mask = BIT(pin_en) | BIT(pin_io0),
            .mode = GPIO_MODE_OUTPUT_OD,
    };
    TEST_ESP_OK(gpio_config(&gpio_cfg));
    gpio_set_level(pin_en, 0);
    gpio_set_level(pin_io0, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(pin_en, 1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(pin_io0, 1);
}