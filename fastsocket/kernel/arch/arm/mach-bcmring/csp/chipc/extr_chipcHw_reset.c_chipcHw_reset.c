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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  SPIClock; int /*<<< orphan*/  UARTClock; } ;
typedef  int /*<<< orphan*/  (* RUNFUNC ) () ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_CACHE_FLUSH_ALL ; 
 int /*<<< orphan*/  INTCHW_INTC0 ; 
 int /*<<< orphan*/  INTCHW_INTC1 ; 
 int /*<<< orphan*/  INTCHW_SINTC ; 
 scalar_t__ MM_ADDR_IO_ARAM ; 
 scalar_t__ MM_IO_BASE_ARAM ; 
 int /*<<< orphan*/  REG_LOCAL_IRQ_RESTORE ; 
 int /*<<< orphan*/  REG_LOCAL_IRQ_SAVE ; 
 int /*<<< orphan*/  chipcHw_REG_PLL_CLOCK_BYPASS_SELECT ; 
 int chipcHw_REG_SOFT_RESET_CHIP_SOFT ; 
 int /*<<< orphan*/  chipcHw_reset_run_from_aram ; 
 int /*<<< orphan*/  chipcHw_softReset (int) ; 
 int /*<<< orphan*/  intcHw_irq_disable (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pChipcHw ; 

void chipcHw_reset(uint32_t mask)
{
	int i = 0;
	RUNFUNC runFunc = (RUNFUNC) (unsigned long)MM_ADDR_IO_ARAM;

	/* Disable all interrupts */
	intcHw_irq_disable(INTCHW_INTC0, 0xffffffff);
	intcHw_irq_disable(INTCHW_INTC1, 0xffffffff);
	intcHw_irq_disable(INTCHW_SINTC, 0xffffffff);

	{
		REG_LOCAL_IRQ_SAVE;
		if (mask & chipcHw_REG_SOFT_RESET_CHIP_SOFT) {
			chipcHw_softReset(chipcHw_REG_SOFT_RESET_CHIP_SOFT);
		}
		/* Bypass the PLL clocks before reboot */
		pChipcHw->UARTClock |= chipcHw_REG_PLL_CLOCK_BYPASS_SELECT;
		pChipcHw->SPIClock |= chipcHw_REG_PLL_CLOCK_BYPASS_SELECT;

		/* Copy the chipcHw_warmReset_run_from_aram function into ARAM */
		do {
			((uint32_t *) MM_IO_BASE_ARAM)[i] =
			    ((uint32_t *) &chipcHw_reset_run_from_aram)[i];
			i++;
		} while (((uint32_t *) MM_IO_BASE_ARAM)[i - 1] != 0xe1a0f00f);	/* 0xe1a0f00f == asm ("mov r15, r15"); */

		CSP_CACHE_FLUSH_ALL;

		/* run the function from ARAM */
		runFunc();

		/* Code will never get here, but include it to balance REG_LOCAL_IRQ_SAVE above */
		REG_LOCAL_IRQ_RESTORE;
	}
}