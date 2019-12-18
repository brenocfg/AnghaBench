#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct il_priv {size_t cmd_queue; TYPE_2__* txq; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  mutex; } ;
struct il_host_cmd {int flags; int callback; scalar_t__ reply_page; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* meta; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CMD_ASYNC ; 
 int CMD_WANT_SKB ; 
 int /*<<< orphan*/  D_INFO (char*,int /*<<< orphan*/ ) ; 
 int ECANCELED ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOST_COMPLETE_TIMEOUT ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  S_FW_ERROR ; 
 int /*<<< orphan*/  S_HCMD_ACTIVE ; 
 int /*<<< orphan*/  S_RFKILL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int il_enqueue_hcmd (struct il_priv*,struct il_host_cmd*) ; 
 int /*<<< orphan*/  il_free_pages (struct il_priv*,scalar_t__) ; 
 int /*<<< orphan*/  il_get_cmd_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
il_send_cmd_sync(struct il_priv *il, struct il_host_cmd *cmd)
{
	int cmd_idx;
	int ret;

	lockdep_assert_held(&il->mutex);

	BUG_ON(cmd->flags & CMD_ASYNC);

	/* A synchronous command can not have a callback set. */
	BUG_ON(cmd->callback);

	D_INFO("Attempting to send sync command %s\n",
	       il_get_cmd_string(cmd->id));

	set_bit(S_HCMD_ACTIVE, &il->status);
	D_INFO("Setting HCMD_ACTIVE for command %s\n",
	       il_get_cmd_string(cmd->id));

	cmd_idx = il_enqueue_hcmd(il, cmd);
	if (cmd_idx < 0) {
		ret = cmd_idx;
		IL_ERR("Error sending %s: enqueue_hcmd failed: %d\n",
		       il_get_cmd_string(cmd->id), ret);
		goto out;
	}

	ret = wait_event_timeout(il->wait_command_queue,
				 !test_bit(S_HCMD_ACTIVE, &il->status),
				 HOST_COMPLETE_TIMEOUT);
	if (!ret) {
		if (test_bit(S_HCMD_ACTIVE, &il->status)) {
			IL_ERR("Error sending %s: time out after %dms.\n",
			       il_get_cmd_string(cmd->id),
			       jiffies_to_msecs(HOST_COMPLETE_TIMEOUT));

			clear_bit(S_HCMD_ACTIVE, &il->status);
			D_INFO("Clearing HCMD_ACTIVE for command %s\n",
			       il_get_cmd_string(cmd->id));
			ret = -ETIMEDOUT;
			goto cancel;
		}
	}

	if (test_bit(S_RFKILL, &il->status)) {
		IL_ERR("Command %s aborted: RF KILL Switch\n",
		       il_get_cmd_string(cmd->id));
		ret = -ECANCELED;
		goto fail;
	}
	if (test_bit(S_FW_ERROR, &il->status)) {
		IL_ERR("Command %s failed: FW Error\n",
		       il_get_cmd_string(cmd->id));
		ret = -EIO;
		goto fail;
	}
	if ((cmd->flags & CMD_WANT_SKB) && !cmd->reply_page) {
		IL_ERR("Error: Response NULL in '%s'\n",
		       il_get_cmd_string(cmd->id));
		ret = -EIO;
		goto cancel;
	}

	ret = 0;
	goto out;

cancel:
	if (cmd->flags & CMD_WANT_SKB) {
		/*
		 * Cancel the CMD_WANT_SKB flag for the cmd in the
		 * TX cmd queue. Otherwise in case the cmd comes
		 * in later, it will possibly set an invalid
		 * address (cmd->meta.source).
		 */
		il->txq[il->cmd_queue].meta[cmd_idx].flags &= ~CMD_WANT_SKB;
	}
fail:
	if (cmd->reply_page) {
		il_free_pages(il, cmd->reply_page);
		cmd->reply_page = 0;
	}
out:
	return ret;
}