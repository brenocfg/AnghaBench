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
typedef  scalar_t__ touch_pad_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_GPIO_MODE_DISABLED ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TOUCH_DENOISE_CHANNEL ; 
 int /*<<< orphan*/  rtc_gpio_init (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_pulldown_dis (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_pullup_dis (scalar_t__) ; 
 int /*<<< orphan*/  rtc_gpio_set_direction (scalar_t__,int /*<<< orphan*/ ) ; 

esp_err_t touch_pad_io_init(touch_pad_t touch_num)
{
    RTC_MODULE_CHECK(touch_num != TOUCH_DENOISE_CHANNEL,
                    "please use `touch_pad_denoise_enable` to set denoise channel", ESP_ERR_INVALID_ARG);
    rtc_gpio_init(touch_num);
    rtc_gpio_set_direction(touch_num, RTC_GPIO_MODE_DISABLED);
    rtc_gpio_pulldown_dis(touch_num);
    rtc_gpio_pullup_dis(touch_num);
    return ESP_OK;
}