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
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int iwl_mvm_sta_send_to_fw (struct iwl_mvm*,struct ieee80211_sta*,int) ; 

int iwl_mvm_update_sta(struct iwl_mvm *mvm,
		       struct ieee80211_vif *vif,
		       struct ieee80211_sta *sta)
{
	return iwl_mvm_sta_send_to_fw(mvm, sta, true);
}