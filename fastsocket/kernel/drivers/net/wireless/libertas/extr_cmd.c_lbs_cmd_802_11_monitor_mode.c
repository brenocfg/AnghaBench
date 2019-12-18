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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct cmd_ds_802_11_monitor_mode {void* mode; void* action; } ;
struct TYPE_2__ {struct cmd_ds_802_11_monitor_mode monitor; } ;
struct cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CMD_802_11_MONITOR_MODE ; 
 scalar_t__ CMD_ACT_SET ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

__attribute__((used)) static int lbs_cmd_802_11_monitor_mode(struct cmd_ds_command *cmd,
				      u16 cmd_action, void *pdata_buf)
{
	struct cmd_ds_802_11_monitor_mode *monitor = &cmd->params.monitor;

	cmd->command = cpu_to_le16(CMD_802_11_MONITOR_MODE);
	cmd->size =
	    cpu_to_le16(sizeof(struct cmd_ds_802_11_monitor_mode) +
			     S_DS_GEN);

	monitor->action = cpu_to_le16(cmd_action);
	if (cmd_action == CMD_ACT_SET) {
		monitor->mode =
		    cpu_to_le16((u16) (*(u32 *) pdata_buf));
	}

	return 0;
}