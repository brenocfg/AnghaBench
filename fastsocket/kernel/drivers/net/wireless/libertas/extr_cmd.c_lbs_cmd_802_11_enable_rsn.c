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
typedef  int uint16_t ;
struct lbs_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_enable_rsn {void* enable; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_ENABLE_RSN ; 
 int CMD_ACT_GET ; 
 int CMD_DISABLE_RSN ; 
 int CMD_ENABLE_RSN ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_enable_rsn*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int le16_to_cpu (void*) ; 

int lbs_cmd_802_11_enable_rsn(struct lbs_private *priv, uint16_t cmd_action,
			      uint16_t *enable)
{
	struct cmd_ds_802_11_enable_rsn cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(cmd_action);

	if (cmd_action == CMD_ACT_GET)
		cmd.enable = 0;
	else {
		if (*enable)
			cmd.enable = cpu_to_le16(CMD_ENABLE_RSN);
		else
			cmd.enable = cpu_to_le16(CMD_DISABLE_RSN);
		lbs_deb_cmd("ENABLE_RSN: %d\n", *enable);
	}

	ret = lbs_cmd_with_response(priv, CMD_802_11_ENABLE_RSN, &cmd);
	if (!ret && cmd_action == CMD_ACT_GET)
		*enable = le16_to_cpu(cmd.enable);

	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}