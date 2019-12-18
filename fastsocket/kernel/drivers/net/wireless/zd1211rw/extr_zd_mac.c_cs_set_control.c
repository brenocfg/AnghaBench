#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zd_mac {int dummy; } ;
struct zd_ctrlset {int /*<<< orphan*/  control; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_TX_CTL_FIRST_FRAGMENT ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int /*<<< orphan*/  ZD_CS_NEED_RANDOM_BACKOFF ; 
 int /*<<< orphan*/  ZD_CS_NO_ACK ; 
 int /*<<< orphan*/  ZD_CS_PS_POLL_FRAME ; 
 int /*<<< orphan*/  ZD_CS_RTS ; 
 int /*<<< orphan*/  ZD_CS_SELF_CTS ; 
 scalar_t__ ieee80211_is_pspoll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_set_control(struct zd_mac *mac, struct zd_ctrlset *cs,
	                   struct ieee80211_hdr *header,
	                   struct ieee80211_tx_info *info)
{
	/*
	 * CONTROL TODO:
	 * - if backoff needed, enable bit 0
	 * - if burst (backoff not needed) disable bit 0
	 */

	cs->control = 0;

	/* First fragment */
	if (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
		cs->control |= ZD_CS_NEED_RANDOM_BACKOFF;

	/* No ACK expected (multicast, etc.) */
	if (info->flags & IEEE80211_TX_CTL_NO_ACK)
		cs->control |= ZD_CS_NO_ACK;

	/* PS-POLL */
	if (ieee80211_is_pspoll(header->frame_control))
		cs->control |= ZD_CS_PS_POLL_FRAME;

	if (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
		cs->control |= ZD_CS_RTS;

	if (info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		cs->control |= ZD_CS_SELF_CTS;

	/* FIXME: Management frame? */
}