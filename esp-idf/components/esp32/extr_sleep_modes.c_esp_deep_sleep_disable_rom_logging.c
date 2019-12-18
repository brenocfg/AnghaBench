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
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_STORE4_REG ; 
 int /*<<< orphan*/  RTC_DISABLE_ROM_LOG ; 

void esp_deep_sleep_disable_rom_logging(void)
{
    /* To disable logging in the ROM, only the least significant bit of the register is used,
     * but since this register is also used to store the frequency of the main crystal (RTC_XTAL_FREQ_REG),
     * you need to write to this register in the same format.
     * Namely, the upper 16 bits and lower should be the same.
     */
    REG_SET_BIT(RTC_CNTL_STORE4_REG, RTC_DISABLE_ROM_LOG);
}