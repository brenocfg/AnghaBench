#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iwl_rxon_context {scalar_t__ ctxid; TYPE_3__* vif; int /*<<< orphan*/  staging; int /*<<< orphan*/  rxon_cmd; int /*<<< orphan*/  active; } ;
struct iwl_rxon_cmd {int dummy; } ;
struct iwl_priv {TYPE_2__* cfg; int /*<<< orphan*/  tx_power_next; scalar_t__ start_calib; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__* ht_params; } ;
struct TYPE_5__ {scalar_t__ smps_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 scalar_t__ IWL_RXON_CTX_BSS ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ieee80211_request_smps (TYPE_3__*,scalar_t__) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_init_sensitivity (struct iwl_priv*) ; 
 int iwl_send_rxon_timing (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int iwl_set_tx_power (struct iwl_priv*,int /*<<< orphan*/ ,int) ; 
 int iwlagn_update_beacon (struct iwl_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  iwlagn_update_qos (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  memcpy (struct iwl_rxon_cmd*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int iwlagn_rxon_connect(struct iwl_priv *priv,
			       struct iwl_rxon_context *ctx)
{
	int ret;
	struct iwl_rxon_cmd *active = (void *)&ctx->active;

	/* RXON timing must be before associated RXON */
	if (ctx->ctxid == IWL_RXON_CTX_BSS) {
		ret = iwl_send_rxon_timing(priv, ctx);
		if (ret) {
			IWL_ERR(priv, "Failed to send timing (%d)!\n", ret);
			return ret;
		}
	}
	/* QoS info may be cleared by previous un-assoc RXON */
	iwlagn_update_qos(priv, ctx);

	/*
	 * We'll run into this code path when beaconing is
	 * enabled, but then we also need to send the beacon
	 * to the device.
	 */
	if (ctx->vif && (ctx->vif->type == NL80211_IFTYPE_AP)) {
		ret = iwlagn_update_beacon(priv, ctx->vif);
		if (ret) {
			IWL_ERR(priv,
				"Error sending required beacon (%d)!\n",
				ret);
			return ret;
		}
	}

	priv->start_calib = 0;
	/*
	 * Apply the new configuration.
	 *
	 * Associated RXON doesn't clear the station table in uCode,
	 * so we don't need to restore stations etc. after this.
	 */
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd, CMD_SYNC,
		      sizeof(struct iwl_rxon_cmd), &ctx->staging);
	if (ret) {
		IWL_ERR(priv, "Error setting new RXON (%d)\n", ret);
		return ret;
	}
	memcpy(active, &ctx->staging, sizeof(*active));

	/* IBSS beacon needs to be sent after setting assoc */
	if (ctx->vif && (ctx->vif->type == NL80211_IFTYPE_ADHOC))
		if (iwlagn_update_beacon(priv, ctx->vif))
			IWL_ERR(priv, "Error sending IBSS beacon\n");
	iwl_init_sensitivity(priv);

	/*
	 * If we issue a new RXON command which required a tune then
	 * we must send a new TXPOWER command or we won't be able to
	 * Tx any frames.
	 *
	 * It's expected we set power here if channel is changing.
	 */
	ret = iwl_set_tx_power(priv, priv->tx_power_next, true);
	if (ret) {
		IWL_ERR(priv, "Error sending TX power (%d)\n", ret);
		return ret;
	}

	if (ctx->vif && ctx->vif->type == NL80211_IFTYPE_STATION &&
	    priv->cfg->ht_params && priv->cfg->ht_params->smps_mode)
		ieee80211_request_smps(ctx->vif,
				       priv->cfg->ht_params->smps_mode);

	return 0;
}