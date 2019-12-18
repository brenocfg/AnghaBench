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
struct iwl_priv {int /*<<< orphan*/  max_delta_stats; int /*<<< orphan*/  delta_stats; int /*<<< orphan*/  accum_stats; } ;
struct iwl_notif_statistics {int /*<<< orphan*/  flag; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_priv*,char*) ; 
 int UCODE_STATISTICS_CLEAR_MSK ; 
 int /*<<< orphan*/  iwlagn_rx_statistics (struct iwl_priv*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static int iwlagn_rx_reply_statistics(struct iwl_priv *priv,
				    struct iwl_rx_cmd_buffer *rxb,
				    struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_notif_statistics *stats = (void *)pkt->data;

	if (le32_to_cpu(stats->flag) & UCODE_STATISTICS_CLEAR_MSK) {
#ifdef CONFIG_IWLWIFI_DEBUGFS
		memset(&priv->accum_stats, 0,
			sizeof(priv->accum_stats));
		memset(&priv->delta_stats, 0,
			sizeof(priv->delta_stats));
		memset(&priv->max_delta_stats, 0,
			sizeof(priv->max_delta_stats));
#endif
		IWL_DEBUG_RX(priv, "Statistics have been cleared\n");
	}
	iwlagn_rx_statistics(priv, rxb, cmd);
	return 0;
}