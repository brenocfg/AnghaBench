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
struct elevator_queue {struct as_data* elevator_data; } ;
struct as_data {int /*<<< orphan*/  io_context; int /*<<< orphan*/ * fifo_list; int /*<<< orphan*/  antic_work; int /*<<< orphan*/  antic_timer; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct as_data*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void as_exit_queue(struct elevator_queue *e)
{
	struct as_data *ad = e->elevator_data;

	del_timer_sync(&ad->antic_timer);
	cancel_work_sync(&ad->antic_work);

	BUG_ON(!list_empty(&ad->fifo_list[BLK_RW_SYNC]));
	BUG_ON(!list_empty(&ad->fifo_list[BLK_RW_ASYNC]));

	put_io_context(ad->io_context);
	kfree(ad);
}