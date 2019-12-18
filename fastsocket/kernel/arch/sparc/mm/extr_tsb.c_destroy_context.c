#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tsb_block; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned long CTX_NRBITS (TYPE_1__) ; 
 scalar_t__ CTX_VALID (TYPE_1__) ; 
 unsigned long MM_NUM_TSBS ; 
 int /*<<< orphan*/  ctx_alloc_lock ; 
 unsigned long* mmu_context_bmap ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tsb_destroy_one (int /*<<< orphan*/ *) ; 

void destroy_context(struct mm_struct *mm)
{
	unsigned long flags, i;

	for (i = 0; i < MM_NUM_TSBS; i++)
		tsb_destroy_one(&mm->context.tsb_block[i]);

	spin_lock_irqsave(&ctx_alloc_lock, flags);

	if (CTX_VALID(mm->context)) {
		unsigned long nr = CTX_NRBITS(mm->context);
		mmu_context_bmap[nr>>6] &= ~(1UL << (nr & 63));
	}

	spin_unlock_irqrestore(&ctx_alloc_lock, flags);
}