#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct binder_proc* private_data; } ;
struct binder_proc {int pid; int /*<<< orphan*/  delivered_death; int /*<<< orphan*/  proc_node; int /*<<< orphan*/  default_priority; int /*<<< orphan*/  wait; int /*<<< orphan*/  todo; TYPE_2__* tsk; } ;
typedef  int /*<<< orphan*/  strbuf ;
struct TYPE_6__ {TYPE_1__* group_leader; int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_OPEN_CLOSE ; 
 int /*<<< orphan*/  BINDER_STAT_PROC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_lock ; 
 scalar_t__ binder_proc_dir_entry_proc ; 
 int /*<<< orphan*/  binder_procs ; 
 int /*<<< orphan*/  binder_read_proc_proc ; 
 int /*<<< orphan*/  binder_stats_created (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_proc_read_entry (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct binder_proc*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  get_task_struct (TYPE_2__*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct binder_proc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  task_nice (TYPE_2__*) ; 

__attribute__((used)) static int binder_open(struct inode *nodp, struct file *filp)
{
	struct binder_proc *proc;

	binder_debug(BINDER_DEBUG_OPEN_CLOSE, "binder_open: %d:%d\n",
		     current->group_leader->pid, current->pid);

	proc = kzalloc(sizeof(*proc), GFP_KERNEL);
	if (proc == NULL)
		return -ENOMEM;
	get_task_struct(current);
	proc->tsk = current;
	INIT_LIST_HEAD(&proc->todo);
	init_waitqueue_head(&proc->wait);
	proc->default_priority = task_nice(current);
	mutex_lock(&binder_lock);
	binder_stats_created(BINDER_STAT_PROC);
	hlist_add_head(&proc->proc_node, &binder_procs);
	proc->pid = current->group_leader->pid;
	INIT_LIST_HEAD(&proc->delivered_death);
	filp->private_data = proc;
	mutex_unlock(&binder_lock);

	if (binder_proc_dir_entry_proc) {
		char strbuf[11];
		snprintf(strbuf, sizeof(strbuf), "%u", proc->pid);
		remove_proc_entry(strbuf, binder_proc_dir_entry_proc);
		create_proc_read_entry(strbuf, S_IRUGO,
				       binder_proc_dir_entry_proc,
				       binder_read_proc_proc, proc);
	}

	return 0;
}