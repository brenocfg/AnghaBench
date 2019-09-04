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
struct task {int dummy; } ;
struct proc {int dummy; } ;
struct label {int dummy; } ;
struct exception_action {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct label*,struct exception_action*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_MACH_UNEXPECTED (char*) ; 
 int /*<<< orphan*/  exc_action_check_exception_send ; 
 struct proc* get_bsdtask_info (struct task*) ; 
 struct label* get_task_crash_label (struct task*) ; 
 struct label* mac_exc_create_label_for_proc (struct proc*) ; 
 int /*<<< orphan*/  mac_exc_free_label (struct label*) ; 

int
mac_exc_action_check_exception_send(struct task *victim_task, struct exception_action *action)
{
	int error = 0;

	struct proc *p = get_bsdtask_info(victim_task);
	struct label *bsd_label = NULL;
	struct label *label = NULL;

	if (p != NULL) {
		// Create a label from the still existing bsd process...
		label = bsd_label = mac_exc_create_label_for_proc(p);
	} else {
		// ... otherwise use the crash label on the task.
		label = get_task_crash_label(victim_task);
	}

	if (label == NULL) {
		MAC_MACH_UNEXPECTED("mac_exc_action_check_exception_send: no exc_action label for process");
		return EPERM;
	}

	MAC_CHECK(exc_action_check_exception_send, label, action, action->label);

	if (bsd_label != NULL) {
		mac_exc_free_label(bsd_label);
	}

	return (error);
}