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
struct request_queue {int /*<<< orphan*/  queue_head; struct elevator_queue* elevator; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* elevator_queue_empty_fn ) (struct request_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct request_queue*) ; 

int elv_queue_empty(struct request_queue *q)
{
	struct elevator_queue *e = q->elevator;

	if (!list_empty(&q->queue_head))
		return 0;

	if (e->ops->elevator_queue_empty_fn)
		return e->ops->elevator_queue_empty_fn(q);

	return 1;
}