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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  mwl8k_bss_info_changed_ap (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_bss_info_changed_sta (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl8k_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		       struct ieee80211_bss_conf *info, u32 changed)
{
	if (vif->type == NL80211_IFTYPE_STATION)
		mwl8k_bss_info_changed_sta(hw, vif, info, changed);
	if (vif->type == NL80211_IFTYPE_AP)
		mwl8k_bss_info_changed_ap(hw, vif, info, changed);
}