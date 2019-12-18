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
struct iwl_priv {int ucode_loaded; unsigned long reload_jiffies; scalar_t__ reload_count; int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; int /*<<< orphan*/  notif_wait; } ;
struct TYPE_2__ {scalar_t__ restart_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_FW_ERRORS (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DL_FW_ERRORS ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_MAX_CONTINUE_RELOAD_CNT ; 
 unsigned int IWL_MIN_RELOAD_DURATION ; 
 int /*<<< orphan*/  IWL_RXON_CTX_BSS ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_have_debug_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_print_rx_config_cmd (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 unsigned long jiffies ; 
 unsigned int jiffies_to_msecs (long) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_fw_error(struct iwl_priv *priv, bool ondemand)
{
	unsigned int reload_msec;
	unsigned long reload_jiffies;

#ifdef CONFIG_IWLWIFI_DEBUG
	if (iwl_have_debug_level(IWL_DL_FW_ERRORS))
		iwl_print_rx_config_cmd(priv, IWL_RXON_CTX_BSS);
#endif

	/* uCode is no longer loaded. */
	priv->ucode_loaded = false;

	/* Set the FW error flag -- cleared on iwl_down */
	set_bit(STATUS_FW_ERROR, &priv->status);

	iwl_abort_notification_waits(&priv->notif_wait);

	/* Keep the restart process from trying to send host
	 * commands by clearing the ready bit */
	clear_bit(STATUS_READY, &priv->status);

	if (!ondemand) {
		/*
		 * If firmware keep reloading, then it indicate something
		 * serious wrong and firmware having problem to recover
		 * from it. Instead of keep trying which will fill the syslog
		 * and hang the system, let's just stop it
		 */
		reload_jiffies = jiffies;
		reload_msec = jiffies_to_msecs((long) reload_jiffies -
					(long) priv->reload_jiffies);
		priv->reload_jiffies = reload_jiffies;
		if (reload_msec <= IWL_MIN_RELOAD_DURATION) {
			priv->reload_count++;
			if (priv->reload_count >= IWL_MAX_CONTINUE_RELOAD_CNT) {
				IWL_ERR(priv, "BUG_ON, Stop restarting\n");
				return;
			}
		} else
			priv->reload_count = 0;
	}

	if (!test_bit(STATUS_EXIT_PENDING, &priv->status)) {
		if (iwlwifi_mod_params.restart_fw) {
			IWL_DEBUG_FW_ERRORS(priv,
				  "Restarting adapter due to uCode error.\n");
			queue_work(priv->workqueue, &priv->restart);
		} else
			IWL_DEBUG_FW_ERRORS(priv,
				  "Detected FW error, but not restarting\n");
	}
}