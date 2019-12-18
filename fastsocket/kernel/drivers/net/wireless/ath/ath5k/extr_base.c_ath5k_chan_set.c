#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath5k_hw {TYPE_1__* curchan; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int ath5k_reset (struct ath5k_hw*,struct ieee80211_channel*,int) ; 

int
ath5k_chan_set(struct ath5k_hw *ah, struct ieee80211_channel *chan)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
		  "channel set, resetting (%u -> %u MHz)\n",
		  ah->curchan->center_freq, chan->center_freq);

	/*
	 * To switch channels clear any pending DMA operations;
	 * wait long enough for the RX fifo to drain, reset the
	 * hardware at the new frequency, and then re-enable
	 * the relevant bits of the h/w.
	 */
	return ath5k_reset(ah, chan, true);
}