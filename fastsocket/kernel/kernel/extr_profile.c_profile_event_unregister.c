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
struct notifier_block {int dummy; } ;
typedef  enum profile_type { ____Placeholder_profile_type } profile_type ;

/* Variables and functions */
 int EINVAL ; 
#define  PROFILE_MUNMAP 129 
#define  PROFILE_TASK_EXIT 128 
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  munmap_notifier ; 
 int /*<<< orphan*/  task_exit_notifier ; 

int profile_event_unregister(enum profile_type type, struct notifier_block *n)
{
	int err = -EINVAL;

	switch (type) {
	case PROFILE_TASK_EXIT:
		err = blocking_notifier_chain_unregister(
				&task_exit_notifier, n);
		break;
	case PROFILE_MUNMAP:
		err = blocking_notifier_chain_unregister(
				&munmap_notifier, n);
		break;
	}

	return err;
}