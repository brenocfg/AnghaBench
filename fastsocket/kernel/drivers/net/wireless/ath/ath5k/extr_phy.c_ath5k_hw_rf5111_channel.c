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
typedef  int u32 ;
struct ieee80211_channel {scalar_t__ band; int /*<<< orphan*/  center_freq; } ;
struct ath5k_hw {int dummy; } ;
struct ath5k_athchan_2ghz {unsigned int a2_athchan; unsigned int a2_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_RF_BUFFER ; 
 int /*<<< orphan*/  AR5K_RF_BUFFER_CONTROL_3 ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int ath5k_hw_bitswap (unsigned int,int) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int ath5k_hw_rf5111_chan2athchan (unsigned int,struct ath5k_athchan_2ghz*) ; 
 unsigned int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_hw_rf5111_channel(struct ath5k_hw *ah,
		struct ieee80211_channel *channel)
{
	struct ath5k_athchan_2ghz ath5k_channel_2ghz;
	unsigned int ath5k_channel =
		ieee80211_frequency_to_channel(channel->center_freq);
	u32 data0, data1, clock;
	int ret;

	/*
	 * Set the channel on the RF5111 radio
	 */
	data0 = data1 = 0;

	if (channel->band == IEEE80211_BAND_2GHZ) {
		/* Map 2GHz channel to 5GHz Atheros channel ID */
		ret = ath5k_hw_rf5111_chan2athchan(
			ieee80211_frequency_to_channel(channel->center_freq),
			&ath5k_channel_2ghz);
		if (ret)
			return ret;

		ath5k_channel = ath5k_channel_2ghz.a2_athchan;
		data0 = ((ath5k_hw_bitswap(ath5k_channel_2ghz.a2_flags, 8) & 0xff)
		    << 5) | (1 << 4);
	}

	if (ath5k_channel < 145 || !(ath5k_channel & 1)) {
		clock = 1;
		data1 = ((ath5k_hw_bitswap(ath5k_channel - 24, 8) & 0xff) << 2) |
			(clock << 1) | (1 << 10) | 1;
	} else {
		clock = 0;
		data1 = ((ath5k_hw_bitswap((ath5k_channel - 24) / 2, 8) & 0xff)
			<< 2) | (clock << 1) | (1 << 10) | 1;
	}

	ath5k_hw_reg_write(ah, (data1 & 0xff) | ((data0 & 0xff) << 8),
			AR5K_RF_BUFFER);
	ath5k_hw_reg_write(ah, ((data1 >> 8) & 0xff) | (data0 & 0xff00),
			AR5K_RF_BUFFER_CONTROL_3);

	return 0;
}