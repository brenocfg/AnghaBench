#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  cap; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_supported_band {TYPE_6__ ht_cap; } ;
struct TYPE_9__ {scalar_t__ width; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_11__ {TYPE_4__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; struct ieee80211_local* local; } ;
struct TYPE_8__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
struct ieee80211_ht_cap {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int ieee80211_get_sdata_band (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_ie_build_ht_cap (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

int mesh_add_ht_cap_ie(struct ieee80211_sub_if_data *sdata,
		       struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	enum ieee80211_band band = ieee80211_get_sdata_band(sdata);
	struct ieee80211_supported_band *sband;
	u8 *pos;

	sband = local->hw.wiphy->bands[band];
	if (!sband->ht_cap.ht_supported ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT)
		return 0;

	if (skb_tailroom(skb) < 2 + sizeof(struct ieee80211_ht_cap))
		return -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(struct ieee80211_ht_cap));
	ieee80211_ie_build_ht_cap(pos, &sband->ht_cap, sband->ht_cap.cap);

	return 0;
}