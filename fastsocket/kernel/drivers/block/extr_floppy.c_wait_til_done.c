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
struct TYPE_2__ {scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EIO ; 
 TYPE_1__* FDCS ; 
 int FD_COMMAND_ERROR ; 
 int FD_COMMAND_NONE ; 
 int FD_COMMAND_OKAY ; 
 scalar_t__ NO_SIGNAL ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_activity () ; 
 int /*<<< orphan*/  command_done ; 
 int command_status ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  intr_cont ; 
 int /*<<< orphan*/  is_alive (char*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_fdc () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_bh (void (*) ()) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int wait_til_done(void (*handler)(void), int interruptible)
{
	int ret;

	schedule_bh(handler);

	if (command_status < 2 && NO_SIGNAL) {
		DECLARE_WAITQUEUE(wait, current);

		add_wait_queue(&command_done, &wait);
		for (;;) {
			set_current_state(interruptible ?
					  TASK_INTERRUPTIBLE :
					  TASK_UNINTERRUPTIBLE);

			if (command_status >= 2 || !NO_SIGNAL)
				break;

			is_alive("wait_til_done");
			schedule();
		}

		set_current_state(TASK_RUNNING);
		remove_wait_queue(&command_done, &wait);
	}

	if (command_status < 2) {
		cancel_activity();
		cont = &intr_cont;
		reset_fdc();
		return -EINTR;
	}

	if (FDCS->reset)
		command_status = FD_COMMAND_ERROR;
	if (command_status == FD_COMMAND_OKAY)
		ret = 0;
	else
		ret = -EIO;
	command_status = FD_COMMAND_NONE;
	return ret;
}