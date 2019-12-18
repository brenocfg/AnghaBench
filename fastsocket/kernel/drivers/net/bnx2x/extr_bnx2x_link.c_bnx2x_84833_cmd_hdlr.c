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
typedef  scalar_t__ u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 scalar_t__ MDIO_84833_CMD_HDLR_COMMAND ; 
 scalar_t__ MDIO_84833_CMD_HDLR_DATA1 ; 
 scalar_t__ MDIO_84833_CMD_HDLR_STATUS ; 
 int /*<<< orphan*/  MDIO_CTL_DEVAD ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int PHY84833_CMDHDLR_WAIT ; 
 scalar_t__ PHY84833_STATUS_CMD_CLEAR_COMPLETE ; 
 scalar_t__ PHY84833_STATUS_CMD_COMPLETE_ERROR ; 
 scalar_t__ PHY84833_STATUS_CMD_COMPLETE_PASS ; 
 scalar_t__ PHY84833_STATUS_CMD_OPEN_FOR_CMDS ; 
 scalar_t__ PHY84833_STATUS_CMD_OPEN_OVERRIDE ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_84833_cmd_hdlr(struct bnx2x_phy *phy,
				struct link_params *params, u16 fw_cmd,
				u16 cmd_args[], int argc)
{
	int idx;
	u16 val;
	struct bnx2x *bp = params->bp;
	/* Write CMD_OPEN_OVERRIDE to STATUS reg */
	bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
			MDIO_84833_CMD_HDLR_STATUS,
			PHY84833_STATUS_CMD_OPEN_OVERRIDE);
	for (idx = 0; idx < PHY84833_CMDHDLR_WAIT; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_84833_CMD_HDLR_STATUS, &val);
		if (val == PHY84833_STATUS_CMD_OPEN_FOR_CMDS)
			break;
		usleep_range(1000, 2000);
	}
	if (idx >= PHY84833_CMDHDLR_WAIT) {
		DP(NETIF_MSG_LINK, "FW cmd: FW not ready.\n");
		return -EINVAL;
	}

	/* Prepare argument(s) and issue command */
	for (idx = 0; idx < argc; idx++) {
		bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
				MDIO_84833_CMD_HDLR_DATA1 + idx,
				cmd_args[idx]);
	}
	bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
			MDIO_84833_CMD_HDLR_COMMAND, fw_cmd);
	for (idx = 0; idx < PHY84833_CMDHDLR_WAIT; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_84833_CMD_HDLR_STATUS, &val);
		if ((val == PHY84833_STATUS_CMD_COMPLETE_PASS) ||
			(val == PHY84833_STATUS_CMD_COMPLETE_ERROR))
			break;
		usleep_range(1000, 2000);
	}
	if ((idx >= PHY84833_CMDHDLR_WAIT) ||
		(val == PHY84833_STATUS_CMD_COMPLETE_ERROR)) {
		DP(NETIF_MSG_LINK, "FW cmd failed.\n");
		return -EINVAL;
	}
	/* Gather returning data */
	for (idx = 0; idx < argc; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_84833_CMD_HDLR_DATA1 + idx,
				&cmd_args[idx]);
	}
	bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
			MDIO_84833_CMD_HDLR_STATUS,
			PHY84833_STATUS_CMD_CLEAR_COMPLETE);
	return 0;
}