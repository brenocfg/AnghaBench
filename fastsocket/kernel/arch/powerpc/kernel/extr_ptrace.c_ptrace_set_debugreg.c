#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long dabr; int dbcr0; TYPE_1__* regs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 unsigned long DABR_TRANSLATION ; 
 int DBCR0_IDM ; 
 int DBSR_DAC1R ; 
 int DBSR_DAC1W ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  MSR_DE ; 
 unsigned long TASK_SIZE ; 

int ptrace_set_debugreg(struct task_struct *task, unsigned long addr,
			       unsigned long data)
{
	/* For ppc64 we support one DABR and no IABR's at the moment (ppc64).
	 *  For embedded processors we support one DAC and no IAC's at the
	 *  moment.
	 */
	if (addr > 0)
		return -EINVAL;

	/* The bottom 3 bits in dabr are flags */
	if ((data & ~0x7UL) >= TASK_SIZE)
		return -EIO;

#ifndef CONFIG_BOOKE

	/* For processors using DABR (i.e. 970), the bottom 3 bits are flags.
	 *  It was assumed, on previous implementations, that 3 bits were
	 *  passed together with the data address, fitting the design of the
	 *  DABR register, as follows:
	 *
	 *  bit 0: Read flag
	 *  bit 1: Write flag
	 *  bit 2: Breakpoint translation
	 *
	 *  Thus, we use them here as so.
	 */

	/* Ensure breakpoint translation bit is set */
	if (data && !(data & DABR_TRANSLATION))
		return -EIO;

	/* Move contents to the DABR register */
	task->thread.dabr = data;

#endif
#if defined(CONFIG_BOOKE)

	/* As described above, it was assumed 3 bits were passed with the data
	 *  address, but we will assume only the mode bits will be passed
	 *  as to not cause alignment restrictions for DAC-based processors.
	 */

	/* DAC's hold the whole address without any mode flags */
	task->thread.dabr = data & ~0x3UL;

	if (task->thread.dabr == 0) {
		task->thread.dbcr0 &= ~(DBSR_DAC1R | DBSR_DAC1W | DBCR0_IDM);
		task->thread.regs->msr &= ~MSR_DE;
		return 0;
	}

	/* Read or Write bits must be set */

	if (!(data & 0x3UL))
		return -EINVAL;

	/* Set the Internal Debugging flag (IDM bit 1) for the DBCR0
	   register */
	task->thread.dbcr0 = DBCR0_IDM;

	/* Check for write and read flags and set DBCR0
	   accordingly */
	if (data & 0x1UL)
		task->thread.dbcr0 |= DBSR_DAC1R;
	if (data & 0x2UL)
		task->thread.dbcr0 |= DBSR_DAC1W;

	task->thread.regs->msr |= MSR_DE;
#endif
	return 0;
}