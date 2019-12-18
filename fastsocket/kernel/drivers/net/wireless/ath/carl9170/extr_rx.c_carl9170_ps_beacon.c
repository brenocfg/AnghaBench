#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_tim_ie {int dtim_count; int bitmap_ctrl; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;
struct TYPE_8__ {int dtim_counter; int /*<<< orphan*/  off_override; int /*<<< orphan*/  last_beacon; } ;
struct TYPE_7__ {int /*<<< orphan*/  curaid; int /*<<< orphan*/  curbssid; } ;
struct ar9170 {TYPE_4__ ps; TYPE_3__ common; TYPE_2__* hw; } ;
struct TYPE_5__ {int flags; int ps_dtim_period; } ;
struct TYPE_6__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int FCS_LEN ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  PS_OFF_BCN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WLAN_EID_TIM ; 
 int* carl9170_find_ie (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_ps_check (struct ar9170*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_check_tim (struct ieee80211_tim_ie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void carl9170_ps_beacon(struct ar9170 *ar, void *data, unsigned int len)
{
	struct ieee80211_hdr *hdr = data;
	struct ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_len;
	bool cam;

	if (likely(!(ar->hw->conf.flags & IEEE80211_CONF_PS)))
		return;

	/* check if this really is a beacon */
	if (!ieee80211_is_beacon(hdr->frame_control))
		return;

	/* min. beacon length + FCS_LEN */
	if (len <= 40 + FCS_LEN)
		return;

	/* and only beacons from the associated BSSID, please */
	if (!ether_addr_equal(hdr->addr3, ar->common.curbssid) ||
	    !ar->common.curaid)
		return;

	ar->ps.last_beacon = jiffies;

	tim = carl9170_find_ie(data, len - FCS_LEN, WLAN_EID_TIM);
	if (!tim)
		return;

	if (tim[1] < sizeof(*tim_ie))
		return;

	tim_len = tim[1];
	tim_ie = (struct ieee80211_tim_ie *) &tim[2];

	if (!WARN_ON_ONCE(!ar->hw->conf.ps_dtim_period))
		ar->ps.dtim_counter = (tim_ie->dtim_count - 1) %
			ar->hw->conf.ps_dtim_period;

	/* Check whenever the PHY can be turned off again. */

	/* 1. What about buffered unicast traffic for our AID? */
	cam = ieee80211_check_tim(tim_ie, tim_len, ar->common.curaid);

	/* 2. Maybe the AP wants to send multicast/broadcast data? */
	cam |= !!(tim_ie->bitmap_ctrl & 0x01);

	if (!cam) {
		/* back to low-power land. */
		ar->ps.off_override &= ~PS_OFF_BCN;
		carl9170_ps_check(ar);
	} else {
		/* force CAM */
		ar->ps.off_override |= PS_OFF_BCN;
	}
}