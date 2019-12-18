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
struct cmd_ds_fwt_access {void* action; } ;
struct TYPE_2__ {struct cmd_ds_fwt_access fwt; } ;
struct cmd_ds_command {scalar_t__ result; void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CMD_FWT_ACCESS ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_enter_args (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cmd_ds_fwt_access*,void*,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_fwt_access*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_cmd_fwt_access(struct cmd_ds_command *cmd,
			       u16 cmd_action, void *pdata_buf)
{
	struct cmd_ds_fwt_access *fwt_access = &cmd->params.fwt;
	lbs_deb_enter_args(LBS_DEB_CMD, "action %d", cmd_action);

	cmd->command = cpu_to_le16(CMD_FWT_ACCESS);
	cmd->size = cpu_to_le16(sizeof(struct cmd_ds_fwt_access) + S_DS_GEN);
	cmd->result = 0;

	if (pdata_buf)
		memcpy(fwt_access, pdata_buf, sizeof(*fwt_access));
	else
		memset(fwt_access, 0, sizeof(*fwt_access));

	fwt_access->action = cpu_to_le16(cmd_action);

	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}