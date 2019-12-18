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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {scalar_t__ inflight_locks; int /*<<< orphan*/  wq; TYPE_1__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  node_num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_clear_refmap_bit (int /*<<< orphan*/ ,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void __dlm_lockres_drop_inflight_ref(struct dlm_ctxt *dlm,
				   struct dlm_lock_resource *res,
				   const char *file,
				   int line)
{
	assert_spin_locked(&res->spinlock);

	BUG_ON(res->inflight_locks == 0);
	res->inflight_locks--;
	mlog(0, "%s:%.*s: inflight--: now %u\n",
	     dlm->name, res->lockname.len, res->lockname.name,
	     res->inflight_locks);
	if (res->inflight_locks == 0)
		dlm_lockres_clear_refmap_bit(dlm->node_num, res);
	wake_up(&res->wq);
}