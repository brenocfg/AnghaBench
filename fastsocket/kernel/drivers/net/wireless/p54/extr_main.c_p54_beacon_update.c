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
struct sk_buff {int dummy; } ;
struct p54_common {scalar_t__ tsf_low32; scalar_t__ tsf_high32; int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_control {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int p54_beacon_format_ie_tim (struct sk_buff*) ; 
 int /*<<< orphan*/  p54_tx_80211 (int /*<<< orphan*/ ,struct ieee80211_tx_control*,struct sk_buff*) ; 

__attribute__((used)) static int p54_beacon_update(struct p54_common *priv,
			struct ieee80211_vif *vif)
{
	struct ieee80211_tx_control control = { };
	struct sk_buff *beacon;
	int ret;

	beacon = ieee80211_beacon_get(priv->hw, vif);
	if (!beacon)
		return -ENOMEM;
	ret = p54_beacon_format_ie_tim(beacon);
	if (ret)
		return ret;

	/*
	 * During operation, the firmware takes care of beaconing.
	 * The driver only needs to upload a new beacon template, once
	 * the template was changed by the stack or userspace.
	 *
	 * LMAC API 3.2.2 also specifies that the driver does not need
	 * to cancel the old beacon template by hand, instead the firmware
	 * will release the previous one through the feedback mechanism.
	 */
	p54_tx_80211(priv->hw, &control, beacon);
	priv->tsf_high32 = 0;
	priv->tsf_low32 = 0;

	return 0;
}