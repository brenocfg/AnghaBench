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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_channel {int band; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_A_HT20 ; 
 int /*<<< orphan*/  CHANNEL_A_HT40MINUS ; 
 int /*<<< orphan*/  CHANNEL_A_HT40PLUS ; 
 int /*<<< orphan*/  CHANNEL_G_HT20 ; 
 int /*<<< orphan*/  CHANNEL_G_HT40MINUS ; 
 int /*<<< orphan*/  CHANNEL_G_HT40PLUS ; 
#define  IEEE80211_BAND_2GHZ 133 
#define  IEEE80211_BAND_5GHZ 132 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 

__attribute__((used)) static u32 ath9k_get_extchanmode(struct ieee80211_channel *chan,
				 enum nl80211_channel_type channel_type)
{
	u32 chanmode = 0;

	switch (chan->band) {
	case IEEE80211_BAND_2GHZ:
		switch (channel_type) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
			chanmode = CHANNEL_G_HT20;
			break;
		case NL80211_CHAN_HT40PLUS:
			chanmode = CHANNEL_G_HT40PLUS;
			break;
		case NL80211_CHAN_HT40MINUS:
			chanmode = CHANNEL_G_HT40MINUS;
			break;
		}
		break;
	case IEEE80211_BAND_5GHZ:
		switch (channel_type) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
			chanmode = CHANNEL_A_HT20;
			break;
		case NL80211_CHAN_HT40PLUS:
			chanmode = CHANNEL_A_HT40PLUS;
			break;
		case NL80211_CHAN_HT40MINUS:
			chanmode = CHANNEL_A_HT40MINUS;
			break;
		}
		break;
	default:
		break;
	}

	return chanmode;
}