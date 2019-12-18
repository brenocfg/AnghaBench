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
typedef  void* u8 ;
typedef  void* u16 ;
struct lbs_offset_value {int /*<<< orphan*/  value; int /*<<< orphan*/  offset; } ;
struct cmd_ds_rf_reg_access {void* value; void* offset; void* action; } ;
struct cmd_ds_mac_reg_access {int /*<<< orphan*/  value; void* offset; void* action; } ;
struct TYPE_2__ {int /*<<< orphan*/  rfreg; int /*<<< orphan*/  bbpreg; int /*<<< orphan*/  macreg; } ;
struct cmd_ds_command {TYPE_1__ params; void* size; int /*<<< orphan*/  command; } ;
struct cmd_ds_bbp_reg_access {void* value; void* offset; void* action; } ;

/* Variables and functions */
#define  CMD_BBP_REG_ACCESS 130 
#define  CMD_MAC_REG_ACCESS 129 
#define  CMD_RF_REG_ACCESS 128 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 int /*<<< orphan*/  S_DS_GEN ; 
 void* cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_cmd_reg_access(struct cmd_ds_command *cmdptr,
			       u8 cmd_action, void *pdata_buf)
{
	struct lbs_offset_value *offval;

	lbs_deb_enter(LBS_DEB_CMD);

	offval = (struct lbs_offset_value *)pdata_buf;

	switch (le16_to_cpu(cmdptr->command)) {
	case CMD_MAC_REG_ACCESS:
		{
			struct cmd_ds_mac_reg_access *macreg;

			cmdptr->size =
			    cpu_to_le16(sizeof (struct cmd_ds_mac_reg_access)
					+ S_DS_GEN);
			macreg =
			    (struct cmd_ds_mac_reg_access *)&cmdptr->params.
			    macreg;

			macreg->action = cpu_to_le16(cmd_action);
			macreg->offset = cpu_to_le16((u16) offval->offset);
			macreg->value = cpu_to_le32(offval->value);

			break;
		}

	case CMD_BBP_REG_ACCESS:
		{
			struct cmd_ds_bbp_reg_access *bbpreg;

			cmdptr->size =
			    cpu_to_le16(sizeof
					     (struct cmd_ds_bbp_reg_access)
					     + S_DS_GEN);
			bbpreg =
			    (struct cmd_ds_bbp_reg_access *)&cmdptr->params.
			    bbpreg;

			bbpreg->action = cpu_to_le16(cmd_action);
			bbpreg->offset = cpu_to_le16((u16) offval->offset);
			bbpreg->value = (u8) offval->value;

			break;
		}

	case CMD_RF_REG_ACCESS:
		{
			struct cmd_ds_rf_reg_access *rfreg;

			cmdptr->size =
			    cpu_to_le16(sizeof
					     (struct cmd_ds_rf_reg_access) +
					     S_DS_GEN);
			rfreg =
			    (struct cmd_ds_rf_reg_access *)&cmdptr->params.
			    rfreg;

			rfreg->action = cpu_to_le16(cmd_action);
			rfreg->offset = cpu_to_le16((u16) offval->offset);
			rfreg->value = (u8) offval->value;

			break;
		}

	default:
		break;
	}

	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}