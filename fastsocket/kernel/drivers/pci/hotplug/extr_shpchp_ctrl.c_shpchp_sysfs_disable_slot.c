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
struct slot {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
#define  BLINKINGOFF_STATE 132 
#define  BLINKINGON_STATE 131 
 int ENODEV ; 
#define  POWEROFF_STATE 130 
#define  POWERON_STATE 129 
#define  STATIC_STATE 128 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int shpchp_disable_slot (struct slot*) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

int shpchp_sysfs_disable_slot(struct slot *p_slot)
{
	int retval = -ENODEV;
	struct controller *ctrl = p_slot->ctrl;

	mutex_lock(&p_slot->lock);
	switch (p_slot->state) {
	case BLINKINGOFF_STATE:
		cancel_delayed_work(&p_slot->work);
	case STATIC_STATE:
		p_slot->state = POWEROFF_STATE;
		mutex_unlock(&p_slot->lock);
		retval = shpchp_disable_slot(p_slot);
		mutex_lock(&p_slot->lock);
		p_slot->state = STATIC_STATE;
		break;
	case POWEROFF_STATE:
		ctrl_info(ctrl, "Slot %s is already in powering off state\n",
			  slot_name(p_slot));
		break;
	case BLINKINGON_STATE:
	case POWERON_STATE:
		ctrl_info(ctrl, "Already disabled on slot %s\n",
			  slot_name(p_slot));
		break;
	default:
		ctrl_err(ctrl, "Not a valid state on slot %s\n",
			 slot_name(p_slot));
		break;
	}
	mutex_unlock(&p_slot->lock);

	return retval;
}