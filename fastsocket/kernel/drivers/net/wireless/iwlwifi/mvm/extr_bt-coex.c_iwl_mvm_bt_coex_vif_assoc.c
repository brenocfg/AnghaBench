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
struct iwl_mvm {int /*<<< orphan*/  last_bt_notif; } ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_3__ {int band; } ;

/* Variables and functions */
 int IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_notif_handle (struct iwl_mvm*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void iwl_mvm_bt_coex_vif_assoc(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	enum ieee80211_band band;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(vif->chanctx_conf);
	if (chanctx_conf && chanctx_conf->def.chan)
		band = chanctx_conf->def.chan->band;
	else
		band = -1;
	rcu_read_unlock();

	/* if we are in 2GHz we will get a notification from the fw */
	if (band == IEEE80211_BAND_2GHZ)
		return;

	/* else, we can remove all the constraints */
	memset(&mvm->last_bt_notif, 0, sizeof(mvm->last_bt_notif));

	iwl_mvm_bt_coex_notif_handle(mvm);
}