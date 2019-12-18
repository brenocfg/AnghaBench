#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ wdog_used; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_WDOG_CRTL ; 
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int /*<<< orphan*/  TIM_START ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smt_start_watchdog(struct s_smc *smc)
{
	SK_UNUSED(smc) ;	/* Make LINT happy. */

#ifndef	DEBUG

#ifdef	PCI
	if (smc->hw.wdog_used) {
		outpw(ADDR(B2_WDOG_CRTL),TIM_START) ;	/* Start timer. */
	}
#endif

#endif	/* DEBUG */
}