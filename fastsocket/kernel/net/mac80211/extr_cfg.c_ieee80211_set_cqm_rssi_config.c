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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_bss_conf {scalar_t__ cqm_rssi_thold; scalar_t__ cqm_rssi_hyst; } ;
struct ieee80211_vif {int driver_flags; struct ieee80211_bss_conf bss_conf; } ;
struct TYPE_3__ {scalar_t__ associated; } ;
struct TYPE_4__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_vif vif; TYPE_2__ u; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_CQM ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_set_cqm_rssi_config(struct wiphy *wiphy,
					 struct net_device *dev,
					 s32 rssi_thold, u32 rssi_hyst)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_vif *vif = &sdata->vif;
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

	if (rssi_thold == bss_conf->cqm_rssi_thold &&
	    rssi_hyst == bss_conf->cqm_rssi_hyst)
		return 0;

	bss_conf->cqm_rssi_thold = rssi_thold;
	bss_conf->cqm_rssi_hyst = rssi_hyst;

	/* tell the driver upon association, unless already associated */
	if (sdata->u.mgd.associated &&
	    sdata->vif.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_CQM);

	return 0;
}