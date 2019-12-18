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
typedef  scalar_t__ uint32_t ;
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int rtc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int RTC_GPIO_OUT_DATA_W1TC_S ; 
 int RTC_GPIO_OUT_DATA_W1TS_S ; 
 int /*<<< orphan*/  RTC_GPIO_OUT_W1TC_REG ; 
 int /*<<< orphan*/  RTC_GPIO_OUT_W1TS_REG ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_gpio_is_valid_gpio (size_t) ; 
 int rtc_gpio_num ; 

esp_err_t rtc_gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
#if CONFIG_IDF_TARGET_ESP32
    int rtc_gpio_num = rtc_gpio_num = rtc_gpio_desc[gpio_num].rtc_num;;
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);

    if (level) {
        WRITE_PERI_REG(RTC_GPIO_OUT_W1TS_REG, (1 << (rtc_gpio_num + RTC_GPIO_OUT_DATA_W1TS_S)));
    } else {
        WRITE_PERI_REG(RTC_GPIO_OUT_W1TC_REG, (1 << (rtc_gpio_num + RTC_GPIO_OUT_DATA_W1TC_S)));
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);
    if (level) {
        WRITE_PERI_REG(RTC_GPIO_OUT_W1TS_REG, (1 << (gpio_num + RTC_GPIO_OUT_DATA_W1TS_S)));
    } else {
        WRITE_PERI_REG(RTC_GPIO_OUT_W1TC_REG, (1 << (gpio_num + RTC_GPIO_OUT_DATA_W1TC_S)));
    }
#endif
    return ESP_OK;
}