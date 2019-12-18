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
struct request_queue {struct elevator_queue* elevator; int /*<<< orphan*/  queue_lock; } ;
struct elevator_type {int dummy; } ;
struct elevator_queue {TYPE_1__* elevator_type; scalar_t__ registered; int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  elevator_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __elv_unregister_queue (struct elevator_queue*) ; 
 int /*<<< orphan*/  blk_add_trace_msg (struct request_queue*,char*,int /*<<< orphan*/ ) ; 
 struct elevator_queue* elevator_alloc (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  elevator_attach (struct request_queue*,struct elevator_queue*,void*) ; 
 int /*<<< orphan*/  elevator_exit (struct elevator_queue*) ; 
 void* elevator_init_queue (struct request_queue*,struct elevator_queue*) ; 
 int /*<<< orphan*/  elv_quiesce_end (struct request_queue*) ; 
 int /*<<< orphan*/  elv_quiesce_start (struct request_queue*) ; 
 int elv_register_queue (struct request_queue*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elevator_switch(struct request_queue *q, struct elevator_type *new_e)
{
	struct elevator_queue *old_elevator, *e;
	void *data;
	int err;

	/*
	 * Allocate new elevator
	 */
	e = elevator_alloc(q, new_e);
	if (!e)
		return -ENOMEM;

	data = elevator_init_queue(q, e);
	if (!data) {
		kobject_put(&e->kobj);
		return -ENOMEM;
	}

	/*
	 * Turn on BYPASS and drain all requests w/ elevator private data
	 */
	elv_quiesce_start(q);

	/*
	 * Remember old elevator.
	 */
	old_elevator = q->elevator;

	/*
	 * attach and start new elevator
	 */
	spin_lock_irq(q->queue_lock);
	elevator_attach(q, e, data);
	spin_unlock_irq(q->queue_lock);

	if (old_elevator->registered) {
		__elv_unregister_queue(old_elevator);

		err = elv_register_queue(q);
		if (err)
			goto fail_register;
	}

	/*
	 * finally exit old elevator and turn off BYPASS.
	 */
	elevator_exit(old_elevator);
	elv_quiesce_end(q);

	blk_add_trace_msg(q, "elv switch: %s", e->elevator_type->elevator_name);

	return 0;

fail_register:
	/*
	 * switch failed, exit the new io scheduler and reattach the old
	 * one again (along with re-adding the sysfs dir)
	 */
	elevator_exit(e);
	q->elevator = old_elevator;
	elv_register_queue(q);
	elv_quiesce_end(q);

	return err;
}