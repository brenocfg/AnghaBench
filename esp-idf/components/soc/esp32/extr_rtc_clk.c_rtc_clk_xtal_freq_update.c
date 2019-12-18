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
typedef  int uint32_t ;
typedef  int rtc_xtal_freq_t ;

/* Variables and functions */
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int RTC_DISABLE_ROM_LOG ; 
 int /*<<< orphan*/  RTC_XTAL_FREQ_REG ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_val_to_reg_val (int) ; 

void rtc_clk_xtal_freq_update(rtc_xtal_freq_t xtal_freq)
{
    uint32_t reg = READ_PERI_REG(RTC_XTAL_FREQ_REG) & RTC_DISABLE_ROM_LOG;
    if (reg == RTC_DISABLE_ROM_LOG) {
        xtal_freq |= 1;
    }
    WRITE_PERI_REG(RTC_XTAL_FREQ_REG, clk_val_to_reg_val(xtal_freq));
}