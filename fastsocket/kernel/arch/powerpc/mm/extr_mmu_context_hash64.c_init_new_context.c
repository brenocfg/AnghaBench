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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_CONTEXT ; 
 int idr_get_new_above (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmu_context_idr ; 
 int /*<<< orphan*/  mmu_context_lock ; 
 int /*<<< orphan*/  mmu_virtual_psize ; 
 scalar_t__ slice_mm_new_context (struct mm_struct*) ; 
 int /*<<< orphan*/  slice_set_user_psize (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	int index;
	int err;

again:
	if (!idr_pre_get(&mmu_context_idr, GFP_KERNEL))
		return -ENOMEM;

	spin_lock(&mmu_context_lock);
	err = idr_get_new_above(&mmu_context_idr, NULL, 1, &index);
	spin_unlock(&mmu_context_lock);

	if (err == -EAGAIN)
		goto again;
	else if (err)
		return err;

	if (index > MAX_CONTEXT) {
		spin_lock(&mmu_context_lock);
		idr_remove(&mmu_context_idr, index);
		spin_unlock(&mmu_context_lock);
		return -ENOMEM;
	}

	/* The old code would re-promote on fork, we don't do that
	 * when using slices as it could cause problem promoting slices
	 * that have been forced down to 4K
	 */
	if (slice_mm_new_context(mm))
		slice_set_user_psize(mm, mmu_virtual_psize);
	mm->context.id = index;

	return 0;
}