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
struct vmbus_channel {int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_channel ; 
 TYPE_1__ vmbus_connection ; 

__attribute__((used)) static void free_channel(struct vmbus_channel *channel)
{

	/*
	 * We have to release the channel's workqueue/thread in the vmbus's
	 * workqueue/thread context
	 * ie we can't destroy ourselves.
	 */
	INIT_WORK(&channel->work, release_channel);
	queue_work(vmbus_connection.work_queue, &channel->work);
}