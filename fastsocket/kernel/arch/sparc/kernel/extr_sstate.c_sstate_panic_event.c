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
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  do_set_sstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panicing_msg ; 

__attribute__((used)) static int sstate_panic_event(struct notifier_block *n, unsigned long event, void *ptr)
{
	do_set_sstate(HV_SOFT_STATE_TRANSITION, panicing_msg);

	return NOTIFY_DONE;
}