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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_RTC_CTRL_WATCHDOGEN ; 
 int /*<<< orphan*/  BV_RTC_PERSISTENT1_GENERAL__RTC_FORCE_UPDATER ; 
 scalar_t__ HW_RTC_CTRL ; 
 scalar_t__ HW_RTC_PERSISTENT1 ; 
 scalar_t__ HW_RTC_WATCHDOG ; 
 scalar_t__ REGS_RTC_BASE ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmp3xxx_setl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stmp3xxx_wdt_io_lock ; 

__attribute__((used)) static void wdt_enable(u32 value)
{
	spin_lock(&stmp3xxx_wdt_io_lock);
	__raw_writel(value, REGS_RTC_BASE + HW_RTC_WATCHDOG);
	stmp3xxx_setl(BM_RTC_CTRL_WATCHDOGEN, REGS_RTC_BASE + HW_RTC_CTRL);
	stmp3xxx_setl(BV_RTC_PERSISTENT1_GENERAL__RTC_FORCE_UPDATER,
			REGS_RTC_BASE + HW_RTC_PERSISTENT1);
	spin_unlock(&stmp3xxx_wdt_io_lock);
}