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
struct ieee80211_channel {int hw_value; int max_power; int max_antenna_gain; int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2x00lib_channel(struct ieee80211_channel *entry,
			      const int channel, const int tx_power,
			      const int value)
{
	/* XXX: this assumption about the band is wrong for 802.11j */
	entry->band = channel <= 14 ? IEEE80211_BAND_2GHZ : IEEE80211_BAND_5GHZ;
	entry->center_freq = ieee80211_channel_to_frequency(channel,
							    entry->band);
	entry->hw_value = value;
	entry->max_power = tx_power;
	entry->max_antenna_gain = 0xff;
}