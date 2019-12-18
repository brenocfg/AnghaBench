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
struct request_queue {struct elevator_queue* elevator; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* elevator_may_queue_fn ) (struct request_queue*,int) ;} ;

/* Variables and functions */
 int ELV_MQUEUE_MAY ; 
 int stub1 (struct request_queue*,int) ; 

int elv_may_queue(struct request_queue *q, int rw)
{
	struct elevator_queue *e = q->elevator;

	if (e->ops->elevator_may_queue_fn)
		return e->ops->elevator_may_queue_fn(q, rw);

	return ELV_MQUEUE_MAY;
}