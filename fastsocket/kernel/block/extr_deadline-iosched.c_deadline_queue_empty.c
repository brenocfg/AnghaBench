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
struct request_queue {TYPE_1__* elevator; } ;
struct deadline_data {int /*<<< orphan*/ * fifo_list; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int deadline_queue_empty(struct request_queue *q)
{
	struct deadline_data *dd = q->elevator->elevator_data;

	return list_empty(&dd->fifo_list[WRITE])
		&& list_empty(&dd->fifo_list[READ]);
}