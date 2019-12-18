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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct ieee80211_bss_conf {int beacon_int; int dtim_period; int assoc; scalar_t__ arp_addr_cnt; scalar_t__ cqm_rssi_thold; TYPE_1__ p2p_noa_attr; int /*<<< orphan*/  assoc_capability; } ;
struct TYPE_10__ {int driver_flags; scalar_t__ p2p; struct ieee80211_bss_conf bss_conf; } ;
struct TYPE_8__ {scalar_t__ dtim_period; TYPE_2__* assoc_data; int /*<<< orphan*/  p2p_noa_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  bssid; struct cfg80211_bss* associated; int /*<<< orphan*/  beacon_timeout; } ;
struct TYPE_9__ {TYPE_3__ mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_5__ vif; TYPE_4__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  iflist_mtx; } ;
struct ieee80211_bss {int /*<<< orphan*/  erp_value; int /*<<< orphan*/  has_erp_value; } ;
struct cfg80211_bss_ies {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {int /*<<< orphan*/  ies; int /*<<< orphan*/  bssid; scalar_t__ priv; } ;
struct TYPE_7__ {scalar_t__ have_beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_ARP_FILTER ; 
 int /*<<< orphan*/  BSS_CHANGED_ASSOC ; 
 int /*<<< orphan*/  BSS_CHANGED_CQM ; 
 int /*<<< orphan*/  BSS_CHANGED_DTIM_PERIOD ; 
 int /*<<< orphan*/  BSS_CHANGED_P2P_PS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_P2P_ATTR_ABSENCE_NOTICE ; 
 int /*<<< orphan*/  IEEE80211_STA_RESET_SIGNAL_AVE ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int beacon_loss_count ; 
 int cfg80211_get_p2p_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_handle_bss_capability (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_led_assoc (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  ieee80211_recalc_ps (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  ieee80211_recalc_ps_vif (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_recalc_smps (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_stop_poll (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_tu_to_usec (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_set_associated(struct ieee80211_sub_if_data *sdata,
				     struct cfg80211_bss *cbss,
				     u32 bss_info_changed)
{
	struct ieee80211_bss *bss = (void *)cbss->priv;
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_bss_conf *bss_conf = &sdata->vif.bss_conf;

	bss_info_changed |= BSS_CHANGED_ASSOC;
	bss_info_changed |= ieee80211_handle_bss_capability(sdata,
		bss_conf->assoc_capability, bss->has_erp_value, bss->erp_value);

	sdata->u.mgd.beacon_timeout = usecs_to_jiffies(ieee80211_tu_to_usec(
		beacon_loss_count * bss_conf->beacon_int));

	sdata->u.mgd.associated = cbss;
	memcpy(sdata->u.mgd.bssid, cbss->bssid, ETH_ALEN);

	sdata->u.mgd.flags |= IEEE80211_STA_RESET_SIGNAL_AVE;

	if (sdata->vif.p2p) {
		const struct cfg80211_bss_ies *ies;

		rcu_read_lock();
		ies = rcu_dereference(cbss->ies);
		if (ies) {
			int ret;

			ret = cfg80211_get_p2p_attr(
					ies->data, ies->len,
					IEEE80211_P2P_ATTR_ABSENCE_NOTICE,
					(u8 *) &bss_conf->p2p_noa_attr,
					sizeof(bss_conf->p2p_noa_attr));
			if (ret >= 2) {
				sdata->u.mgd.p2p_noa_index =
					bss_conf->p2p_noa_attr.index;
				bss_info_changed |= BSS_CHANGED_P2P_PS;
			}
		}
		rcu_read_unlock();
	}

	/* just to be sure */
	ieee80211_stop_poll(sdata);

	ieee80211_led_assoc(local, 1);

	if (sdata->u.mgd.assoc_data->have_beacon) {
		/*
		 * If the AP is buggy we may get here with no DTIM period
		 * known, so assume it's 1 which is the only safe assumption
		 * in that case, although if the TIM IE is broken powersave
		 * probably just won't work at all.
		 */
		bss_conf->dtim_period = sdata->u.mgd.dtim_period ?: 1;
		bss_info_changed |= BSS_CHANGED_DTIM_PERIOD;
	} else {
		bss_conf->dtim_period = 0;
	}

	bss_conf->assoc = 1;

	/* Tell the driver to monitor connection quality (if supported) */
	if (sdata->vif.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI &&
	    bss_conf->cqm_rssi_thold)
		bss_info_changed |= BSS_CHANGED_CQM;

	/* Enable ARP filtering */
	if (bss_conf->arp_addr_cnt)
		bss_info_changed |= BSS_CHANGED_ARP_FILTER;

	ieee80211_bss_info_change_notify(sdata, bss_info_changed);

	mutex_lock(&local->iflist_mtx);
	ieee80211_recalc_ps(local, -1);
	mutex_unlock(&local->iflist_mtx);

	ieee80211_recalc_smps(sdata);
	ieee80211_recalc_ps_vif(sdata);

	netif_carrier_on(sdata->dev);
}