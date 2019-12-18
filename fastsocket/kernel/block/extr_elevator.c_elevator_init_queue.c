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
struct request_queue {int dummy; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct TYPE_2__ {void* (* elevator_init_fn ) (struct request_queue*) ;} ;

/* Variables and functions */
 void* stub1 (struct request_queue*) ; 

__attribute__((used)) static void *elevator_init_queue(struct request_queue *q,
				 struct elevator_queue *eq)
{
	return eq->ops->elevator_init_fn(q);
}