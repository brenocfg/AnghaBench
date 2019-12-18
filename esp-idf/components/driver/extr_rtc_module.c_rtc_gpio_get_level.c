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
typedef  int uint32_t ;
typedef  size_t gpio_num_t ;
struct TYPE_4__ {int in; } ;
struct TYPE_6__ {TYPE_1__ in_val; } ;
struct TYPE_5__ {int rtc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 TYPE_3__ RTCIO ; 
 int RTC_GPIO_IN_NEXT_S ; 
 int /*<<< orphan*/  RTC_GPIO_IN_REG ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_gpio_is_valid_gpio (size_t) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

uint32_t rtc_gpio_get_level(gpio_num_t gpio_num)
{
    uint32_t level = 0;
#if CONFIG_IDF_TARGET_ESP32
    int rtc_gpio_num = rtc_gpio_desc[gpio_num].rtc_num;
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);

    portENTER_CRITICAL(&rtc_spinlock);
    level = READ_PERI_REG(RTC_GPIO_IN_REG);
    portEXIT_CRITICAL(&rtc_spinlock);
    return ((level >> (RTC_GPIO_IN_NEXT_S + rtc_gpio_num)) & 0x01);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    RTC_MODULE_CHECK(rtc_gpio_is_valid_gpio(gpio_num), "RTC_GPIO number error", ESP_ERR_INVALID_ARG);
    portENTER_CRITICAL(&rtc_spinlock);
    level = RTCIO.in_val.in;
    portEXIT_CRITICAL(&rtc_spinlock);
    return ((level >> gpio_num) & 0x1);
#endif
}