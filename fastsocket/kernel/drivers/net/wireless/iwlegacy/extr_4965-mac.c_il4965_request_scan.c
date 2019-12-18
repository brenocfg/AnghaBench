#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_19__ {int /*<<< orphan*/  life_time; } ;
struct TYPE_20__ {void* len; void* rate_n_flags; TYPE_8__ stop_time; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  tx_flags; } ;
struct il_scan_cmd {int flags; int filter_flags; int channel_count; void* len; TYPE_9__ tx_cmd; int /*<<< orphan*/ * data; void* rx_chain; int /*<<< orphan*/  good_CRC_th; TYPE_4__* direct_scan; void* suspend_time; void* max_out_time; int /*<<< orphan*/  quiet_time; int /*<<< orphan*/  quiet_plcp_th; } ;
struct il_scan_channel {int dummy; } ;
struct TYPE_18__ {int valid_rx_ant; int valid_tx_ant; int /*<<< orphan*/  bcast_id; } ;
struct TYPE_13__ {int active_chains; } ;
struct TYPE_11__ {int flags; } ;
struct il_priv {int scan_band; int /*<<< orphan*/  status; TYPE_6__* scan_request; TYPE_7__ hw_params; TYPE_2__ chain_noise_data; int /*<<< orphan*/ * scan_tx_ant; TYPE_1__* cfg; TYPE_10__ active; struct il_scan_cmd* scan_cmd; int /*<<< orphan*/  mutex; } ;
struct il_host_cmd {int len; struct il_scan_cmd* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {int beacon_int; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; TYPE_3__ bss_conf; } ;
struct ieee80211_mgmt {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_17__ {int n_ssids; int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; TYPE_5__* ssids; } ;
struct TYPE_16__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_15__ {int /*<<< orphan*/  ssid; scalar_t__ len; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int* scan_rx_antennas; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CHANNEL_MODE_PURE_40 ; 
 int /*<<< orphan*/  CMD_SIZE_HUGE ; 
 int /*<<< orphan*/  C_SCAN ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  D_SCAN (char*,...) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int /*<<< orphan*/  IL_ACTIVE_QUIET_TIME ; 
 int /*<<< orphan*/  IL_GOOD_CRC_TH_DEFAULT ; 
 int /*<<< orphan*/  IL_GOOD_CRC_TH_NEVER ; 
 scalar_t__ IL_MAX_SCAN_SIZE ; 
 int /*<<< orphan*/  IL_PLCP_QUIET_THRESH ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int RATE_1M_PLCP ; 
 int RATE_6M_PLCP ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int RXON_FILTER_ACCEPT_GRP_MSK ; 
 int RXON_FILTER_BCON_AWARE_MSK ; 
 int RXON_FLG_AUTO_DETECT_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_CHANNEL_MODE_MSK ; 
 int RXON_FLG_CHANNEL_MODE_POS ; 
 int RXON_RX_CHAIN_DRIVER_FORCE_POS ; 
 int RXON_RX_CHAIN_FORCE_MIMO_SEL_POS ; 
 int RXON_RX_CHAIN_FORCE_SEL_POS ; 
 int RXON_RX_CHAIN_VALID_POS ; 
 int /*<<< orphan*/  S_POWER_PMI ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 int /*<<< orphan*/  TX_CMD_FLG_SEQ_CTL_MSK ; 
 int /*<<< orphan*/  TX_CMD_LIFE_TIME_INFINITE ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int il4965_first_antenna (int) ; 
 int il4965_get_channels_for_scan (struct il_priv*,struct ieee80211_vif*,int,int,int,void*) ; 
 int /*<<< orphan*/  il4965_toggle_tx_ant (struct il_priv*,int /*<<< orphan*/ *,int) ; 
 int il_fill_probe_req (struct il_priv*,struct ieee80211_mgmt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ il_is_any_associated (struct il_priv*) ; 
 int il_send_cmd_sync (struct il_priv*,struct il_host_cmd*) ; 
 struct il_scan_cmd* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct il_scan_cmd*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il4965_request_scan(struct il_priv *il, struct ieee80211_vif *vif)
{
	struct il_host_cmd cmd = {
		.id = C_SCAN,
		.len = sizeof(struct il_scan_cmd),
		.flags = CMD_SIZE_HUGE,
	};
	struct il_scan_cmd *scan;
	u32 rate_flags = 0;
	u16 cmd_len;
	u16 rx_chain = 0;
	enum ieee80211_band band;
	u8 n_probes = 0;
	u8 rx_ant = il->hw_params.valid_rx_ant;
	u8 rate;
	bool is_active = false;
	int chan_mod;
	u8 active_chains;
	u8 scan_tx_antennas = il->hw_params.valid_tx_ant;
	int ret;

	lockdep_assert_held(&il->mutex);

	if (!il->scan_cmd) {
		il->scan_cmd =
		    kmalloc(sizeof(struct il_scan_cmd) + IL_MAX_SCAN_SIZE,
			    GFP_KERNEL);
		if (!il->scan_cmd) {
			D_SCAN("fail to allocate memory for scan\n");
			return -ENOMEM;
		}
	}
	scan = il->scan_cmd;
	memset(scan, 0, sizeof(struct il_scan_cmd) + IL_MAX_SCAN_SIZE);

	scan->quiet_plcp_th = IL_PLCP_QUIET_THRESH;
	scan->quiet_time = IL_ACTIVE_QUIET_TIME;

	if (il_is_any_associated(il)) {
		u16 interval;
		u32 extra;
		u32 suspend_time = 100;
		u32 scan_suspend_time = 100;

		D_INFO("Scanning while associated...\n");
		interval = vif->bss_conf.beacon_int;

		scan->suspend_time = 0;
		scan->max_out_time = cpu_to_le32(200 * 1024);
		if (!interval)
			interval = suspend_time;

		extra = (suspend_time / interval) << 22;
		scan_suspend_time =
		    (extra | ((suspend_time % interval) * 1024));
		scan->suspend_time = cpu_to_le32(scan_suspend_time);
		D_SCAN("suspend_time 0x%X beacon interval %d\n",
		       scan_suspend_time, interval);
	}

	if (il->scan_request->n_ssids) {
		int i, p = 0;
		D_SCAN("Kicking off active scan\n");
		for (i = 0; i < il->scan_request->n_ssids; i++) {
			/* always does wildcard anyway */
			if (!il->scan_request->ssids[i].ssid_len)
				continue;
			scan->direct_scan[p].id = WLAN_EID_SSID;
			scan->direct_scan[p].len =
			    il->scan_request->ssids[i].ssid_len;
			memcpy(scan->direct_scan[p].ssid,
			       il->scan_request->ssids[i].ssid,
			       il->scan_request->ssids[i].ssid_len);
			n_probes++;
			p++;
		}
		is_active = true;
	} else
		D_SCAN("Start passive scan.\n");

	scan->tx_cmd.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK;
	scan->tx_cmd.sta_id = il->hw_params.bcast_id;
	scan->tx_cmd.stop_time.life_time = TX_CMD_LIFE_TIME_INFINITE;

	switch (il->scan_band) {
	case IEEE80211_BAND_2GHZ:
		scan->flags = RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK;
		chan_mod =
		    le32_to_cpu(il->active.flags & RXON_FLG_CHANNEL_MODE_MSK) >>
		    RXON_FLG_CHANNEL_MODE_POS;
		if (chan_mod == CHANNEL_MODE_PURE_40) {
			rate = RATE_6M_PLCP;
		} else {
			rate = RATE_1M_PLCP;
			rate_flags = RATE_MCS_CCK_MSK;
		}
		break;
	case IEEE80211_BAND_5GHZ:
		rate = RATE_6M_PLCP;
		break;
	default:
		IL_WARN("Invalid scan band\n");
		return -EIO;
	}

	/*
	 * If active scanning is requested but a certain channel is
	 * marked passive, we can do active scanning if we detect
	 * transmissions.
	 *
	 * There is an issue with some firmware versions that triggers
	 * a sysassert on a "good CRC threshold" of zero (== disabled),
	 * on a radar channel even though this means that we should NOT
	 * send probes.
	 *
	 * The "good CRC threshold" is the number of frames that we
	 * need to receive during our dwell time on a channel before
	 * sending out probes -- setting this to a huge value will
	 * mean we never reach it, but at the same time work around
	 * the aforementioned issue. Thus use IL_GOOD_CRC_TH_NEVER
	 * here instead of IL_GOOD_CRC_TH_DISABLED.
	 */
	scan->good_CRC_th =
	    is_active ? IL_GOOD_CRC_TH_DEFAULT : IL_GOOD_CRC_TH_NEVER;

	band = il->scan_band;

	if (il->cfg->scan_rx_antennas[band])
		rx_ant = il->cfg->scan_rx_antennas[band];

	il4965_toggle_tx_ant(il, &il->scan_tx_ant[band], scan_tx_antennas);
	rate_flags |= BIT(il->scan_tx_ant[band]) << RATE_MCS_ANT_POS;
	scan->tx_cmd.rate_n_flags = cpu_to_le32(rate | rate_flags);

	/* In power save mode use one chain, otherwise use all chains */
	if (test_bit(S_POWER_PMI, &il->status)) {
		/* rx_ant has been set to all valid chains previously */
		active_chains =
		    rx_ant & ((u8) (il->chain_noise_data.active_chains));
		if (!active_chains)
			active_chains = rx_ant;

		D_SCAN("chain_noise_data.active_chains: %u\n",
		       il->chain_noise_data.active_chains);

		rx_ant = il4965_first_antenna(active_chains);
	}

	/* MIMO is not used here, but value is required */
	rx_chain |= il->hw_params.valid_rx_ant << RXON_RX_CHAIN_VALID_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_MIMO_SEL_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_SEL_POS;
	rx_chain |= 0x1 << RXON_RX_CHAIN_DRIVER_FORCE_POS;
	scan->rx_chain = cpu_to_le16(rx_chain);

	cmd_len =
	    il_fill_probe_req(il, (struct ieee80211_mgmt *)scan->data,
			      vif->addr, il->scan_request->ie,
			      il->scan_request->ie_len,
			      IL_MAX_SCAN_SIZE - sizeof(*scan));
	scan->tx_cmd.len = cpu_to_le16(cmd_len);

	scan->filter_flags |=
	    (RXON_FILTER_ACCEPT_GRP_MSK | RXON_FILTER_BCON_AWARE_MSK);

	scan->channel_count =
	    il4965_get_channels_for_scan(il, vif, band, is_active, n_probes,
					 (void *)&scan->data[cmd_len]);
	if (scan->channel_count == 0) {
		D_SCAN("channel count %d\n", scan->channel_count);
		return -EIO;
	}

	cmd.len +=
	    le16_to_cpu(scan->tx_cmd.len) +
	    scan->channel_count * sizeof(struct il_scan_channel);
	cmd.data = scan;
	scan->len = cpu_to_le16(cmd.len);

	set_bit(S_SCAN_HW, &il->status);

	ret = il_send_cmd_sync(il, &cmd);
	if (ret)
		clear_bit(S_SCAN_HW, &il->status);

	return ret;
}