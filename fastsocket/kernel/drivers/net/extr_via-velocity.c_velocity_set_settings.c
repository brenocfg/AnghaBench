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
typedef  int u32 ;
struct velocity_info {int /*<<< orphan*/  mac_regs; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ speed; scalar_t__ duplex; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int VELOCITY_AUTONEG_ENABLE ; 
 int VELOCITY_DUPLEX_FULL ; 
 int VELOCITY_LINK_FAIL ; 
 int VELOCITY_SPEED_10 ; 
 int VELOCITY_SPEED_100 ; 
 int check_connection_type (int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  velocity_set_media_mode (struct velocity_info*,int) ; 

__attribute__((used)) static int velocity_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct velocity_info *vptr = netdev_priv(dev);
	u32 curr_status;
	u32 new_status = 0;
	int ret = 0;

	curr_status = check_connection_type(vptr->mac_regs);
	curr_status &= (~VELOCITY_LINK_FAIL);

	new_status |= ((cmd->autoneg) ? VELOCITY_AUTONEG_ENABLE : 0);
	new_status |= ((cmd->speed == SPEED_100) ? VELOCITY_SPEED_100 : 0);
	new_status |= ((cmd->speed == SPEED_10) ? VELOCITY_SPEED_10 : 0);
	new_status |= ((cmd->duplex == DUPLEX_FULL) ? VELOCITY_DUPLEX_FULL : 0);

	if ((new_status & VELOCITY_AUTONEG_ENABLE) && (new_status != (curr_status | VELOCITY_AUTONEG_ENABLE)))
		ret = -EINVAL;
	else
		velocity_set_media_mode(vptr, new_status);

	return ret;
}