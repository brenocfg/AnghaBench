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
struct mapped_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int TASK_INTERRUPTIBLE ; 
 int TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dm_unplug_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  md_in_flight (struct mapped_device*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int dm_wait_for_completion(struct mapped_device *md, int interruptible)
{
	int r = 0;
	DECLARE_WAITQUEUE(wait, current);

	dm_unplug_all(md->queue);

	add_wait_queue(&md->wait, &wait);

	while (1) {
		set_current_state(interruptible);

		if (!md_in_flight(md))
			break;

		if (interruptible == TASK_INTERRUPTIBLE &&
		    signal_pending(current)) {
			r = -EINTR;
			break;
		}

		io_schedule();
	}
	set_current_state(TASK_RUNNING);

	remove_wait_queue(&md->wait, &wait);

	return r;
}