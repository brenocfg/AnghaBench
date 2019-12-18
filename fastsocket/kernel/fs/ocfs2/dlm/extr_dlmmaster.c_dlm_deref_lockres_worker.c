#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int deref_node; struct dlm_lock_resource* deref_res; } ;
struct TYPE_5__ {TYPE_1__ dl; } ;
struct dlm_work_item {TYPE_2__ u; struct dlm_ctxt* dlm; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int state; TYPE_3__ lockname; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  refmap; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_DROPPING_REF ; 
 int /*<<< orphan*/  DLM_LOCK_RES_SETREF_INPROG ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres_flags (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lockres_calc_usage (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_clear_refmap_bit (int,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_deref_lockres_worker(struct dlm_work_item *item, void *data)
{
	struct dlm_ctxt *dlm;
	struct dlm_lock_resource *res;
	u8 node;
	u8 cleared = 0;

	dlm = item->dlm;
	res = item->u.dl.deref_res;
	node = item->u.dl.deref_node;

	spin_lock(&res->spinlock);
	BUG_ON(res->state & DLM_LOCK_RES_DROPPING_REF);
	if (test_bit(node, res->refmap)) {
		__dlm_wait_on_lockres_flags(res, DLM_LOCK_RES_SETREF_INPROG);
		dlm_lockres_clear_refmap_bit(node, res);
		cleared = 1;
	}
	spin_unlock(&res->spinlock);

	if (cleared) {
		mlog(0, "%s:%.*s node %u ref dropped in dispatch\n",
		     dlm->name, res->lockname.len, res->lockname.name, node);
		dlm_lockres_calc_usage(dlm, res);
	} else {
		mlog(ML_ERROR, "%s:%.*s: node %u trying to drop ref "
		     "but it is already dropped!\n", dlm->name,
		     res->lockname.len, res->lockname.name, node);
		dlm_print_one_lock_resource(res);
	}

	dlm_lockres_put(res);
}