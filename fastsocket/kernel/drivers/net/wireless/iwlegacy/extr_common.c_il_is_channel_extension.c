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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int dummy; } ;
struct il_channel_info {int ht40_extension_channel; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 scalar_t__ IEEE80211_HT_PARAM_CHA_SEC_ABOVE ; 
 scalar_t__ IEEE80211_HT_PARAM_CHA_SEC_BELOW ; 
 struct il_channel_info* il_get_channel_info (struct il_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_is_channel_valid (struct il_channel_info const*) ; 

__attribute__((used)) static bool
il_is_channel_extension(struct il_priv *il, enum ieee80211_band band,
			u16 channel, u8 extension_chan_offset)
{
	const struct il_channel_info *ch_info;

	ch_info = il_get_channel_info(il, band, channel);
	if (!il_is_channel_valid(ch_info))
		return false;

	if (extension_chan_offset == IEEE80211_HT_PARAM_CHA_SEC_ABOVE)
		return !(ch_info->
			 ht40_extension_channel & IEEE80211_CHAN_NO_HT40PLUS);
	else if (extension_chan_offset == IEEE80211_HT_PARAM_CHA_SEC_BELOW)
		return !(ch_info->
			 ht40_extension_channel & IEEE80211_CHAN_NO_HT40MINUS);

	return false;
}