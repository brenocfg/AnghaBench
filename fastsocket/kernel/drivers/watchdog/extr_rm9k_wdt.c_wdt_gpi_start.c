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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CPGIG1ER ; 
 int /*<<< orphan*/  iob () ; 
 int /*<<< orphan*/  lock_titan_regs () ; 
 int titan_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  titan_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_titan_regs () ; 
 int wd_ctr ; 

__attribute__((used)) static void wdt_gpi_start(void)
{
	u32 reg;

	lock_titan_regs();
	reg = titan_readl(CPGIG1ER);
	titan_writel(reg | (0x100 << wd_ctr), CPGIG1ER);
	iob();
	unlock_titan_regs();
}