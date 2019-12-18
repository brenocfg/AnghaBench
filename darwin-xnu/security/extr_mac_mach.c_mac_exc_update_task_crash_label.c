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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct label*,struct label*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exc_action_label_update ; 
 struct label* get_task_crash_label (struct task*) ; 
 struct task* kernel_task ; 

int mac_exc_update_task_crash_label(struct task *task, struct label *label) {
	int error;

	assert(task != kernel_task);

	struct label *crash_label = get_task_crash_label(task);

	MAC_CHECK(exc_action_label_update, NULL, crash_label, label);
	
	return (error);
}