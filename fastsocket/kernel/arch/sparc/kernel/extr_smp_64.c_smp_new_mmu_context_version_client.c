#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct mm_struct {TYPE_2__ context; } ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_HWBITS (TYPE_2__) ; 
 int /*<<< orphan*/  CTX_VALID (TYPE_2__) ; 
 int /*<<< orphan*/  SECONDARY_CONTEXT ; 
 int /*<<< orphan*/  __flush_tlb_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_softint (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  load_secondary_context (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void smp_new_mmu_context_version_client(int irq, struct pt_regs *regs)
{
	struct mm_struct *mm;
	unsigned long flags;

	clear_softint(1 << irq);

	/* See if we need to allocate a new TLB context because
	 * the version of the one we are using is now out of date.
	 */
	mm = current->active_mm;
	if (unlikely(!mm || (mm == &init_mm)))
		return;

	spin_lock_irqsave(&mm->context.lock, flags);

	if (unlikely(!CTX_VALID(mm->context)))
		get_new_mmu_context(mm);

	spin_unlock_irqrestore(&mm->context.lock, flags);

	load_secondary_context(mm);
	__flush_tlb_mm(CTX_HWBITS(mm->context),
		       SECONDARY_CONTEXT);
}