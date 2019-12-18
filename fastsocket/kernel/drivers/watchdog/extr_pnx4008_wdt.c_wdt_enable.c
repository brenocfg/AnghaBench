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
 int COUNT_ENAB ; 
 int DEBUG_EN ; 
 int MATCH_INT ; 
 int MATCH_OUTPUT_HIGH ; 
 int M_RES2 ; 
 int RESET_COUNT ; 
 int RESET_COUNT0 ; 
 int STOP_COUNT0 ; 
 int WDOG_COUNTER_RATE ; 
 int /*<<< orphan*/  WDTIM_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_EMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_MATCH0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_MCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_PULSE (int /*<<< orphan*/ ) ; 
 scalar_t__ __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (scalar_t__,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int heartbeat ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_base ; 
 scalar_t__ wdt_clk ; 

__attribute__((used)) static void wdt_enable(void)
{
	spin_lock(&io_lock);

	if (wdt_clk)
		clk_set_rate(wdt_clk, 1);

	/* stop counter, initiate counter reset */
	__raw_writel(RESET_COUNT, WDTIM_CTRL(wdt_base));
	/*wait for reset to complete. 100% guarantee event */
	while (__raw_readl(WDTIM_COUNTER(wdt_base)))
		cpu_relax();
	/* internal and external reset, stop after that */
	__raw_writel(M_RES2 | STOP_COUNT0 | RESET_COUNT0,
		WDTIM_MCTRL(wdt_base));
	/* configure match output */
	__raw_writel(MATCH_OUTPUT_HIGH, WDTIM_EMR(wdt_base));
	/* clear interrupt, just in case */
	__raw_writel(MATCH_INT, WDTIM_INT(wdt_base));
	/* the longest pulse period 65541/(13*10^6) seconds ~ 5 ms. */
	__raw_writel(0xFFFF, WDTIM_PULSE(wdt_base));
	__raw_writel(heartbeat * WDOG_COUNTER_RATE, WDTIM_MATCH0(wdt_base));
	/*enable counter, stop when debugger active */
	__raw_writel(COUNT_ENAB | DEBUG_EN, WDTIM_CTRL(wdt_base));

	spin_unlock(&io_lock);
}