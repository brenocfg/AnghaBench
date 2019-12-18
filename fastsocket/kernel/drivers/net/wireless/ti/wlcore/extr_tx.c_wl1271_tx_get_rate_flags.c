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
typedef  int u8 ;

/* Variables and functions */
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 

__attribute__((used)) static u8 wl1271_tx_get_rate_flags(u8 rate_class_index)
{
	u8 flags = 0;

	/*
	 * TODO: use wl12xx constants when this code is moved to wl12xx, as
	 * only it uses Tx-completion.
	 */
	if (rate_class_index <= 8)
		flags |= IEEE80211_TX_RC_MCS;

	/*
	 * TODO: use wl12xx constants when this code is moved to wl12xx, as
	 * only it uses Tx-completion.
	 */
	if (rate_class_index == 0)
		flags |= IEEE80211_TX_RC_SHORT_GI;

	return flags;
}