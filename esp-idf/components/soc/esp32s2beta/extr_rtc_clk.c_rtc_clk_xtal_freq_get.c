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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rtc_xtal_freq_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_XTAL_FREQ_AUTO ; 
 int /*<<< orphan*/  RTC_XTAL_FREQ_REG ; 
 int /*<<< orphan*/  SOC_LOGW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  clk_val_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_val_to_clk_val (int /*<<< orphan*/ ) ; 

rtc_xtal_freq_t rtc_clk_xtal_freq_get(void)
{
    /* We may have already written XTAL value into RTC_XTAL_FREQ_REG */
    uint32_t xtal_freq_reg = READ_PERI_REG(RTC_XTAL_FREQ_REG);
    if (!clk_val_is_valid(xtal_freq_reg)) {
        SOC_LOGW(TAG, "invalid RTC_XTAL_FREQ_REG value: 0x%08x", xtal_freq_reg);
        return RTC_XTAL_FREQ_AUTO;
    }
    return reg_val_to_clk_val(xtal_freq_reg);
}