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
struct TYPE_4__ {int skip_table; TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct ieee80211_supported_band {scalar_t__ band; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int max_rate_tries; } ;
struct TYPE_3__ {int count; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_NO_CCK_RATE ; 
 int /*<<< orphan*/  rate_lowest_index (struct ieee80211_supported_band*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rate_lowest_non_cck_index (struct ieee80211_supported_band*,struct ieee80211_sta*) ; 

__attribute__((used)) static void __rate_control_send_low(struct ieee80211_hw *hw,
				    struct ieee80211_supported_band *sband,
				    struct ieee80211_sta *sta,
				    struct ieee80211_tx_info *info)
{
	if ((sband->band != IEEE80211_BAND_2GHZ) ||
	    !(info->flags & IEEE80211_TX_CTL_NO_CCK_RATE))
		info->control.rates[0].idx = rate_lowest_index(sband, sta);
	else
		info->control.rates[0].idx =
			rate_lowest_non_cck_index(sband, sta);

	info->control.rates[0].count =
		(info->flags & IEEE80211_TX_CTL_NO_ACK) ?
		1 : hw->max_rate_tries;

	info->control.skip_table = 1;
}