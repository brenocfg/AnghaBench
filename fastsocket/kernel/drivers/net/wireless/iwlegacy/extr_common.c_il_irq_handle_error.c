#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; TYPE_5__* cfg; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; TYPE_3__* ops; TYPE_2__* hw; } ;
struct TYPE_10__ {TYPE_4__* mod_params; } ;
struct TYPE_9__ {scalar_t__ restart_fw; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dump_fh ) (struct il_priv*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* dump_nic_error_log ) (struct il_priv*) ;} ;
struct TYPE_7__ {TYPE_1__* wiphy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IL_DBG (int,char*) ; 
 int IL_DL_FW_ERRORS ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  S_FW_ERROR ; 
 int /*<<< orphan*/  S_HCMD_ACTIVE ; 
 int /*<<< orphan*/  S_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int il_get_debug_level (struct il_priv*) ; 
 int /*<<< orphan*/  il_print_rx_config_cmd (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 int /*<<< orphan*/  stub2 (struct il_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
il_irq_handle_error(struct il_priv *il)
{
	/* Set the FW error flag -- cleared on il_down */
	set_bit(S_FW_ERROR, &il->status);

	/* Cancel currently queued command. */
	clear_bit(S_HCMD_ACTIVE, &il->status);

	IL_ERR("Loaded firmware version: %s\n", il->hw->wiphy->fw_version);

	il->ops->dump_nic_error_log(il);
	if (il->ops->dump_fh)
		il->ops->dump_fh(il, NULL, false);
#ifdef CONFIG_IWLEGACY_DEBUG
	if (il_get_debug_level(il) & IL_DL_FW_ERRORS)
		il_print_rx_config_cmd(il);
#endif

	wake_up(&il->wait_command_queue);

	/* Keep the restart process from trying to send host
	 * commands by clearing the INIT status bit */
	clear_bit(S_READY, &il->status);

	if (!test_bit(S_EXIT_PENDING, &il->status)) {
		IL_DBG(IL_DL_FW_ERRORS,
		       "Restarting adapter due to uCode error.\n");

		if (il->cfg->mod_params->restart_fw)
			queue_work(il->workqueue, &il->restart);
	}
}