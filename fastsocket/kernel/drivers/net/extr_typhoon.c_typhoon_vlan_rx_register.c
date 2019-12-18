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
struct vlan_group {int dummy; } ;
struct typhoon {int /*<<< orphan*/  state_lock; struct vlan_group* vlgrp; int /*<<< orphan*/  name; int /*<<< orphan*/  offload; } ;
struct net_device {int dummy; } ;
struct cmd_desc {int /*<<< orphan*/  parm3; int /*<<< orphan*/  parm2; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMMAND_WITH_RESPONSE (struct cmd_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPHOON_CMD_SET_OFFLOAD_TASKS ; 
 int /*<<< orphan*/  TYPHOON_OFFLOAD_VLAN ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int typhoon_issue_command (struct typhoon*,int,struct cmd_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
typhoon_vlan_rx_register(struct net_device *dev, struct vlan_group *grp)
{
	struct typhoon *tp = netdev_priv(dev);
	struct cmd_desc xp_cmd;
	int err;

	spin_lock_bh(&tp->state_lock);
	if(!tp->vlgrp != !grp) {
		/* We've either been turned on for the first time, or we've
		 * been turned off. Update the 3XP.
		 */
		if(grp)
			tp->offload |= TYPHOON_OFFLOAD_VLAN;
		else
			tp->offload &= ~TYPHOON_OFFLOAD_VLAN;

		/* If the interface is up, the runtime is running -- and we
		 * must be up for the vlan core to call us.
		 *
		 * Do the command outside of the spin lock, as it is slow.
		 */
		INIT_COMMAND_WITH_RESPONSE(&xp_cmd,
					TYPHOON_CMD_SET_OFFLOAD_TASKS);
		xp_cmd.parm2 = tp->offload;
		xp_cmd.parm3 = tp->offload;
		spin_unlock_bh(&tp->state_lock);
		err = typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);
		if(err < 0)
			printk("%s: vlan offload error %d\n", tp->name, -err);
		spin_lock_bh(&tp->state_lock);
	}

	/* now make the change visible */
	tp->vlgrp = grp;
	spin_unlock_bh(&tp->state_lock);
}