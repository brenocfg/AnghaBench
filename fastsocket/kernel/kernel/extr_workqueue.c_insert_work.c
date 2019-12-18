#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct work_struct {int /*<<< orphan*/  entry; } ;
struct list_head {int dummy; } ;
struct cpu_workqueue_struct {int /*<<< orphan*/  more_work; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  set_wq_data (struct work_struct*,struct cpu_workqueue_struct*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  trace_workqueue_insertion (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_work(struct cpu_workqueue_struct *cwq,
			struct work_struct *work, struct list_head *head)
{
	trace_workqueue_insertion(cwq->thread, work);

	set_wq_data(work, cwq);
	/*
	 * Ensure that we get the right work->data if we see the
	 * result of list_add() below, see try_to_grab_pending().
	 */
	smp_wmb();
	list_add_tail(&work->entry, head);
	wake_up(&cwq->more_work);
}