#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_supported_band {unsigned int n_bitrates; TYPE_5__* bitrates; } ;
struct ieee80211_rx_status {int rate_idx; int /*<<< orphan*/  flag; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct TYPE_8__ {TYPE_2__ chandef; } ;
struct ieee80211_hw {TYPE_4__* wiphy; TYPE_3__ conf; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_10__ {int hw_value; int hw_value_short; } ;
struct TYPE_9__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int ATH9K_RX_2040 ; 
 int ATH9K_RX_GI ; 
 int /*<<< orphan*/  RX_FLAG_40MHZ ; 
 int /*<<< orphan*/  RX_FLAG_HT ; 
 int /*<<< orphan*/  RX_FLAG_SHORTPRE ; 
 int /*<<< orphan*/  RX_FLAG_SHORT_GI ; 

__attribute__((used)) static void ath9k_process_rate(struct ieee80211_hw *hw,
			       struct ieee80211_rx_status *rxs,
			       u8 rx_rate, u8 rs_flags)
{
	struct ieee80211_supported_band *sband;
	enum ieee80211_band band;
	unsigned int i = 0;

	if (rx_rate & 0x80) {
		/* HT rate */
		rxs->flag |= RX_FLAG_HT;
		if (rs_flags & ATH9K_RX_2040)
			rxs->flag |= RX_FLAG_40MHZ;
		if (rs_flags & ATH9K_RX_GI)
			rxs->flag |= RX_FLAG_SHORT_GI;
		rxs->rate_idx = rx_rate & 0x7f;
		return;
	}

	band = hw->conf.chandef.chan->band;
	sband = hw->wiphy->bands[band];

	for (i = 0; i < sband->n_bitrates; i++) {
		if (sband->bitrates[i].hw_value == rx_rate) {
			rxs->rate_idx = i;
			return;
		}
		if (sband->bitrates[i].hw_value_short == rx_rate) {
			rxs->rate_idx = i;
			rxs->flag |= RX_FLAG_SHORTPRE;
			return;
		}
	}

}