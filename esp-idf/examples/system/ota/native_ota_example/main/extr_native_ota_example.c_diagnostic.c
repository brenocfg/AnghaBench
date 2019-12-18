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
struct TYPE_3__ {unsigned long long pin_bit_mask; int /*<<< orphan*/  pull_up_en; int /*<<< orphan*/  pull_down_en; int /*<<< orphan*/  mode; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 unsigned long long CONFIG_EXAMPLE_GPIO_DIAGNOSTIC ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT ; 
 int /*<<< orphan*/  GPIO_PIN_INTR_DISABLE ; 
 int /*<<< orphan*/  GPIO_PULLDOWN_DISABLE ; 
 int /*<<< orphan*/  GPIO_PULLUP_ENABLE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int gpio_get_level (unsigned long long) ; 
 int /*<<< orphan*/  gpio_reset_pin (unsigned long long) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static bool diagnostic(void)
{
    gpio_config_t io_conf;
    io_conf.intr_type    = GPIO_PIN_INTR_DISABLE;
    io_conf.mode         = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << CONFIG_EXAMPLE_GPIO_DIAGNOSTIC);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en   = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "Diagnostics (5 sec)...");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    bool diagnostic_is_ok = gpio_get_level(CONFIG_EXAMPLE_GPIO_DIAGNOSTIC);

    gpio_reset_pin(CONFIG_EXAMPLE_GPIO_DIAGNOSTIC);
    return diagnostic_is_ok;
}