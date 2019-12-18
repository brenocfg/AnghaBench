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
struct lx_rmh {int cmd_idx; int /*<<< orphan*/ * stat; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  dsp_stat; int /*<<< orphan*/  stat_len; int /*<<< orphan*/  cmd_len; } ;
typedef  enum cmd_mb_opcodes { ____Placeholder_cmd_mb_opcodes } cmd_mb_opcodes ;
struct TYPE_2__ {int /*<<< orphan*/  dcStatusType; int /*<<< orphan*/  dcStatusLength; int /*<<< orphan*/  dcCmdLength; int /*<<< orphan*/  dcCodeOp; } ;

/* Variables and functions */
 int CMD_14_INVALID ; 
 int REG_CRM_NUMBER ; 
 TYPE_1__* dsp_commands ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 

__attribute__((used)) static void lx_message_init(struct lx_rmh *rmh, enum cmd_mb_opcodes cmd)
{
	snd_BUG_ON(cmd >= CMD_14_INVALID);

	rmh->cmd[0] = dsp_commands[cmd].dcCodeOp;
	rmh->cmd_len = dsp_commands[cmd].dcCmdLength;
	rmh->stat_len = dsp_commands[cmd].dcStatusLength;
	rmh->dsp_stat = dsp_commands[cmd].dcStatusType;
	rmh->cmd_idx = cmd;
	memset(&rmh->cmd[1], 0, (REG_CRM_NUMBER - 1) * sizeof(u32));

#ifdef CONFIG_SND_DEBUG
	memset(rmh->stat, 0, REG_CRM_NUMBER * sizeof(u32));
#endif
#ifdef RMH_DEBUG
	rmh->cmd_idx = cmd;
#endif
}