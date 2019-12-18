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
typedef  int u64 ;
typedef  int u32 ;
struct pt_regs {int dummy; } ;
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int CBE_PM_CTR_OVERFLOW_INTR (int /*<<< orphan*/ ) ; 
 int CBE_PM_TRACE_BUF_EMPTY ; 
 int /*<<< orphan*/  NUM_INTERVAL_CYC ; 
 int NUM_SPUS_PER_NODE ; 
 int cbe_cpu_to_node (int) ; 
 int /*<<< orphan*/  cbe_disable_pm (int) ; 
 int /*<<< orphan*/  cbe_enable_pm (int) ; 
 int /*<<< orphan*/  cbe_enable_pm_interrupts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cbe_get_and_clear_pm_interrupts (int) ; 
 int cbe_read_pm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbe_read_trace_buffer (int,int*) ; 
 int /*<<< orphan*/  cbe_write_ctr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbe_write_pm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cntr_lock ; 
 int /*<<< orphan*/  hdw_thread ; 
 int /*<<< orphan*/  oprof_spu_smpl_arry_lck ; 
 int oprofile_running ; 
 int /*<<< orphan*/  pm_interval ; 
 int /*<<< orphan*/ * reset_value ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int spu_evnt_phys_spu_indx ; 
 int /*<<< orphan*/  spu_sync_buffer (int,int*,int) ; 
 int /*<<< orphan*/  trace_address ; 
 int /*<<< orphan*/  virt_cntr_inter_mask ; 
 int /*<<< orphan*/  write_pm_cntrl (int) ; 

__attribute__((used)) static void cell_handle_interrupt_spu(struct pt_regs *regs,
				      struct op_counter_config *ctr)
{
	u32 cpu, cpu_tmp;
	u64 trace_entry;
	u32 interrupt_mask;
	u64 trace_buffer[2];
	u64 last_trace_buffer;
	u32 sample;
	u32 trace_addr;
	unsigned long sample_array_lock_flags;
	int spu_num;
	unsigned long flags;

	/* Make sure spu event interrupt handler and spu event swap
	 * don't access the counters simultaneously.
	 */
	cpu = smp_processor_id();
	spin_lock_irqsave(&cntr_lock, flags);

	cpu_tmp = cpu;
	cbe_disable_pm(cpu);

	interrupt_mask = cbe_get_and_clear_pm_interrupts(cpu);

	sample = 0xABCDEF;
	trace_entry = 0xfedcba;
	last_trace_buffer = 0xdeadbeaf;

	if ((oprofile_running == 1) && (interrupt_mask != 0)) {
		/* disable writes to trace buff */
		cbe_write_pm(cpu, pm_interval, 0);

		/* only have one perf cntr being used, cntr 0 */
		if ((interrupt_mask & CBE_PM_CTR_OVERFLOW_INTR(0))
		    && ctr[0].enabled)
			/* The SPU PC values will be read
			 * from the trace buffer, reset counter
			 */

			cbe_write_ctr(cpu, 0, reset_value[0]);

		trace_addr = cbe_read_pm(cpu, trace_address);

		while (!(trace_addr & CBE_PM_TRACE_BUF_EMPTY)) {
			/* There is data in the trace buffer to process
			 * Read the buffer until you get to the last
			 * entry.  This is the value we want.
			 */

			cbe_read_trace_buffer(cpu, trace_buffer);
			trace_addr = cbe_read_pm(cpu, trace_address);
		}

		/* SPU Address 16 bit count format for 128 bit
		 * HW trace buffer is used for the SPU PC storage
		 *    HDR bits          0:15
		 *    SPU Addr 0 bits   16:31
		 *    SPU Addr 1 bits   32:47
		 *    unused bits       48:127
		 *
		 * HDR: bit4 = 1 SPU Address 0 valid
		 * HDR: bit5 = 1 SPU Address 1 valid
		 *  - unfortunately, the valid bits don't seem to work
		 *
		 * Note trace_buffer[0] holds bits 0:63 of the HW
		 * trace buffer, trace_buffer[1] holds bits 64:127
		 */

		trace_entry = trace_buffer[0]
			& 0x00000000FFFF0000;

		/* only top 16 of the 18 bit SPU PC address
		 * is stored in trace buffer, hence shift right
		 * by 16 -2 bits */
		sample = trace_entry >> 14;
		last_trace_buffer = trace_buffer[0];

		spu_num = spu_evnt_phys_spu_indx
			+ (cbe_cpu_to_node(cpu) * NUM_SPUS_PER_NODE);

		/* make sure only one process at a time is calling
		 * spu_sync_buffer()
		 */
		spin_lock_irqsave(&oprof_spu_smpl_arry_lck,
				  sample_array_lock_flags);
		spu_sync_buffer(spu_num, &sample, 1);
		spin_unlock_irqrestore(&oprof_spu_smpl_arry_lck,
				       sample_array_lock_flags);

		smp_wmb();    /* insure spu event buffer updates are written
			       * don't want events intermingled... */

		/* The counters were frozen by the interrupt.
		 * Reenable the interrupt and restart the counters.
		 */
		cbe_write_pm(cpu, pm_interval, NUM_INTERVAL_CYC);
		cbe_enable_pm_interrupts(cpu, hdw_thread,
					 virt_cntr_inter_mask);

		/* clear the trace buffer, re-enable writes to trace buff */
		cbe_write_pm(cpu, trace_address, 0);
		cbe_write_pm(cpu, pm_interval, NUM_INTERVAL_CYC);

		/* The writes to the various performance counters only writes
		 * to a latch.  The new values (interrupt setting bits, reset
		 * counter value etc.) are not copied to the actual registers
		 * until the performance monitor is enabled.  In order to get
		 * this to work as desired, the permormance monitor needs to
		 * be disabled while writing to the latches.  This is a
		 * HW design issue.
		 */
		write_pm_cntrl(cpu);
		cbe_enable_pm(cpu);
	}
	spin_unlock_irqrestore(&cntr_lock, flags);
}