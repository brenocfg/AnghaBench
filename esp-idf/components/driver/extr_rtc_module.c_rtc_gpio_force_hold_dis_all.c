#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ hold_force; } ;
typedef  TYPE_2__ rtc_gpio_desc_t ;
struct TYPE_5__ {scalar_t__ rtc_pad_force_hold; } ;
struct TYPE_7__ {TYPE_1__ rtc_pwc; } ;

/* Variables and functions */
 int GPIO_PIN_COUNT ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_CNTL_HOLD_FORCE_REG ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__* rtc_gpio_desc ; 
 int /*<<< orphan*/  rtc_spinlock ; 

void rtc_gpio_force_hold_dis_all(void)
{
#if CONFIG_IDF_TARGET_ESP32
    for (int gpio = 0; gpio < GPIO_PIN_COUNT; ++gpio) {
        const rtc_gpio_desc_t* desc = &rtc_gpio_desc[gpio];
        if (desc->hold_force != 0) {
            REG_CLR_BIT(RTC_CNTL_HOLD_FORCE_REG, desc->hold_force);
        }
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    portENTER_CRITICAL(&rtc_spinlock);
    RTCCNTL.rtc_pwc.rtc_pad_force_hold = 0;
    portEXIT_CRITICAL(&rtc_spinlock);
#endif
}