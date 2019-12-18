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
struct controller {struct controller* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 struct controller* cpqhp_ctrl_list ; 
 int /*<<< orphan*/  cpqhp_pushbutton_thread (scalar_t__) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  interrupt_event_handler (struct controller*) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ pushbutton_pending ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_thread(void* data)
{
	struct controller *ctrl;

	while (1) {
		dbg("!!!!event_thread sleeping\n");
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();

		if (kthread_should_stop())
			break;
		/* Do stuff here */
		if (pushbutton_pending)
			cpqhp_pushbutton_thread(pushbutton_pending);
		else
			for (ctrl = cpqhp_ctrl_list; ctrl; ctrl=ctrl->next)
				interrupt_event_handler(ctrl);
	}
	dbg("event_thread signals exit\n");
	return 0;
}