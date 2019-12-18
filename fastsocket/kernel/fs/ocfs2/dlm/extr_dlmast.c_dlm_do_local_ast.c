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
struct dlm_lockstatus {int dummy; } ;
struct dlm_lock_resource {int dummy; } ;
struct TYPE_2__ {scalar_t__ node; } ;
struct dlm_lock {int /*<<< orphan*/  astdata; TYPE_1__ ml; int /*<<< orphan*/  (* ast ) (int /*<<< orphan*/ ) ;struct dlm_lockstatus* lksb; } ;
struct dlm_ctxt {scalar_t__ node_num; } ;
typedef  int /*<<< orphan*/  (* dlm_astlockfunc_t ) (int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dlm_update_lvb (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_lock*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void dlm_do_local_ast(struct dlm_ctxt *dlm, struct dlm_lock_resource *res,
		      struct dlm_lock *lock)
{
	dlm_astlockfunc_t *fn;
	struct dlm_lockstatus *lksb;

	mlog_entry_void();

	lksb = lock->lksb;
	fn = lock->ast;
	BUG_ON(lock->ml.node != dlm->node_num);

	dlm_update_lvb(dlm, res, lock);
	(*fn)(lock->astdata);
}