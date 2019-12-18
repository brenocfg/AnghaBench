#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_GPIO_MODE_DISABLED ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_gpio_hold_en (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_is_valid_gpio (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_dis (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_pullup_dis (size_t) ; 
 int /*<<< orphan*/  rtc_gpio_set_direction (size_t,int /*<<< orphan*/ ) ; 

esp_err_t rtc_gpio_isolate(gpio_num_t gpio_num)
{
#if CONFIG_IDF_TARGET_ESP32
    if (rtc_gpio_desc[gpio_num].reg == 0) {
        return ESP_ERR_INVALID_ARG;
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);
#endif
    rtc_gpio_pullup_dis(gpio_num);
    rtc_gpio_pulldown_dis(gpio_num);
    rtc_gpio_set_direction(gpio_num, RTC_GPIO_MODE_DISABLED);
    rtc_gpio_hold_en(gpio_num);

    return ESP_OK;
}