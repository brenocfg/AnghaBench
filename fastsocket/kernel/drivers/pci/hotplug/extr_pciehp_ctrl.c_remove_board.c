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
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ POWER_CTRL (struct controller*) ; 
 scalar_t__ PWR_LED (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pciehp_green_led_off (struct slot*) ; 
 int pciehp_power_off_slot (struct slot*) ; 
 int pciehp_unconfigure_device (struct slot*) ; 

__attribute__((used)) static int remove_board(struct slot *p_slot)
{
	int retval = 0;
	struct controller *ctrl = p_slot->ctrl;

	retval = pciehp_unconfigure_device(p_slot);
	if (retval)
		return retval;

	if (POWER_CTRL(ctrl)) {
		/* power off slot */
		retval = pciehp_power_off_slot(p_slot);
		if (retval) {
			ctrl_err(ctrl,
				 "Issue of Slot Disable command failed\n");
			return retval;
		}
		/*
		 * After turning power off, we must wait for at least 1 second
		 * before taking any action that relies on power having been
		 * removed from the slot/adapter.
		 */
		msleep(1000);
	}

	/* turn off Green LED */
	if (PWR_LED(ctrl))
		pciehp_green_led_off(p_slot);

	return 0;
}