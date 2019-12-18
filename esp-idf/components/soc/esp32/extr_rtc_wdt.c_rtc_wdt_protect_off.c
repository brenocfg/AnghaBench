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
 int /*<<< orphan*/  RTC_CNTL_WDTWPROTECT_REG ; 
 int /*<<< orphan*/  RTC_CNTL_WDT_WKEY_VALUE ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_wdt_protect_off(void)
{
    WRITE_PERI_REG(RTC_CNTL_WDTWPROTECT_REG, RTC_CNTL_WDT_WKEY_VALUE);
}