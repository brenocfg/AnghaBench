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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  flags; void* owner; int /*<<< orphan*/  end; scalar_t__ start; int /*<<< orphan*/  number; int /*<<< orphan*/  fsid; scalar_t__ pid; int /*<<< orphan*/  optype; } ;
struct plock_op {TYPE_2__ info; } ;
struct file_lock {scalar_t__ fl_owner; scalar_t__ fl_pid; TYPE_1__* fl_lmops; } ;
struct file {int dummy; } ;
struct dlm_ls {int /*<<< orphan*/  ls_global_id; } ;
typedef  void* __u64 ;
struct TYPE_3__ {scalar_t__ fl_grant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_PLOCK_FL_CLOSE ; 
 int /*<<< orphan*/  DLM_PLOCK_OP_UNLOCK ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 struct plock_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_op (struct plock_op*) ; 

__attribute__((used)) static void do_unlock_close(struct dlm_ls *ls, u64 number,
			    struct file *file, struct file_lock *fl)
{
	struct plock_op *op;

	op = kzalloc(sizeof(*op), GFP_NOFS);
	if (!op)
		return;

	op->info.optype		= DLM_PLOCK_OP_UNLOCK;
	op->info.pid		= fl->fl_pid;
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= 0;
	op->info.end		= OFFSET_MAX;
	if (fl->fl_lmops && fl->fl_lmops->fl_grant)
		op->info.owner	= (__u64) fl->fl_pid;
	else
		op->info.owner	= (__u64)(long) fl->fl_owner;

	op->info.flags |= DLM_PLOCK_FL_CLOSE;
	send_op(op);
}