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
struct TYPE_2__ {int /*<<< orphan*/  klv_template_id; } ;
struct wl12xx_vif {int /*<<< orphan*/  basic_rate; TYPE_1__ sta; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int /*<<< orphan*/  hw; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_KLV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_nullfunc_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 

int wl12xx_cmd_build_klv_null_data(struct wl1271 *wl,
				   struct wl12xx_vif *wlvif)
{
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);
	struct sk_buff *skb = NULL;
	int ret = -ENOMEM;

	skb = ieee80211_nullfunc_get(wl->hw, vif);
	if (!skb)
		goto out;

	ret = wl1271_cmd_template_set(wl, wlvif->role_id, CMD_TEMPL_KLV,
				      skb->data, skb->len,
				      wlvif->sta.klv_template_id,
				      wlvif->basic_rate);

out:
	dev_kfree_skb(skb);
	if (ret)
		wl1271_warning("cmd build klv null data failed %d", ret);

	return ret;

}