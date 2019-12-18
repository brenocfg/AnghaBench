#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct line6_dump_request {int /*<<< orphan*/  wait; scalar_t__ in_progress; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  wait ; 

int line6_wait_dump(struct line6_dump_request *l6dr, int nonblock)
{
	int retval = 0;
	DECLARE_WAITQUEUE(wait, current);
	add_wait_queue(&l6dr->wait, &wait);
	current->state = TASK_INTERRUPTIBLE;

	while (l6dr->in_progress) {
		if (nonblock) {
			retval = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			retval = -ERESTARTSYS;
			break;
		} else
			schedule();
	}

	current->state = TASK_RUNNING;
	remove_wait_queue(&l6dr->wait, &wait);
	return retval;
}