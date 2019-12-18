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
struct as_data {int /*<<< orphan*/ * fifo_list; } ;
struct TYPE_2__ {struct as_data* elevator_data; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as_queue_empty(struct request_queue *q)
{
	struct as_data *ad = q->elevator->elevator_data;

	return list_empty(&ad->fifo_list[BLK_RW_ASYNC])
		&& list_empty(&ad->fifo_list[BLK_RW_SYNC]);
}