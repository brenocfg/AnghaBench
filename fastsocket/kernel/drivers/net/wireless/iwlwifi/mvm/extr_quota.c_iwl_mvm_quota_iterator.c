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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct iwl_mvm_vif {int /*<<< orphan*/  monitor_active; int /*<<< orphan*/  ap_active; TYPE_1__* phy_ctxt; } ;
struct iwl_mvm_quota_iterator_data {scalar_t__* colors; int /*<<< orphan*/ * n_interfaces; struct ieee80211_vif* new_vif; } ;
struct TYPE_4__ {int /*<<< orphan*/  ibss_joined; int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {int type; TYPE_2__ bss_conf; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ color; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MAX_BINDINGS ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MONITOR 130 
#define  NL80211_IFTYPE_P2P_DEVICE 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ NUM_PHY_CTX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_quota_iterator(void *_data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct iwl_mvm_quota_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u16 id;

	/*
	 * We'll account for the new interface (if any) below,
	 * skip it here in case we're not called from within
	 * the add_interface callback (otherwise it won't show
	 * up in iteration)
	 */
	if (vif == data->new_vif)
		return;

	if (!mvmvif->phy_ctxt)
		return;

	/* currently, PHY ID == binding ID */
	id = mvmvif->phy_ctxt->id;

	/* need at least one binding per PHY */
	BUILD_BUG_ON(NUM_PHY_CTX > MAX_BINDINGS);

	if (WARN_ON_ONCE(id >= MAX_BINDINGS))
		return;

	if (data->colors[id] < 0)
		data->colors[id] = mvmvif->phy_ctxt->color;
	else
		WARN_ON_ONCE(data->colors[id] != mvmvif->phy_ctxt->color);

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		if (vif->bss_conf.assoc)
			data->n_interfaces[id]++;
		break;
	case NL80211_IFTYPE_AP:
		if (mvmvif->ap_active)
			data->n_interfaces[id]++;
		break;
	case NL80211_IFTYPE_MONITOR:
		if (mvmvif->monitor_active)
			data->n_interfaces[id]++;
		break;
	case NL80211_IFTYPE_P2P_DEVICE:
		break;
	case NL80211_IFTYPE_ADHOC:
		if (vif->bss_conf.ibss_joined)
			data->n_interfaces[id]++;
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}
}