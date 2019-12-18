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
struct se_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_put_cmd (struct se_cmd*) ; 

void transport_cmd_finish_abort(struct se_cmd *cmd, int remove)
{
	if (transport_cmd_check_stop_to_fabric(cmd))
		return;
	if (remove)
		transport_put_cmd(cmd);
}