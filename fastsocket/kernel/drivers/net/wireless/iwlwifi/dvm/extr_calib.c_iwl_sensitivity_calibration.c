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
typedef  scalar_t__ u32 ;
struct statistics_rx_phy {int /*<<< orphan*/  plcp_err; int /*<<< orphan*/  false_alarm_cnt; } ;
struct statistics_rx_non_phy {scalar_t__ interference_data_flag; int /*<<< orphan*/  beacon_energy_c; int /*<<< orphan*/  beacon_energy_b; int /*<<< orphan*/  beacon_energy_a; int /*<<< orphan*/  beacon_silence_rssi_c; int /*<<< orphan*/  beacon_silence_rssi_b; int /*<<< orphan*/  beacon_silence_rssi_a; int /*<<< orphan*/  channel_load; } ;
struct statistics_general_data {void* beacon_energy_c; void* beacon_energy_b; void* beacon_energy_a; void* beacon_silence_rssi_c; void* beacon_silence_rssi_b; void* beacon_silence_rssi_a; } ;
struct iwl_sensitivity_data {scalar_t__ last_bad_plcp_cnt_cck; scalar_t__ last_bad_plcp_cnt_ofdm; scalar_t__ last_fa_cnt_ofdm; scalar_t__ last_fa_cnt_cck; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct statistics_rx_phy rx_cck; struct statistics_rx_phy rx_ofdm; struct statistics_rx_non_phy rx_non_phy; } ;
struct iwl_priv {int calib_disabled; TYPE_2__* fw; TYPE_1__ statistics; struct iwl_sensitivity_data sensitivity_data; } ;
struct TYPE_4__ {scalar_t__ enhance_sensitivity_table; } ;

/* Variables and functions */
 scalar_t__ INTERFERENCE_DATA_AVAILABLE ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,...) ; 
 int IWL_SENSITIVITY_CALIB_DISABLED ; 
 int /*<<< orphan*/  iwl_enhance_sensitivity_write (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_is_any_associated (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_sens_auto_corr_ofdm (struct iwl_priv*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwl_sens_energy_cck (struct iwl_priv*,scalar_t__,scalar_t__,struct statistics_general_data*) ; 
 int /*<<< orphan*/  iwl_sensitivity_write (struct iwl_priv*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_sensitivity_calibration(struct iwl_priv *priv)
{
	u32 rx_enable_time;
	u32 fa_cck;
	u32 fa_ofdm;
	u32 bad_plcp_cck;
	u32 bad_plcp_ofdm;
	u32 norm_fa_ofdm;
	u32 norm_fa_cck;
	struct iwl_sensitivity_data *data = NULL;
	struct statistics_rx_non_phy *rx_info;
	struct statistics_rx_phy *ofdm, *cck;
	struct statistics_general_data statis;

	if (priv->calib_disabled & IWL_SENSITIVITY_CALIB_DISABLED)
		return;

	data = &(priv->sensitivity_data);

	if (!iwl_is_any_associated(priv)) {
		IWL_DEBUG_CALIB(priv, "<< - not associated\n");
		return;
	}

	spin_lock_bh(&priv->statistics.lock);
	rx_info = &priv->statistics.rx_non_phy;
	ofdm = &priv->statistics.rx_ofdm;
	cck = &priv->statistics.rx_cck;
	if (rx_info->interference_data_flag != INTERFERENCE_DATA_AVAILABLE) {
		IWL_DEBUG_CALIB(priv, "<< invalid data.\n");
		spin_unlock_bh(&priv->statistics.lock);
		return;
	}

	/* Extract Statistics: */
	rx_enable_time = le32_to_cpu(rx_info->channel_load);
	fa_cck = le32_to_cpu(cck->false_alarm_cnt);
	fa_ofdm = le32_to_cpu(ofdm->false_alarm_cnt);
	bad_plcp_cck = le32_to_cpu(cck->plcp_err);
	bad_plcp_ofdm = le32_to_cpu(ofdm->plcp_err);

	statis.beacon_silence_rssi_a =
			le32_to_cpu(rx_info->beacon_silence_rssi_a);
	statis.beacon_silence_rssi_b =
			le32_to_cpu(rx_info->beacon_silence_rssi_b);
	statis.beacon_silence_rssi_c =
			le32_to_cpu(rx_info->beacon_silence_rssi_c);
	statis.beacon_energy_a =
			le32_to_cpu(rx_info->beacon_energy_a);
	statis.beacon_energy_b =
			le32_to_cpu(rx_info->beacon_energy_b);
	statis.beacon_energy_c =
			le32_to_cpu(rx_info->beacon_energy_c);

	spin_unlock_bh(&priv->statistics.lock);

	IWL_DEBUG_CALIB(priv, "rx_enable_time = %u usecs\n", rx_enable_time);

	if (!rx_enable_time) {
		IWL_DEBUG_CALIB(priv, "<< RX Enable Time == 0!\n");
		return;
	}

	/* These statistics increase monotonically, and do not reset
	 *   at each beacon.  Calculate difference from last value, or just
	 *   use the new statistics value if it has reset or wrapped around. */
	if (data->last_bad_plcp_cnt_cck > bad_plcp_cck)
		data->last_bad_plcp_cnt_cck = bad_plcp_cck;
	else {
		bad_plcp_cck -= data->last_bad_plcp_cnt_cck;
		data->last_bad_plcp_cnt_cck += bad_plcp_cck;
	}

	if (data->last_bad_plcp_cnt_ofdm > bad_plcp_ofdm)
		data->last_bad_plcp_cnt_ofdm = bad_plcp_ofdm;
	else {
		bad_plcp_ofdm -= data->last_bad_plcp_cnt_ofdm;
		data->last_bad_plcp_cnt_ofdm += bad_plcp_ofdm;
	}

	if (data->last_fa_cnt_ofdm > fa_ofdm)
		data->last_fa_cnt_ofdm = fa_ofdm;
	else {
		fa_ofdm -= data->last_fa_cnt_ofdm;
		data->last_fa_cnt_ofdm += fa_ofdm;
	}

	if (data->last_fa_cnt_cck > fa_cck)
		data->last_fa_cnt_cck = fa_cck;
	else {
		fa_cck -= data->last_fa_cnt_cck;
		data->last_fa_cnt_cck += fa_cck;
	}

	/* Total aborted signal locks */
	norm_fa_ofdm = fa_ofdm + bad_plcp_ofdm;
	norm_fa_cck = fa_cck + bad_plcp_cck;

	IWL_DEBUG_CALIB(priv, "cck: fa %u badp %u  ofdm: fa %u badp %u\n", fa_cck,
			bad_plcp_cck, fa_ofdm, bad_plcp_ofdm);

	iwl_sens_auto_corr_ofdm(priv, norm_fa_ofdm, rx_enable_time);
	iwl_sens_energy_cck(priv, norm_fa_cck, rx_enable_time, &statis);
	if (priv->fw->enhance_sensitivity_table)
		iwl_enhance_sensitivity_write(priv);
	else
		iwl_sensitivity_write(priv);
}