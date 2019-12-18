#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  FUN_PD ; 
 int /*<<< orphan*/  GPIO_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_IS_VALID_GPIO (size_t) ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RTC_GPIO_IS_VALID_GPIO (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_en (size_t) ; 

esp_err_t gpio_pulldown_en(gpio_num_t gpio_num)
{
    GPIO_CHECK(GPIO_IS_VALID_GPIO(gpio_num), "GPIO number error", ESP_ERR_INVALID_ARG);
#if CONFIG_IDF_TARGET_ESP32
    if (RTC_GPIO_IS_VALID_GPIO(gpio_num)) {
        rtc_gpio_pulldown_en(gpio_num);
    } else {
        REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PD);
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PD);
#endif
    return ESP_OK;
}