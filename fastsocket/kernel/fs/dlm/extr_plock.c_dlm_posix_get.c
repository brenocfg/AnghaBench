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
struct TYPE_4__ {int ex; int rv; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ pid; void* owner; scalar_t__ number; int /*<<< orphan*/  fsid; int /*<<< orphan*/  optype; } ;
struct plock_op {scalar_t__ done; TYPE_2__ info; int /*<<< orphan*/  list; } ;
struct file_lock {scalar_t__ fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; scalar_t__ fl_pid; int /*<<< orphan*/  fl_flags; scalar_t__ fl_owner; TYPE_1__* fl_lmops; } ;
struct file {int dummy; } ;
struct dlm_ls {int /*<<< orphan*/  ls_global_id; } ;
typedef  int /*<<< orphan*/  dlm_lockspace_t ;
typedef  void* __u64 ;
struct TYPE_3__ {scalar_t__ fl_grant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_PLOCK_OP_GET ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FL_POSIX ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  kfree (struct plock_op*) ; 
 struct plock_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,unsigned long long) ; 
 int /*<<< orphan*/  ops_lock ; 
 int /*<<< orphan*/  recv_wq ; 
 int /*<<< orphan*/  send_op (struct plock_op*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int dlm_posix_get(dlm_lockspace_t *lockspace, u64 number, struct file *file,
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

	op->info.optype		= DLM_PLOCK_OP_GET;
	op->info.pid		= fl->fl_pid;
	op->info.ex		= (fl->fl_type == F_WRLCK);
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	if (fl->fl_lmops && fl->fl_lmops->fl_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	else
		op->info.owner	= (__u64)(long) fl->fl_owner;

	send_op(op);
	wait_event(recv_wq, (op->done != 0));

	spin_lock(&ops_lock);
	if (!list_empty(&op->list)) {
		log_error(ls, "dlm_posix_get: op on list %llx",
			  (unsigned long long)number);
		list_del(&op->list);
	}
	spin_unlock(&ops_lock);

	/* info.rv from userspace is 1 for conflict, 0 for no-conflict,
	   -ENOENT if there are no locks on the file */

	rv = op->info.rv;

	fl->fl_type = F_UNLCK;
	if (rv == -ENOENT)
		rv = 0;
	else if (rv > 0) {
		locks_init_lock(fl);
		fl->fl_type = (op->info.ex) ? F_WRLCK : F_RDLCK;
		fl->fl_flags = FL_POSIX;
		fl->fl_pid = op->info.pid;
		fl->fl_start = op->info.start;
		fl->fl_end = op->info.end;
		rv = 0;
	}

	kfree(op);
out:
	dlm_put_lockspace(ls);
	return rv;
}