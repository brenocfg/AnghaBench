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
struct tsb_config {int /*<<< orphan*/ * tsb; } ;
struct TYPE_2__ {unsigned long sparc64_ctx_val; struct tsb_config* tsb_block; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned long CTX_PGSZ0_SHIFT ; 
 unsigned long CTX_PGSZ1_SHIFT ; 
 unsigned long CTX_PGSZ_BASE ; 
 unsigned long CTX_PGSZ_HUGE ; 
 unsigned long CTX_PGSZ_MASK ; 
 size_t MM_TSB_HUGE ; 
 scalar_t__ cheetah_plus ; 
 int /*<<< orphan*/  context_reload ; 
 int /*<<< orphan*/  ctx_alloc_lock ; 
 int /*<<< orphan*/  do_flush_tlb_mm (struct mm_struct*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_tsb_sync (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tlb_type ; 
 int /*<<< orphan*/  tsb_context_switch (struct mm_struct*) ; 
 int /*<<< orphan*/  tsb_grow (struct mm_struct*,size_t,int /*<<< orphan*/ ) ; 

void hugetlb_prefault_arch_hook(struct mm_struct *mm)
{
	struct tsb_config *tp = &mm->context.tsb_block[MM_TSB_HUGE];

	if (likely(tp->tsb != NULL))
		return;

	tsb_grow(mm, MM_TSB_HUGE, 0);
	tsb_context_switch(mm);
	smp_tsb_sync(mm);

	/* On UltraSPARC-III+ and later, configure the second half of
	 * the Data-TLB for huge pages.
	 */
	if (tlb_type == cheetah_plus) {
		unsigned long ctx;

		spin_lock(&ctx_alloc_lock);
		ctx = mm->context.sparc64_ctx_val;
		ctx &= ~CTX_PGSZ_MASK;
		ctx |= CTX_PGSZ_BASE << CTX_PGSZ0_SHIFT;
		ctx |= CTX_PGSZ_HUGE << CTX_PGSZ1_SHIFT;

		if (ctx != mm->context.sparc64_ctx_val) {
			/* When changing the page size fields, we
			 * must perform a context flush so that no
			 * stale entries match.  This flush must
			 * occur with the original context register
			 * settings.
			 */
			do_flush_tlb_mm(mm);

			/* Reload the context register of all processors
			 * also executing in this address space.
			 */
			mm->context.sparc64_ctx_val = ctx;
			on_each_cpu(context_reload, mm, 0);
		}
		spin_unlock(&ctx_alloc_lock);
	}
}