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
struct il_priv {int dummy; } ;
struct il_host_cmd {int flags; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int il_send_cmd_async (struct il_priv*,struct il_host_cmd*) ; 
 int il_send_cmd_sync (struct il_priv*,struct il_host_cmd*) ; 

int
il_send_cmd(struct il_priv *il, struct il_host_cmd *cmd)
{
	if (cmd->flags & CMD_ASYNC)
		return il_send_cmd_async(il, cmd);

	return il_send_cmd_sync(il, cmd);
}