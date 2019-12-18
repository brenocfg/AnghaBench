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
typedef  int u8 ;
typedef  int u32 ;
struct slot {int /*<<< orphan*/  hp_slot; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT_REG (int /*<<< orphan*/ ) ; 
#define  SLOT_STATE_DISABLED 130 
#define  SLOT_STATE_ENABLED 129 
 int SLOT_STATE_MASK ; 
#define  SLOT_STATE_PWRONLY 128 
 int SLOT_STATE_SHIFT ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_power_status(struct slot * slot, u8 *status)
{
	struct controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_readl(ctrl, SLOT_REG(slot->hp_slot));
	u8 state = (slot_reg & SLOT_STATE_MASK) >> SLOT_STATE_SHIFT;

	switch (state) {
	case SLOT_STATE_PWRONLY:
		*status = 2;	/* Powered only */
		break;
	case SLOT_STATE_ENABLED:
		*status = 1;	/* Enabled */
		break;
	case SLOT_STATE_DISABLED:
		*status = 0;	/* Disabled */
		break;
	default:
		*status = 0xFF;	/* Reserved */
		break;
	}

	return 0;
}