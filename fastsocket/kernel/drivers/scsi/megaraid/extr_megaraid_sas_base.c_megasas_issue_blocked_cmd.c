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
struct megasas_instance {int /*<<< orphan*/  int_cmd_wait_q; TYPE_1__* instancet; } ;
struct megasas_cmd {scalar_t__ cmd_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* issue_dcmd ) (struct megasas_instance*,struct megasas_cmd*) ;} ;

/* Variables and functions */
 scalar_t__ ENODATA ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
megasas_issue_blocked_cmd(struct megasas_instance *instance,
			  struct megasas_cmd *cmd)
{
	cmd->cmd_status = ENODATA;

	instance->instancet->issue_dcmd(instance, cmd);

	wait_event(instance->int_cmd_wait_q, cmd->cmd_status != ENODATA);

	return 0;
}