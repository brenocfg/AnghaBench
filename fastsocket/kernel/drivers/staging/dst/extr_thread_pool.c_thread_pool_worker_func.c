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
struct thread_pool_worker {int /*<<< orphan*/  schedule_data; int /*<<< orphan*/  private; int /*<<< orphan*/  (* action ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ has_data; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_pool_worker_make_ready (struct thread_pool_worker*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int thread_pool_worker_func(void *data)
{
	struct thread_pool_worker *w = data;

	while (!kthread_should_stop()) {
		wait_event_interruptible(w->wait,
			kthread_should_stop() || w->has_data);

		if (kthread_should_stop())
			break;

		if (!w->has_data)
			continue;

		w->action(w->private, w->schedule_data);
		thread_pool_worker_make_ready(w);
	}

	return 0;
}