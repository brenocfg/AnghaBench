#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sta {int dummy; } ;
struct sta_info {void* rate_ctrl_priv; struct ieee80211_sta sta; } ;
struct sk_buff {int dummy; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_local {struct rate_control_ref* rate_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx_status ) (int /*<<< orphan*/ ,struct ieee80211_supported_band*,struct ieee80211_sta*,void*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STA_RATE_CONTROL ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_supported_band*,struct ieee80211_sta*,void*,struct sk_buff*) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rate_control_tx_status(struct ieee80211_local *local,
					  struct ieee80211_supported_band *sband,
					  struct sta_info *sta,
					  struct sk_buff *skb)
{
	struct rate_control_ref *ref = local->rate_ctrl;
	struct ieee80211_sta *ista = &sta->sta;
	void *priv_sta = sta->rate_ctrl_priv;

	if (!ref || !test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
		return;

	ref->ops->tx_status(ref->priv, sband, ista, priv_sta, skb);
}