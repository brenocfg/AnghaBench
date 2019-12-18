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
typedef  int rtc_gpio_mode_t ;
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
#define  RTC_GPIO_MODE_DISABLED 131 
#define  RTC_GPIO_MODE_INPUT_ONLY 130 
#define  RTC_GPIO_MODE_INPUT_OUTPUT 129 
#define  RTC_GPIO_MODE_OUTPUT_ONLY 128 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_input_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_input_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_is_valid_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_output_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_output_enable (int /*<<< orphan*/ ) ; 

esp_err_t rtc_gpio_set_direction(gpio_num_t gpio_num, rtc_gpio_mode_t mode)
{
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);

    switch (mode) {
    case RTC_GPIO_MODE_INPUT_ONLY:
        rtc_gpio_output_disable(gpio_num);
        rtc_gpio_input_enable(gpio_num);
        break;
    case RTC_GPIO_MODE_OUTPUT_ONLY:
        rtc_gpio_output_enable(gpio_num);
        rtc_gpio_input_disable(gpio_num);
        break;
    case RTC_GPIO_MODE_INPUT_OUTPUT:
        rtc_gpio_output_enable(gpio_num);
        rtc_gpio_input_enable(gpio_num);
        break;
    case RTC_GPIO_MODE_DISABLED:
        rtc_gpio_output_disable(gpio_num);
        rtc_gpio_input_disable(gpio_num);
        break;
    }

    return ESP_OK;
}