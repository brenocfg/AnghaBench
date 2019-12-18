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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct p54_common {int powersave_override; int /*<<< orphan*/  aid; int /*<<< orphan*/  bssid; } ;
struct ieee80211_tim_ie {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_check_tim (struct ieee80211_tim_ie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p54_find_ie (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_set_ps (struct p54_common*) ; 

__attribute__((used)) static void p54_pspoll_workaround(struct p54_common *priv, struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (void *) skb->data;
	struct ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_len;
	bool new_psm;

	/* only beacons have a TIM IE */
	if (!ieee80211_is_beacon(hdr->frame_control))
		return;

	if (!priv->aid)
		return;

	/* only consider beacons from the associated BSSID */
	if (!ether_addr_equal(hdr->addr3, priv->bssid))
		return;

	tim = p54_find_ie(skb, WLAN_EID_TIM);
	if (!tim)
		return;

	tim_len = tim[1];
	tim_ie = (struct ieee80211_tim_ie *) &tim[2];

	new_psm = ieee80211_check_tim(tim_ie, tim_len, priv->aid);
	if (new_psm != priv->powersave_override) {
		priv->powersave_override = new_psm;
		p54_set_ps(priv);
	}
}