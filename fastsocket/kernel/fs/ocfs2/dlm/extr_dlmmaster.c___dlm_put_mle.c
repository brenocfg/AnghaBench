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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct dlm_master_list_entry {TYPE_1__ mle_refs; struct dlm_ctxt* dlm; } ;
struct dlm_ctxt {int /*<<< orphan*/  master_lock; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_mle_release ; 
 int /*<<< orphan*/  dlm_print_one_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  kref_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,struct dlm_master_list_entry*) ; 

__attribute__((used)) static void __dlm_put_mle(struct dlm_master_list_entry *mle)
{
	struct dlm_ctxt *dlm;
	dlm = mle->dlm;

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&dlm->master_lock);
	if (!atomic_read(&mle->mle_refs.refcount)) {
		/* this may or may not crash, but who cares.
		 * it's a BUG. */
		mlog(ML_ERROR, "bad mle: %p\n", mle);
		dlm_print_one_mle(mle);
		BUG();
	} else
		kref_put(&mle->mle_refs, dlm_mle_release);
}