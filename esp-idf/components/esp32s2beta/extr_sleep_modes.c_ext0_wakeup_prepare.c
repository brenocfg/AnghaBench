#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mux_sel; int fun_ie; scalar_t__ fun_sel; } ;
struct TYPE_3__ {int ext0_rtc_gpio_num; int /*<<< orphan*/  ext0_trigger_level; } ;

/* Variables and functions */
 size_t GPIO_PIN_COUNT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_WAKEUP0_LV_S ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_WAKEUP_CONF_REG ; 
 scalar_t__ RTC_GPIO_IS_VALID_GPIO (size_t) ; 
 int /*<<< orphan*/  RTC_IO_EXT_WAKEUP0_REG ; 
 int /*<<< orphan*/  RTC_IO_EXT_WAKEUP0_SEL ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** rtc_gpio_reg ; 
 TYPE_1__ s_config ; 

__attribute__((used)) static void ext0_wakeup_prepare(void)
{
    int rtc_gpio_num = s_config.ext0_rtc_gpio_num;
    // Set GPIO to be used for wakeup
    REG_SET_FIELD(RTC_IO_EXT_WAKEUP0_REG, RTC_IO_EXT_WAKEUP0_SEL, rtc_gpio_num);
    // Set level which will trigger wakeup
    SET_PERI_REG_BITS(RTC_CNTL_EXT_WAKEUP_CONF_REG, 0x1,
            s_config.ext0_trigger_level, RTC_CNTL_EXT_WAKEUP0_LV_S);
    // Find GPIO descriptor in the rtc_gpio_reg table and configure the pad
    for (size_t gpio_num = 0; gpio_num < GPIO_PIN_COUNT; ++gpio_num) {
        if (gpio_num == rtc_gpio_num && RTC_GPIO_IS_VALID_GPIO(gpio_num)) {
            rtc_gpio_reg[gpio_num]->mux_sel = 1;
            rtc_gpio_reg[gpio_num]->fun_sel = 0;
            rtc_gpio_reg[gpio_num]->fun_ie = 1;
            break;
        }
    }
}