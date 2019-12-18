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
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WLCORE_CHAN_HT20 ; 
 int WLCORE_CHAN_HT40MINUS ; 
 int WLCORE_CHAN_HT40PLUS ; 
 int WLCORE_CHAN_NO_HT ; 

__attribute__((used)) static u8 wlcore_get_native_channel_type(u8 nl_channel_type)
{
	switch (nl_channel_type) {
	case NL80211_CHAN_NO_HT:
		return WLCORE_CHAN_NO_HT;
	case NL80211_CHAN_HT20:
		return WLCORE_CHAN_HT20;
	case NL80211_CHAN_HT40MINUS:
		return WLCORE_CHAN_HT40MINUS;
	case NL80211_CHAN_HT40PLUS:
		return WLCORE_CHAN_HT40PLUS;
	default:
		WARN_ON(1);
		return WLCORE_CHAN_NO_HT;
	}
}