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
struct cn_callback_entry {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ cn_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cn_callback_entry*) ; 

__attribute__((used)) static void cn_queue_free_callback(struct cn_callback_entry *cbq)
{
	/* The first jobs have been sent to kevent, flush them too */
	flush_scheduled_work();
	if (cbq->pdev->cn_queue)
		flush_workqueue(cbq->pdev->cn_queue);

	kfree(cbq);
}