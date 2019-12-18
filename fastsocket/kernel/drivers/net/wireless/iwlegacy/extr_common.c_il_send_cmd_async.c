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
struct il_priv {int /*<<< orphan*/  status; } ;
struct il_host_cmd {int flags; int /*<<< orphan*/  id; scalar_t__ callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CMD_ASYNC ; 
 int CMD_WANT_SKB ; 
 int EBUSY ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int il_enqueue_hcmd (struct il_priv*,struct il_host_cmd*) ; 
 scalar_t__ il_generic_cmd_callback ; 
 int /*<<< orphan*/  il_get_cmd_string (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il_send_cmd_async(struct il_priv *il, struct il_host_cmd *cmd)
{
	int ret;

	BUG_ON(!(cmd->flags & CMD_ASYNC));

	/* An asynchronous command can not expect an SKB to be set. */
	BUG_ON(cmd->flags & CMD_WANT_SKB);

	/* Assign a generic callback if one is not provided */
	if (!cmd->callback)
		cmd->callback = il_generic_cmd_callback;

	if (test_bit(S_EXIT_PENDING, &il->status))
		return -EBUSY;

	ret = il_enqueue_hcmd(il, cmd);
	if (ret < 0) {
		IL_ERR("Error sending %s: enqueue_hcmd failed: %d\n",
		       il_get_cmd_string(cmd->id), ret);
		return ret;
	}
	return 0;
}