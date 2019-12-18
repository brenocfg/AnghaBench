#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rtc_num; int /*<<< orphan*/  ie; int /*<<< orphan*/  reg; int /*<<< orphan*/  func; int /*<<< orphan*/  mux; } ;
typedef  TYPE_1__ rtc_gpio_desc_t ;
struct TYPE_5__ {int ext0_rtc_gpio_num; int /*<<< orphan*/  ext0_trigger_level; } ;

/* Variables and functions */
 size_t GPIO_PIN_COUNT ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_WAKEUP0_LV_S ; 
 int /*<<< orphan*/  RTC_CNTL_EXT_WAKEUP_CONF_REG ; 
 int /*<<< orphan*/  RTC_IO_EXT_WAKEUP0_REG ; 
 int /*<<< orphan*/  RTC_IO_EXT_WAKEUP0_SEL ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtc_gpio_desc ; 
 TYPE_2__ s_config ; 

__attribute__((used)) static void ext0_wakeup_prepare(void)
{
    int rtc_gpio_num = s_config.ext0_rtc_gpio_num;
    // Set GPIO to be used for wakeup
    REG_SET_FIELD(RTC_IO_EXT_WAKEUP0_REG, RTC_IO_EXT_WAKEUP0_SEL, rtc_gpio_num);
    // Set level which will trigger wakeup
    SET_PERI_REG_BITS(RTC_CNTL_EXT_WAKEUP_CONF_REG, 0x1,
            s_config.ext0_trigger_level, RTC_CNTL_EXT_WAKEUP0_LV_S);
    // Find GPIO descriptor in the rtc_gpio_desc table and configure the pad
    for (size_t gpio_num = 0; gpio_num < GPIO_PIN_COUNT; ++gpio_num) {
        const rtc_gpio_desc_t* desc = &rtc_gpio_desc[gpio_num];
        if (desc->rtc_num == rtc_gpio_num) {
            REG_SET_BIT(desc->reg, desc->mux);
            SET_PERI_REG_BITS(desc->reg, 0x3, 0, desc->func);
            REG_SET_BIT(desc->reg, desc->ie);
            break;
        }
    }
}