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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {scalar_t__ bt_enable_flag; scalar_t__ last_bt_traffic_load; scalar_t__ bt_traffic_load; scalar_t__ iw_mode; scalar_t__ bt_status; scalar_t__ bt_ci_compliance; int /*<<< orphan*/  bt_runtime_config; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  bt_traffic_change_work; int /*<<< orphan*/  bt_ch_announce; int /*<<< orphan*/  bt_is_sco; } ;
struct iwl_device_cmd {int dummy; } ;
struct iwl_bt_uart_msg {int dummy; } ;
struct iwl_bt_coex_profile_notif {scalar_t__ bt_status; scalar_t__ bt_traffic_load; scalar_t__ bt_ci_compliance; struct iwl_bt_uart_msg last_bt_uart_msg; } ;

/* Variables and functions */
 scalar_t__ IWLAGN_BT_FLAG_COEX_MODE_DISABLED ; 
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_NONE ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_priv*,char*,...) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  iwlagn_bt_traffic_is_sco (struct iwl_bt_uart_msg*) ; 
 scalar_t__ iwlagn_fill_txpower_mode (struct iwl_priv*,struct iwl_bt_uart_msg*) ; 
 int /*<<< orphan*/  iwlagn_print_uartmsg (struct iwl_priv*,struct iwl_bt_uart_msg*) ; 
 scalar_t__ iwlagn_set_kill_msk (struct iwl_priv*,struct iwl_bt_uart_msg*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

int iwlagn_bt_coex_profile_notif(struct iwl_priv *priv,
				  struct iwl_rx_cmd_buffer *rxb,
				  struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_bt_coex_profile_notif *coex = (void *)pkt->data;
	struct iwl_bt_uart_msg *uart_msg = &coex->last_bt_uart_msg;

	if (priv->bt_enable_flag == IWLAGN_BT_FLAG_COEX_MODE_DISABLED) {
		/* bt coex disabled */
		return 0;
	}

	IWL_DEBUG_COEX(priv, "BT Coex notification:\n");
	IWL_DEBUG_COEX(priv, "    status: %d\n", coex->bt_status);
	IWL_DEBUG_COEX(priv, "    traffic load: %d\n", coex->bt_traffic_load);
	IWL_DEBUG_COEX(priv, "    CI compliance: %d\n",
			coex->bt_ci_compliance);
	iwlagn_print_uartmsg(priv, uart_msg);

	priv->last_bt_traffic_load = priv->bt_traffic_load;
	priv->bt_is_sco = iwlagn_bt_traffic_is_sco(uart_msg);

	if (priv->iw_mode != NL80211_IFTYPE_ADHOC) {
		if (priv->bt_status != coex->bt_status ||
		    priv->last_bt_traffic_load != coex->bt_traffic_load) {
			if (coex->bt_status) {
				/* BT on */
				if (!priv->bt_ch_announce)
					priv->bt_traffic_load =
						IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
				else
					priv->bt_traffic_load =
						coex->bt_traffic_load;
			} else {
				/* BT off */
				priv->bt_traffic_load =
					IWL_BT_COEX_TRAFFIC_LOAD_NONE;
			}
			priv->bt_status = coex->bt_status;
			queue_work(priv->workqueue,
				   &priv->bt_traffic_change_work);
		}
	}

	/* schedule to send runtime bt_config */
	/* check reduce power before change ack/cts kill mask */
	if (iwlagn_fill_txpower_mode(priv, uart_msg) ||
	    iwlagn_set_kill_msk(priv, uart_msg))
		queue_work(priv->workqueue, &priv->bt_runtime_config);


	/* FIXME: based on notification, adjust the prio_boost */

	priv->bt_ci_compliance = coex->bt_ci_compliance;
	return 0;
}