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
struct vm_area_struct {int /*<<< orphan*/  vm_end; } ;
struct shared_policy {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {TYPE_1__ w; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 struct mempolicy* mpol_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int mpol_set_nodemask (struct mempolicy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_set_shared_policy (struct shared_policy*,struct vm_area_struct*,struct mempolicy*) ; 
 int /*<<< orphan*/  scratch ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 

void mpol_shared_policy_init(struct shared_policy *sp, struct mempolicy *mpol)
{
	int ret;

	sp->root = RB_ROOT;		/* empty tree == default mempolicy */
	spin_lock_init(&sp->lock);

	if (mpol) {
		struct vm_area_struct pvma;
		struct mempolicy *new;
		NODEMASK_SCRATCH(scratch);

		if (!scratch)
			return;
		/* contextualize the tmpfs mount point mempolicy */
		new = mpol_new(mpol->mode, mpol->flags, &mpol->w.user_nodemask);
		if (IS_ERR(new)) {
			mpol_put(mpol);	/* drop our ref on sb mpol */
			NODEMASK_SCRATCH_FREE(scratch);
			return;		/* no valid nodemask intersection */
		}

		task_lock(current);
		ret = mpol_set_nodemask(new, &mpol->w.user_nodemask, scratch);
		task_unlock(current);
		mpol_put(mpol);	/* drop our ref on sb mpol */
		if (ret) {
			NODEMASK_SCRATCH_FREE(scratch);
			mpol_put(new);
			return;
		}

		/* Create pseudo-vma that contains just the policy */
		memset(&pvma, 0, sizeof(struct vm_area_struct));
		pvma.vm_end = TASK_SIZE;	/* policy covers entire file */
		mpol_set_shared_policy(sp, &pvma, new); /* adds ref */
		mpol_put(new);			/* drop initial ref */
		NODEMASK_SCRATCH_FREE(scratch);
	}
}