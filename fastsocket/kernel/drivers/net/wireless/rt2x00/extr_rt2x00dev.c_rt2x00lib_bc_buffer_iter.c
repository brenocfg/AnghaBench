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
struct sk_buff {int dummy; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 struct sk_buff* ieee80211_get_buffered_bc (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rt2x00mac_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void rt2x00lib_bc_buffer_iter(void *data, u8 *mac,
				     struct ieee80211_vif *vif)
{
	struct rt2x00_dev *rt2x00dev = data;
	struct sk_buff *skb;

	/*
	 * Only AP mode interfaces do broad- and multicast buffering
	 */
	if (vif->type != NL80211_IFTYPE_AP)
		return;

	/*
	 * Send out buffered broad- and multicast frames
	 */
	skb = ieee80211_get_buffered_bc(rt2x00dev->hw, vif);
	while (skb) {
		rt2x00mac_tx(rt2x00dev->hw, NULL, skb);
		skb = ieee80211_get_buffered_bc(rt2x00dev->hw, vif);
	}
}