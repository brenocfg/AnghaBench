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
struct wl12xx_vif {int /*<<< orphan*/  flags; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int /*<<< orphan*/  hw; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_AP_PROBE_RESPONSE ; 
 int /*<<< orphan*/  DEBUG_AP ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WLVIF_FLAG_AP_PROBE_RESP_SET ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_proberesp_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wl1271_ap_set_probe_resp_tmpl(struct wl1271 *wl, u32 rates,
					 struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct sk_buff *skb;
	int ret;

	skb = ieee80211_proberesp_get(wl->hw, vif);
	if (!skb)
		return -EOPNOTSUPP;

	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_AP_PROBE_RESPONSE,
				      skb->data,
				      skb->len, 0,
				      rates);
	dev_kfree_skb(skb);

	if (ret < 0)
		goto out;

	wl1271_debug(DEBUG_AP, "probe response updated");
	set_bit(WLVIF_FLAG_AP_PROBE_RESP_SET, &wlvif->flags);

out:
	return ret;
}