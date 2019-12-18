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
struct ieee80211_sta {scalar_t__ bandwidth; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 

__attribute__((used)) static bool iwl_is_ht40_tx_allowed(struct ieee80211_sta *sta)
{
	return sta->bandwidth >= IEEE80211_STA_RX_BW_40;
}