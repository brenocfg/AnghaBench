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
union smp_flush_state {scalar_t__ flush_mm; scalar_t__ flush_va; int /*<<< orphan*/  flush_cpumask; } ;
struct pt_regs {unsigned int orig_ax; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  active_mm; } ;
struct TYPE_3__ {scalar_t__ active_mm; } ;

/* Variables and functions */
 unsigned int INVALIDATE_TLB_VECTOR_START ; 
 scalar_t__ TLBSTATE_OK ; 
 scalar_t__ TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  __flush_tlb_one (scalar_t__) ; 
 int /*<<< orphan*/  ack_APIC_irq () ; 
 TYPE_2__ cpu_tlbstate ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 union smp_flush_state* flush_state ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_tlb_count ; 
 int /*<<< orphan*/  leave_mm (unsigned int) ; 
 int /*<<< orphan*/  load_user_cs_desc (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  local_flush_tlb () ; 
 scalar_t__ percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

void smp_invalidate_interrupt(struct pt_regs *regs)
{
	unsigned int cpu;
	unsigned int sender;
	union smp_flush_state *f;

	cpu = smp_processor_id();

#ifdef CONFIG_X86_32
	if (current->active_mm)
		load_user_cs_desc(cpu, current->active_mm);
#endif

	/*
	 * orig_rax contains the negated interrupt vector.
	 * Use that to determine where the sender put the data.
	 */
	sender = ~regs->orig_ax - INVALIDATE_TLB_VECTOR_START;
	f = &flush_state[sender];

	if (!cpumask_test_cpu(cpu, to_cpumask(f->flush_cpumask)))
		goto out;
		/*
		 * This was a BUG() but until someone can quote me the
		 * line from the intel manual that guarantees an IPI to
		 * multiple CPUs is retried _only_ on the erroring CPUs
		 * its staying as a return
		 *
		 * BUG();
		 */

	if (f->flush_mm == percpu_read(cpu_tlbstate.active_mm)) {
		if (percpu_read(cpu_tlbstate.state) == TLBSTATE_OK) {
			if (f->flush_va == TLB_FLUSH_ALL)
				local_flush_tlb();
			else
				__flush_tlb_one(f->flush_va);
		} else
			leave_mm(cpu);
	}
out:
	ack_APIC_irq();
	smp_mb__before_clear_bit();
	cpumask_clear_cpu(cpu, to_cpumask(f->flush_cpumask));
	smp_mb__after_clear_bit();
	inc_irq_stat(irq_tlb_count);
}