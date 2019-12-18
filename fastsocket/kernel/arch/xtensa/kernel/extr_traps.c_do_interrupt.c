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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCLEAR ; 
 int /*<<< orphan*/  INTENABLE ; 
 int /*<<< orphan*/  INTREAD ; 
 int XCHAL_NUM_INTERRUPTS ; 
 int /*<<< orphan*/  do_IRQ (int,struct pt_regs*) ; 
 unsigned long get_sr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sr (int,int /*<<< orphan*/ ) ; 

void do_interrupt (struct pt_regs *regs)
{
	unsigned long intread = get_sr (INTREAD);
	unsigned long intenable = get_sr (INTENABLE);
	int i, mask;

	/* Handle all interrupts (no priorities).
	 * (Clear the interrupt before processing, in case it's
	 *  edge-triggered or software-generated)
	 */

	for (i=0, mask = 1; i < XCHAL_NUM_INTERRUPTS; i++, mask <<= 1) {
		if (mask & (intread & intenable)) {
			set_sr (mask, INTCLEAR);
			do_IRQ (i,regs);
		}
	}
}