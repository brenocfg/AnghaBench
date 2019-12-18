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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  plist; } ;
struct futex_q {int /*<<< orphan*/ * lock_ptr; TYPE_1__ list; struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  plist_del (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wake_futex(struct futex_q *q)
{
	struct task_struct *p = q->task;

	/*
	 * We set q->lock_ptr = NULL _before_ we wake up the task. If
	 * a non futex wake up happens on another CPU then the task
	 * might exit and p would dereference a non existing task
	 * struct. Prevent this by holding a reference on p across the
	 * wake up.
	 */
	get_task_struct(p);

	plist_del(&q->list, &q->list.plist);
	/*
	 * The waiting task can free the futex_q as soon as
	 * q->lock_ptr = NULL is written, without taking any locks. A
	 * memory barrier is required here to prevent the following
	 * store to lock_ptr from getting ahead of the plist_del.
	 */
	smp_wmb();
	q->lock_ptr = NULL;

	wake_up_state(p, TASK_NORMAL);
	put_task_struct(p);
}