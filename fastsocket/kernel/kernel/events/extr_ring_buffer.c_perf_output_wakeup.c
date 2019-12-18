#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_output_handle {TYPE_2__* event; TYPE_1__* rb; } ;
struct TYPE_4__ {int pending_wakeup; int /*<<< orphan*/  pending; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_output_wakeup(struct perf_output_handle *handle)
{
	atomic_set(&handle->rb->poll, POLL_IN);

	handle->event->pending_wakeup = 1;
	irq_work_queue(&handle->event->pending);
}