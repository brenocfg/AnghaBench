#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  cfg; int /*<<< orphan*/  cmd_id; } ;
typedef  TYPE_1__ audpp_cmd_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_CFG ; 
 int /*<<< orphan*/  AUDPP_CMD_CFG_ENABLE ; 
 int /*<<< orphan*/  AUDPP_CMD_CFG_SLEEP ; 
 int audpp_send_queue1 (TYPE_1__*,int) ; 

__attribute__((used)) static int audpp_dsp_config(int enable)
{
	audpp_cmd_cfg cmd;

	cmd.cmd_id = AUDPP_CMD_CFG;
	cmd.cfg = enable ? AUDPP_CMD_CFG_ENABLE : AUDPP_CMD_CFG_SLEEP;

	return audpp_send_queue1(&cmd, sizeof(cmd));
}