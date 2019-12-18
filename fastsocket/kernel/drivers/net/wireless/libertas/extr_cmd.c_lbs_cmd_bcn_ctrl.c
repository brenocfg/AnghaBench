#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct lbs_private {scalar_t__ beacon_period; scalar_t__ beacon_enable; } ;
struct cmd_ds_802_11_beacon_control {void* beacon_period; void* beacon_enable; void* action; } ;
struct TYPE_2__ {struct cmd_ds_802_11_beacon_control bcn_ctrl; } ;
struct cmd_ds_command {void* command; void* size; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CMD_802_11_BEACON_CTRL ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_cmd_bcn_ctrl(struct lbs_private * priv,
				struct cmd_ds_command *cmd,
				u16 cmd_action)
{
	struct cmd_ds_802_11_beacon_control
		*bcn_ctrl = &cmd->params.bcn_ctrl;

	lbs_deb_enter(LBS_DEB_CMD);
	cmd->size =
	    cpu_to_le16(sizeof(struct cmd_ds_802_11_beacon_control)
			     + S_DS_GEN);
	cmd->command = cpu_to_le16(CMD_802_11_BEACON_CTRL);

	bcn_ctrl->action = cpu_to_le16(cmd_action);
	bcn_ctrl->beacon_enable = cpu_to_le16(priv->beacon_enable);
	bcn_ctrl->beacon_period = cpu_to_le16(priv->beacon_period);

	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}