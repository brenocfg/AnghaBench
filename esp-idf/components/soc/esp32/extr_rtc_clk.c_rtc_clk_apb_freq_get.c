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

/* Variables and functions */
 int MHZ ; 
 int /*<<< orphan*/  READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_APB_FREQ_REG ; 
 int reg_val_to_clk_val (int /*<<< orphan*/ ) ; 

uint32_t rtc_clk_apb_freq_get(void)
{
    uint32_t freq_hz = reg_val_to_clk_val(READ_PERI_REG(RTC_APB_FREQ_REG)) << 12;
    // round to the nearest MHz
    freq_hz += MHZ / 2;
    uint32_t remainder = freq_hz % MHZ;
    return freq_hz - remainder;
}