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
struct task_struct {int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  transaction_mutex; int /*<<< orphan*/  response_mutex; int /*<<< orphan*/  request_mutex; int /*<<< orphan*/  reply_waitq; int /*<<< orphan*/  reply_lock; int /*<<< orphan*/  reply_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int xb_init_comms () ; 
 int /*<<< orphan*/  xenbus_thread ; 
 int /*<<< orphan*/  xenwatch_pid ; 
 int /*<<< orphan*/  xenwatch_thread ; 
 TYPE_1__ xs_state ; 

int xs_init(void)
{
	int err;
	struct task_struct *task;

	INIT_LIST_HEAD(&xs_state.reply_list);
	spin_lock_init(&xs_state.reply_lock);
	init_waitqueue_head(&xs_state.reply_waitq);

	mutex_init(&xs_state.request_mutex);
	mutex_init(&xs_state.response_mutex);
	init_rwsem(&xs_state.transaction_mutex);
	init_rwsem(&xs_state.watch_mutex);

	/* Initialize the shared memory rings to talk to xenstored */
	err = xb_init_comms();
	if (err)
		return err;

	task = kthread_run(xenwatch_thread, NULL, "xenwatch");
	if (IS_ERR(task))
		return PTR_ERR(task);
	xenwatch_pid = task->pid;

	task = kthread_run(xenbus_thread, NULL, "xenbus");
	if (IS_ERR(task))
		return PTR_ERR(task);

	return 0;
}