#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_1__* pin; } ;
struct TYPE_5__ {int rtc_num; } ;
struct TYPE_4__ {scalar_t__ int_type; scalar_t__ wakeup_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_CLR_BIT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ RTCIO ; 
 int /*<<< orphan*/  RTC_GPIO_PIN0_INT_TYPE ; 
 scalar_t__ RTC_GPIO_PIN0_REG ; 
 int /*<<< orphan*/  RTC_GPIO_PIN0_WAKEUP_ENABLE ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_gpio_is_valid_gpio (size_t) ; 

esp_err_t rtc_gpio_wakeup_disable(gpio_num_t gpio_num)
{
#if CONFIG_IDF_TARGET_ESP32
    int rtc_num = rtc_gpio_desc[gpio_num].rtc_num;
    if (rtc_num < 0) {
        return ESP_ERR_INVALID_ARG;
    }

    uint32_t reg = RTC_GPIO_PIN0_REG + rtc_num * sizeof(uint32_t);
    /* each pin has its own register, spinlock not needed */
    REG_CLR_BIT(reg, RTC_GPIO_PIN0_WAKEUP_ENABLE);
    REG_SET_FIELD(reg, RTC_GPIO_PIN0_INT_TYPE, 0);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);
    /* each pin has its own register, spinlock not needed */
    RTCIO.pin[gpio_num].wakeup_enable = 0;
    RTCIO.pin[gpio_num].int_type = 0;
#endif
    return ESP_OK;
}