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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct cmd_ds_bt_access {void* id; int /*<<< orphan*/  addr1; void* action; } ;
struct TYPE_2__ {struct cmd_ds_bt_access bt; } ;
struct cmd_ds_command {scalar_t__ result; void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
#define  CMD_ACT_BT_ACCESS_ADD 133 
#define  CMD_ACT_BT_ACCESS_DEL 132 
#define  CMD_ACT_BT_ACCESS_GET_INVERT 131 
#define  CMD_ACT_BT_ACCESS_LIST 130 
#define  CMD_ACT_BT_ACCESS_RESET 129 
#define  CMD_ACT_BT_ACCESS_SET_INVERT 128 
 int CMD_BT_ACCESS ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 int /*<<< orphan*/  LBS_DEB_MESH ; 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int lbs_cmd_bt_access(struct cmd_ds_command *cmd,
			       u16 cmd_action, void *pdata_buf)
{
	struct cmd_ds_bt_access *bt_access = &cmd->params.bt;
	lbs_deb_enter_args(LBS_DEB_CMD, "action %d", cmd_action);

	cmd->command = cpu_to_le16(CMD_BT_ACCESS);
	cmd->size = cpu_to_le16(sizeof(struct cmd_ds_bt_access) + S_DS_GEN);
	cmd->result = 0;
	bt_access->action = cpu_to_le16(cmd_action);

	switch (cmd_action) {
	case CMD_ACT_BT_ACCESS_ADD:
		memcpy(bt_access->addr1, pdata_buf, 2 * ETH_ALEN);
		lbs_deb_hex(LBS_DEB_MESH, "BT_ADD: blinded MAC addr", bt_access->addr1, 6);
		break;
	case CMD_ACT_BT_ACCESS_DEL:
		memcpy(bt_access->addr1, pdata_buf, 1 * ETH_ALEN);
		lbs_deb_hex(LBS_DEB_MESH, "BT_DEL: blinded MAC addr", bt_access->addr1, 6);
		break;
	case CMD_ACT_BT_ACCESS_LIST:
		bt_access->id = cpu_to_le32(*(u32 *) pdata_buf);
		break;
	case CMD_ACT_BT_ACCESS_RESET:
		break;
	case CMD_ACT_BT_ACCESS_SET_INVERT:
		bt_access->id = cpu_to_le32(*(u32 *) pdata_buf);
		break;
	case CMD_ACT_BT_ACCESS_GET_INVERT:
		break;
	default:
		break;
	}
	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}