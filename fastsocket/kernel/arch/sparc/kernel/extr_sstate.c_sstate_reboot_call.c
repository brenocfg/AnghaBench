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

/* Variables and functions */
 int /*<<< orphan*/  HV_SOFT_STATE_TRANSITION ; 
 int NOTIFY_OK ; 
#define  SYS_DOWN 130 
#define  SYS_HALT 129 
#define  SYS_POWER_OFF 128 
 int /*<<< orphan*/  do_set_sstate (int /*<<< orphan*/ ,char const*) ; 
 char* halting_msg ; 
 char* poweroff_msg ; 
 char* rebooting_msg ; 

__attribute__((used)) static int sstate_reboot_call(struct notifier_block *np, unsigned long type, void *_unused)
{
	const char *msg;

	switch (type) {
	case SYS_DOWN:
	default:
		msg = rebooting_msg;
		break;

	case SYS_HALT:
		msg = halting_msg;
		break;

	case SYS_POWER_OFF:
		msg = poweroff_msg;
		break;
	}

	do_set_sstate(HV_SOFT_STATE_TRANSITION, msg);

	return NOTIFY_OK;
}