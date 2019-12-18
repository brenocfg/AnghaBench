#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sta_info {int dummy; } ;
struct ieee802_11_elems {scalar_t__ pwr_constr_elem; int /*<<< orphan*/  country_elem_len; scalar_t__ country_elem; int /*<<< orphan*/ * opmode_notif; int /*<<< orphan*/  vht_operation; int /*<<< orphan*/  ht_operation; int /*<<< orphan*/ * erp_info; TYPE_12__* tim; int /*<<< orphan*/  wmm_param_len; int /*<<< orphan*/  wmm_param; int /*<<< orphan*/  tim_len; } ;
struct ieee80211_bss_conf {int cqm_rssi_thold; int cqm_rssi_hyst; int dtim_period; scalar_t__ sync_dtim_count; int /*<<< orphan*/  sync_device_ts; void* sync_tsf; int /*<<< orphan*/  p2p_noa_attr; } ;
struct TYPE_14__ {int driver_flags; struct ieee80211_bss_conf bss_conf; scalar_t__ p2p; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_if_managed {int last_beacon_signal; int flags; int ave_beacon_signal; int last_cqm_event_signal; int count_beacon_signal; int last_ave_beacon_signal; scalar_t__ rssi_min_thold; scalar_t__ rssi_max_thold; scalar_t__ p2p_noa_index; int beacon_crc_valid; scalar_t__ beacon_crc; scalar_t__ powersave; int /*<<< orphan*/  aid; TYPE_4__* associated; TYPE_3__* assoc_data; int /*<<< orphan*/  mtx; } ;
struct TYPE_21__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_11__ vif; TYPE_6__ u; struct ieee80211_local* local; } ;
struct ieee80211_rx_status {scalar_t__ freq; int signal; int /*<<< orphan*/  band; int /*<<< orphan*/  device_timestamp; } ;
struct ieee80211_p2p_noa_attr {scalar_t__ index; } ;
struct TYPE_24__ {int capab_info; } ;
struct TYPE_23__ {int /*<<< orphan*/  capab_info; int /*<<< orphan*/  timestamp; scalar_t__ variable; int /*<<< orphan*/  beacon_int; } ;
struct TYPE_13__ {TYPE_9__ probe_resp; TYPE_8__ beacon; } ;
struct ieee80211_mgmt {TYPE_10__ u; int /*<<< orphan*/  bssid; } ;
struct TYPE_20__ {scalar_t__ dynamic_ps_timeout; int flags; } ;
struct TYPE_22__ {int flags; TYPE_5__ conf; } ;
struct ieee80211_local {int pspolling; int /*<<< orphan*/  sta_mtx; TYPE_7__ hw; int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  mtx; } ;
struct ieee80211_channel {scalar_t__ center_freq; } ;
struct TYPE_16__ {struct ieee80211_channel* chan; } ;
struct ieee80211_chanctx_conf {TYPE_1__ def; } ;
typedef  int /*<<< orphan*/  noa ;
typedef  enum rx_mgmt_action { ____Placeholder_rx_mgmt_action } rx_mgmt_action ;
struct TYPE_19__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_18__ {int need_beacon; int have_beacon; int timeout_started; int /*<<< orphan*/  timeout; TYPE_2__* bss; } ;
struct TYPE_17__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_15__ {scalar_t__ dtim_count; scalar_t__ dtim_period; } ;

/* Variables and functions */
 scalar_t__ BSS_CHANGED_DTIM_PERIOD ; 
 scalar_t__ BSS_CHANGED_P2P_PS ; 
 scalar_t__ BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_PS ; 
 int IEEE80211_HW_PS_NULLFUNC_STACK ; 
 int IEEE80211_HW_TIMING_BEACON_ONLY ; 
 int /*<<< orphan*/  IEEE80211_P2P_ATTR_ABSENCE_NOTICE ; 
 int IEEE80211_SIGNAL_AVE_MIN_COUNT ; 
 int IEEE80211_SIGNAL_AVE_WEIGHT ; 
 int IEEE80211_STA_BEACON_POLL ; 
 int IEEE80211_STA_RESET_SIGNAL_AVE ; 
 int /*<<< orphan*/  IEEE80211_STYPE_DEAUTH ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW ; 
 int /*<<< orphan*/  RSSI_EVENT_HIGH ; 
 int /*<<< orphan*/  RSSI_EVENT_LOW ; 
 int RX_MGMT_CFG80211_TX_DEAUTH ; 
 int RX_MGMT_NONE ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_SPECTRUM_MGMT ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  care_about_ies ; 
 int cfg80211_get_p2p_attr (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32_be (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  drv_rssi_callback (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,scalar_t__) ; 
 int ieee80211_check_tim (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_config_bw (struct ieee80211_sub_if_data*,struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ieee80211_cqm_rssi_notify (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_handle_bss_capability (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_handle_pwr_constr (struct ieee80211_sub_if_data*,struct ieee80211_channel*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_recalc_ps (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  ieee80211_run_deferred_scan (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_rx_bss_info (struct ieee80211_sub_if_data*,struct ieee80211_mgmt*,size_t,struct ieee80211_rx_status*,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  ieee80211_send_nullfunc (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_pspoll (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_set_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_beacon_monitor (struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_sta_wmm_params (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vht_handle_opmode (struct ieee80211_sub_if_data*,struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (scalar_t__,size_t,int,struct ieee802_11_elems*) ; 
 scalar_t__ ieee802_11_parse_elems_crc (scalar_t__,size_t,int,struct ieee802_11_elems*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_p2p_noa_attr*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlme_dbg_ratelimited (struct ieee80211_sub_if_data*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  run_again (struct ieee80211_if_managed*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum rx_mgmt_action
ieee80211_rx_mgmt_beacon(struct ieee80211_sub_if_data *sdata,
			 struct ieee80211_mgmt *mgmt, size_t len,
			 u8 *deauth_buf, struct ieee80211_rx_status *rx_status)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_bss_conf *bss_conf = &sdata->vif.bss_conf;
	size_t baselen;
	struct ieee802_11_elems elems;
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *chan;
	struct sta_info *sta;
	u32 changed = 0;
	bool erp_valid;
	u8 erp_value = 0;
	u32 ncrc;
	u8 *bssid;

	lockdep_assert_held(&ifmgd->mtx);

	/* Process beacon from the current BSS */
	baselen = (u8 *) mgmt->u.beacon.variable - (u8 *) mgmt;
	if (baselen > len)
		return RX_MGMT_NONE;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (!chanctx_conf) {
		rcu_read_unlock();
		return RX_MGMT_NONE;
	}

	if (rx_status->freq != chanctx_conf->def.chan->center_freq) {
		rcu_read_unlock();
		return RX_MGMT_NONE;
	}
	chan = chanctx_conf->def.chan;
	rcu_read_unlock();

	if (ifmgd->assoc_data && ifmgd->assoc_data->need_beacon &&
	    ether_addr_equal(mgmt->bssid, ifmgd->assoc_data->bss->bssid)) {
		ieee802_11_parse_elems(mgmt->u.beacon.variable,
				       len - baselen, false, &elems);

		ieee80211_rx_bss_info(sdata, mgmt, len, rx_status, &elems);
		ifmgd->assoc_data->have_beacon = true;
		ifmgd->assoc_data->need_beacon = false;
		if (local->hw.flags & IEEE80211_HW_TIMING_BEACON_ONLY) {
			sdata->vif.bss_conf.sync_tsf =
				le64_to_cpu(mgmt->u.beacon.timestamp);
			sdata->vif.bss_conf.sync_device_ts =
				rx_status->device_timestamp;
			if (elems.tim)
				sdata->vif.bss_conf.sync_dtim_count =
					elems.tim->dtim_count;
			else
				sdata->vif.bss_conf.sync_dtim_count = 0;
		}
		/* continue assoc process */
		ifmgd->assoc_data->timeout = jiffies;
		ifmgd->assoc_data->timeout_started = true;
		run_again(ifmgd, ifmgd->assoc_data->timeout);
		return RX_MGMT_NONE;
	}

	if (!ifmgd->associated ||
	    !ether_addr_equal(mgmt->bssid, ifmgd->associated->bssid))
		return RX_MGMT_NONE;
	bssid = ifmgd->associated->bssid;

	/* Track average RSSI from the Beacon frames of the current AP */
	ifmgd->last_beacon_signal = rx_status->signal;
	if (ifmgd->flags & IEEE80211_STA_RESET_SIGNAL_AVE) {
		ifmgd->flags &= ~IEEE80211_STA_RESET_SIGNAL_AVE;
		ifmgd->ave_beacon_signal = rx_status->signal * 16;
		ifmgd->last_cqm_event_signal = 0;
		ifmgd->count_beacon_signal = 1;
		ifmgd->last_ave_beacon_signal = 0;
	} else {
		ifmgd->ave_beacon_signal =
			(IEEE80211_SIGNAL_AVE_WEIGHT * rx_status->signal * 16 +
			 (16 - IEEE80211_SIGNAL_AVE_WEIGHT) *
			 ifmgd->ave_beacon_signal) / 16;
		ifmgd->count_beacon_signal++;
	}

	if (ifmgd->rssi_min_thold != ifmgd->rssi_max_thold &&
	    ifmgd->count_beacon_signal >= IEEE80211_SIGNAL_AVE_MIN_COUNT) {
		int sig = ifmgd->ave_beacon_signal;
		int last_sig = ifmgd->last_ave_beacon_signal;

		/*
		 * if signal crosses either of the boundaries, invoke callback
		 * with appropriate parameters
		 */
		if (sig > ifmgd->rssi_max_thold &&
		    (last_sig <= ifmgd->rssi_min_thold || last_sig == 0)) {
			ifmgd->last_ave_beacon_signal = sig;
			drv_rssi_callback(local, sdata, RSSI_EVENT_HIGH);
		} else if (sig < ifmgd->rssi_min_thold &&
			   (last_sig >= ifmgd->rssi_max_thold ||
			   last_sig == 0)) {
			ifmgd->last_ave_beacon_signal = sig;
			drv_rssi_callback(local, sdata, RSSI_EVENT_LOW);
		}
	}

	if (bss_conf->cqm_rssi_thold &&
	    ifmgd->count_beacon_signal >= IEEE80211_SIGNAL_AVE_MIN_COUNT &&
	    !(sdata->vif.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)) {
		int sig = ifmgd->ave_beacon_signal / 16;
		int last_event = ifmgd->last_cqm_event_signal;
		int thold = bss_conf->cqm_rssi_thold;
		int hyst = bss_conf->cqm_rssi_hyst;
		if (sig < thold &&
		    (last_event == 0 || sig < last_event - hyst)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				GFP_KERNEL);
		} else if (sig > thold &&
			   (last_event == 0 || sig > last_event + hyst)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				GFP_KERNEL);
		}
	}

	if (ifmgd->flags & IEEE80211_STA_BEACON_POLL) {
		mlme_dbg_ratelimited(sdata,
				     "cancelling AP probe due to a received beacon\n");
		mutex_lock(&local->mtx);
		ifmgd->flags &= ~IEEE80211_STA_BEACON_POLL;
		ieee80211_run_deferred_scan(local);
		mutex_unlock(&local->mtx);

		mutex_lock(&local->iflist_mtx);
		ieee80211_recalc_ps(local, -1);
		mutex_unlock(&local->iflist_mtx);
	}

	/*
	 * Push the beacon loss detection into the future since
	 * we are processing a beacon from the AP just now.
	 */
	ieee80211_sta_reset_beacon_monitor(sdata);

	ncrc = crc32_be(0, (void *)&mgmt->u.beacon.beacon_int, 4);
	ncrc = ieee802_11_parse_elems_crc(mgmt->u.beacon.variable,
					  len - baselen, false, &elems,
					  care_about_ies, ncrc);

	if (local->hw.flags & IEEE80211_HW_PS_NULLFUNC_STACK) {
		bool directed_tim = ieee80211_check_tim(elems.tim,
							elems.tim_len,
							ifmgd->aid);
		if (directed_tim) {
			if (local->hw.conf.dynamic_ps_timeout > 0) {
				if (local->hw.conf.flags & IEEE80211_CONF_PS) {
					local->hw.conf.flags &= ~IEEE80211_CONF_PS;
					ieee80211_hw_config(local,
							    IEEE80211_CONF_CHANGE_PS);
				}
				ieee80211_send_nullfunc(local, sdata, 0);
			} else if (!local->pspolling && sdata->u.mgd.powersave) {
				local->pspolling = true;

				/*
				 * Here is assumed that the driver will be
				 * able to send ps-poll frame and receive a
				 * response even though power save mode is
				 * enabled, but some drivers might require
				 * to disable power save here. This needs
				 * to be investigated.
				 */
				ieee80211_send_pspoll(local, sdata);
			}
		}
	}

	if (sdata->vif.p2p) {
		struct ieee80211_p2p_noa_attr noa = {};
		int ret;

		ret = cfg80211_get_p2p_attr(mgmt->u.beacon.variable,
					    len - baselen,
					    IEEE80211_P2P_ATTR_ABSENCE_NOTICE,
					    (u8 *) &noa, sizeof(noa));
		if (ret >= 2) {
			if (sdata->u.mgd.p2p_noa_index != noa.index) {
				/* valid noa_attr and index changed */
				sdata->u.mgd.p2p_noa_index = noa.index;
				memcpy(&bss_conf->p2p_noa_attr, &noa, sizeof(noa));
				changed |= BSS_CHANGED_P2P_PS;
				/*
				 * make sure we update all information, the CRC
				 * mechanism doesn't look at P2P attributes.
				 */
				ifmgd->beacon_crc_valid = false;
			}
		} else if (sdata->u.mgd.p2p_noa_index != -1) {
			/* noa_attr not found and we had valid noa_attr before */
			sdata->u.mgd.p2p_noa_index = -1;
			memset(&bss_conf->p2p_noa_attr, 0, sizeof(bss_conf->p2p_noa_attr));
			changed |= BSS_CHANGED_P2P_PS;
			ifmgd->beacon_crc_valid = false;
		}
	}

	if (ncrc == ifmgd->beacon_crc && ifmgd->beacon_crc_valid)
		return RX_MGMT_NONE;
	ifmgd->beacon_crc = ncrc;
	ifmgd->beacon_crc_valid = true;

	ieee80211_rx_bss_info(sdata, mgmt, len, rx_status, &elems);

	if (ieee80211_sta_wmm_params(local, sdata, elems.wmm_param,
				     elems.wmm_param_len))
		changed |= BSS_CHANGED_QOS;

	/*
	 * If we haven't had a beacon before, tell the driver about the
	 * DTIM period (and beacon timing if desired) now.
	 */
	if (!bss_conf->dtim_period) {
		/* a few bogus AP send dtim_period = 0 or no TIM IE */
		if (elems.tim)
			bss_conf->dtim_period = elems.tim->dtim_period ?: 1;
		else
			bss_conf->dtim_period = 1;

		if (local->hw.flags & IEEE80211_HW_TIMING_BEACON_ONLY) {
			sdata->vif.bss_conf.sync_tsf =
				le64_to_cpu(mgmt->u.beacon.timestamp);
			sdata->vif.bss_conf.sync_device_ts =
				rx_status->device_timestamp;
			if (elems.tim)
				sdata->vif.bss_conf.sync_dtim_count =
					elems.tim->dtim_count;
			else
				sdata->vif.bss_conf.sync_dtim_count = 0;
		}

		changed |= BSS_CHANGED_DTIM_PERIOD;
	}

	if (elems.erp_info) {
		erp_valid = true;
		erp_value = elems.erp_info[0];
	} else {
		erp_valid = false;
	}
	changed |= ieee80211_handle_bss_capability(sdata,
			le16_to_cpu(mgmt->u.beacon.capab_info),
			erp_valid, erp_value);

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, bssid);

	if (ieee80211_config_bw(sdata, sta, elems.ht_operation,
				elems.vht_operation, bssid, &changed)) {
		mutex_unlock(&local->sta_mtx);
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_DEAUTH_LEAVING,
				       true, deauth_buf);
		return RX_MGMT_CFG80211_TX_DEAUTH;
	}

	if (sta && elems.opmode_notif)
		ieee80211_vht_handle_opmode(sdata, sta, *elems.opmode_notif,
					    rx_status->band, true);
	mutex_unlock(&local->sta_mtx);

	if (elems.country_elem && elems.pwr_constr_elem &&
	    mgmt->u.probe_resp.capab_info &
				cpu_to_le16(WLAN_CAPABILITY_SPECTRUM_MGMT))
		changed |= ieee80211_handle_pwr_constr(sdata, chan,
						       elems.country_elem,
						       elems.country_elem_len,
						       elems.pwr_constr_elem);

	ieee80211_bss_info_change_notify(sdata, changed);

	return RX_MGMT_NONE;
}