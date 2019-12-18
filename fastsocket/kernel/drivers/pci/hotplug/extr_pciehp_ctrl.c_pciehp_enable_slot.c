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
typedef  scalar_t__ u8 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ MRL_SENS (struct controller*) ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int board_added (struct slot*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int pciehp_get_adapter_status (struct slot*,scalar_t__*) ; 
 int pciehp_get_latch_status (struct slot*,scalar_t__*) ; 
 int pciehp_get_power_status (struct slot*,scalar_t__*) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  update_slot_info (struct slot*) ; 

int pciehp_enable_slot(struct slot *p_slot)
{
	u8 getstatus = 0;
	int rc;
	struct controller *ctrl = p_slot->ctrl;

	rc = pciehp_get_adapter_status(p_slot, &getstatus);
	if (rc || !getstatus) {
		ctrl_info(ctrl, "No adapter on slot(%s)\n", slot_name(p_slot));
		return -ENODEV;
	}
	if (MRL_SENS(p_slot->ctrl)) {
		rc = pciehp_get_latch_status(p_slot, &getstatus);
		if (rc || getstatus) {
			ctrl_info(ctrl, "Latch open on slot(%s)\n",
				  slot_name(p_slot));
			return -ENODEV;
		}
	}

	if (POWER_CTRL(p_slot->ctrl)) {
		rc = pciehp_get_power_status(p_slot, &getstatus);
		if (rc || getstatus) {
			ctrl_info(ctrl, "Already enabled on slot(%s)\n",
				  slot_name(p_slot));
			return -EINVAL;
		}
	}

	pciehp_get_latch_status(p_slot, &getstatus);

	rc = board_added(p_slot);
	if (rc) {
		pciehp_get_latch_status(p_slot, &getstatus);
	}

	update_slot_info(p_slot);

	return rc;
}