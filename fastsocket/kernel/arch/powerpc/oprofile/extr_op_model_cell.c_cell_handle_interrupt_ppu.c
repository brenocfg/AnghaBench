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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct pt_regs {int /*<<< orphan*/  nip; } ;
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int CBE_PM_CTR_OVERFLOW_INTR (int) ; 
 int /*<<< orphan*/  cbe_disable_pm (int) ; 
 int /*<<< orphan*/  cbe_enable_pm (int) ; 
 int /*<<< orphan*/  cbe_enable_pm_interrupts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cbe_get_and_clear_pm_interrupts (int) ; 
 int /*<<< orphan*/  cbe_write_ctr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cntr_lock ; 
 int /*<<< orphan*/  hdw_thread ; 
 int is_kernel_addr (int /*<<< orphan*/ ) ; 
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_ext_sample (int /*<<< orphan*/ ,struct pt_regs*,int,int) ; 
 int oprofile_running ; 
 int /*<<< orphan*/ * reset_value ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_cntr_inter_mask ; 

__attribute__((used)) static void cell_handle_interrupt_ppu(struct pt_regs *regs,
				      struct op_counter_config *ctr)
{
	u32 cpu;
	u64 pc;
	int is_kernel;
	unsigned long flags = 0;
	u32 interrupt_mask;
	int i;

	cpu = smp_processor_id();

	/*
	 * Need to make sure the interrupt handler and the virt counter
	 * routine are not running at the same time. See the
	 * cell_virtual_cntr() routine for additional comments.
	 */
	spin_lock_irqsave(&cntr_lock, flags);

	/*
	 * Need to disable and reenable the performance counters
	 * to get the desired behavior from the hardware.  This
	 * is hardware specific.
	 */

	cbe_disable_pm(cpu);

	interrupt_mask = cbe_get_and_clear_pm_interrupts(cpu);

	/*
	 * If the interrupt mask has been cleared, then the virt cntr
	 * has cleared the interrupt.  When the thread that generated
	 * the interrupt is restored, the data count will be restored to
	 * 0xffffff0 to cause the interrupt to be regenerated.
	 */

	if ((oprofile_running == 1) && (interrupt_mask != 0)) {
		pc = regs->nip;
		is_kernel = is_kernel_addr(pc);

		for (i = 0; i < num_counters; ++i) {
			if ((interrupt_mask & CBE_PM_CTR_OVERFLOW_INTR(i))
			    && ctr[i].enabled) {
				oprofile_add_ext_sample(pc, regs, i, is_kernel);
				cbe_write_ctr(cpu, i, reset_value[i]);
			}
		}

		/*
		 * The counters were frozen by the interrupt.
		 * Reenable the interrupt and restart the counters.
		 * If there was a race between the interrupt handler and
		 * the virtual counter routine.	 The virutal counter
		 * routine may have cleared the interrupts.  Hence must
		 * use the virt_cntr_inter_mask to re-enable the interrupts.
		 */
		cbe_enable_pm_interrupts(cpu, hdw_thread,
					 virt_cntr_inter_mask);

		/*
		 * The writes to the various performance counters only writes
		 * to a latch.	The new values (interrupt setting bits, reset
		 * counter value etc.) are not copied to the actual registers
		 * until the performance monitor is enabled.  In order to get
		 * this to work as desired, the permormance monitor needs to
		 * be disabled while writing to the latches.  This is a
		 * HW design issue.
		 */
		cbe_enable_pm(cpu);
	}
	spin_unlock_irqrestore(&cntr_lock, flags);
}