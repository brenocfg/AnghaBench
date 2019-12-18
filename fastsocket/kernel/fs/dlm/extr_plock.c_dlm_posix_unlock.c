#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int rv; int /*<<< orphan*/  flags; void* owner; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ number; int /*<<< orphan*/  fsid; scalar_t__ pid; int /*<<< orphan*/  optype; } ;
struct plock_op {scalar_t__ done; TYPE_2__ info; int /*<<< orphan*/  list; } ;
struct file_lock {int fl_flags; scalar_t__ fl_owner; scalar_t__ fl_pid; TYPE_1__* fl_lmops; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;
struct file {int dummy; } ;
struct dlm_ls {int /*<<< orphan*/  ls_global_id; } ;
typedef  int /*<<< orphan*/  dlm_lockspace_t ;
typedef  void* __u64 ;
struct TYPE_3__ {scalar_t__ fl_grant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_PLOCK_FL_CLOSE ; 
 int /*<<< orphan*/  DLM_PLOCK_OP_UNLOCK ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int FL_CLOSE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  kfree (struct plock_op*) ; 
 struct plock_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,unsigned long long) ; 
 int /*<<< orphan*/  ops_lock ; 
 scalar_t__ posix_lock_file_wait (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  recv_wq ; 
 int /*<<< orphan*/  send_op (struct plock_op*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int dlm_posix_unlock(dlm_lockspace_t *lockspace, u64 number, struct file *file,
		     struct file_lock *fl)
{
	struct dlm_ls *ls;
	struct plock_op *op;
	int rv;

	ls = dlm_find_lockspace_local(lockspace);
	if (!ls)
		return -EINVAL;

	op = kzalloc(sizeof(*op), GFP_NOFS);
	if (!op) {
		rv = -ENOMEM;
		goto out;
	}

	if (posix_lock_file_wait(file, fl) < 0)
		log_error(ls, "dlm_posix_unlock: vfs unlock error %llx",
			  (unsigned long long)number);

	op->info.optype		= DLM_PLOCK_OP_UNLOCK;
	op->info.pid		= fl->fl_pid;
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	if (fl->fl_lmops && fl->fl_lmops->fl_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	else
		op->info.owner	= (__u64)(long) fl->fl_owner;

	if (fl->fl_flags & FL_CLOSE) {
		op->info.flags |= DLM_PLOCK_FL_CLOSE;
		send_op(op);
		rv = 0;
		goto out;
	}

	send_op(op);
	wait_event(recv_wq, (op->done != 0));

	spin_lock(&ops_lock);
	if (!list_empty(&op->list)) {
		log_error(ls, "dlm_posix_unlock: op on list %llx",
			  (unsigned long long)number);
		list_del(&op->list);
	}
	spin_unlock(&ops_lock);

	rv = op->info.rv;

	if (rv == -ENOENT)
		rv = 0;

	kfree(op);
out:
	dlm_put_lockspace(ls);
	return rv;
}