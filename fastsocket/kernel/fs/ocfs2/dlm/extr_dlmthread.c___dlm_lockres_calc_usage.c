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
struct dlm_lock_resource {int /*<<< orphan*/  purge; int /*<<< orphan*/  owner; TYPE_1__ lockname; int /*<<< orphan*/  last_used; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  purge_count; int /*<<< orphan*/  purge_list; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 scalar_t__ __dlm_lockres_unused (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_get (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_lock_resource*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __dlm_lockres_calc_usage(struct dlm_ctxt *dlm,
			      struct dlm_lock_resource *res)
{
	mlog_entry("%.*s\n", res->lockname.len, res->lockname.name);

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&res->spinlock);

	if (__dlm_lockres_unused(res)){
		if (list_empty(&res->purge)) {
			mlog(0, "putting lockres %.*s:%p onto purge list\n",
			     res->lockname.len, res->lockname.name, res);

			res->last_used = jiffies;
			dlm_lockres_get(res);
			list_add_tail(&res->purge, &dlm->purge_list);
			dlm->purge_count++;
		}
	} else if (!list_empty(&res->purge)) {
		mlog(0, "removing lockres %.*s:%p from purge list, owner=%u\n",
		     res->lockname.len, res->lockname.name, res, res->owner);

		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
	}
}