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
typedef  size_t u8 ;
struct ieee80211_tx_rate_control {TYPE_1__* hw; scalar_t__ rts; } ;
struct ieee80211_tx_rate {size_t count; int /*<<< orphan*/  flags; int /*<<< orphan*/  idx; } ;
struct ath_rate_table {TYPE_2__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy; int /*<<< orphan*/  ratecode; } ;
struct TYPE_3__ {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_USE_RTS_CTS ; 
 scalar_t__ WLAN_RC_PHY_40 (int /*<<< orphan*/ ) ; 
 scalar_t__ WLAN_RC_PHY_HT (int /*<<< orphan*/ ) ; 
 scalar_t__ WLAN_RC_PHY_SGI (int /*<<< orphan*/ ) ; 
 scalar_t__ conf_is_ht40 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath_rc_rate_set_series(const struct ath_rate_table *rate_table,
				   struct ieee80211_tx_rate *rate,
				   struct ieee80211_tx_rate_control *txrc,
				   u8 tries, u8 rix, int rtsctsenable)
{
	rate->count = tries;
	rate->idx = rate_table->info[rix].ratecode;

	if (txrc->rts || rtsctsenable)
		rate->flags |= IEEE80211_TX_RC_USE_RTS_CTS;

	if (WLAN_RC_PHY_HT(rate_table->info[rix].phy)) {
		rate->flags |= IEEE80211_TX_RC_MCS;
		if (WLAN_RC_PHY_40(rate_table->info[rix].phy) &&
		    conf_is_ht40(&txrc->hw->conf))
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		if (WLAN_RC_PHY_SGI(rate_table->info[rix].phy))
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;
	}
}