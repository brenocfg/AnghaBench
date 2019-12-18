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

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTC_IO_TOUCH_PAD9_REG ; 
 int RTC_IO_TOUCH_PAD9_XPD_M ; 
 int RTC_IO_X32N_MUX_SEL ; 
 int RTC_IO_X32P_MUX_SEL ; 
 int RTC_IO_XPD_XTAL_32K_M ; 
 int /*<<< orphan*/  RTC_IO_XTAL_32K_PAD_REG ; 
 int /*<<< orphan*/  XTAL_32K_DAC_VAL ; 
 int /*<<< orphan*/  XTAL_32K_DBIAS_VAL ; 
 int /*<<< orphan*/  XTAL_32K_DRES_VAL ; 
 int /*<<< orphan*/  rtc_clk_32k_enable_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_clk_32k_enable(bool enable)
{
    if (enable) {
        rtc_clk_32k_enable_common(XTAL_32K_DAC_VAL, XTAL_32K_DRES_VAL, XTAL_32K_DBIAS_VAL);
    } else {
        /* Disable X32N and X32P pad drive external xtal */
        CLEAR_PERI_REG_MASK(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_XPD_XTAL_32K_M);
        CLEAR_PERI_REG_MASK(RTC_IO_XTAL_32K_PAD_REG, RTC_IO_X32N_MUX_SEL | RTC_IO_X32P_MUX_SEL);

#ifdef CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT
        /* Power down TOUCH */
        CLEAR_PERI_REG_MASK(RTC_IO_TOUCH_PAD9_REG, RTC_IO_TOUCH_PAD9_XPD_M);
#endif // CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_CURRENT
    }
}