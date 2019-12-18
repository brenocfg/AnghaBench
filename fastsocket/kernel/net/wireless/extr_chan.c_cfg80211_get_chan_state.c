#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int iftype; TYPE_3__* wiphy; struct ieee80211_channel* channel; int /*<<< orphan*/  mesh_id_len; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  cac_started; TYPE_2__* current_bss; int /*<<< orphan*/  ibss_fixed; scalar_t__ netdev; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum cfg80211_chan_mode { ____Placeholder_cfg80211_chan_mode } cfg80211_chan_mode ;
struct TYPE_6__ {int features; } ;
struct TYPE_4__ {struct ieee80211_channel* channel; } ;
struct TYPE_5__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int CHAN_MODE_EXCLUSIVE ; 
 int CHAN_MODE_SHARED ; 
 int CHAN_MODE_UNDEFINED ; 
 int NL80211_FEATURE_P2P_DEVICE_NEEDS_CHANNEL ; 
#define  NL80211_IFTYPE_ADHOC 139 
#define  NL80211_IFTYPE_AP 138 
#define  NL80211_IFTYPE_AP_VLAN 137 
#define  NL80211_IFTYPE_MESH_POINT 136 
#define  NL80211_IFTYPE_MONITOR 135 
#define  NL80211_IFTYPE_P2P_CLIENT 134 
#define  NL80211_IFTYPE_P2P_DEVICE 133 
#define  NL80211_IFTYPE_P2P_GO 132 
#define  NL80211_IFTYPE_STATION 131 
#define  NL80211_IFTYPE_UNSPECIFIED 130 
#define  NL80211_IFTYPE_WDS 129 
#define  NUM_NL80211_IFTYPES 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  netif_running (scalar_t__) ; 

void
cfg80211_get_chan_state(struct wireless_dev *wdev,
		        struct ieee80211_channel **chan,
		        enum cfg80211_chan_mode *chanmode)
{
	*chan = NULL;
	*chanmode = CHAN_MODE_UNDEFINED;

	ASSERT_WDEV_LOCK(wdev);

	if (wdev->netdev && !netif_running(wdev->netdev))
		return;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_ADHOC:
		if (wdev->current_bss) {
			*chan = wdev->current_bss->pub.channel;
			*chanmode = wdev->ibss_fixed
				  ? CHAN_MODE_SHARED
				  : CHAN_MODE_EXCLUSIVE;
			return;
		}
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		if (wdev->current_bss) {
			*chan = wdev->current_bss->pub.channel;
			*chanmode = CHAN_MODE_SHARED;
			return;
		}
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
		if (wdev->cac_started) {
			*chan = wdev->channel;
			*chanmode = CHAN_MODE_SHARED;
		} else if (wdev->beacon_interval) {
			*chan = wdev->channel;
			*chanmode = CHAN_MODE_SHARED;
		}
		return;
	case NL80211_IFTYPE_MESH_POINT:
		if (wdev->mesh_id_len) {
			*chan = wdev->channel;
			*chanmode = CHAN_MODE_SHARED;
		}
		return;
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_WDS:
		/* these interface types don't really have a channel */
		return;
	case NL80211_IFTYPE_P2P_DEVICE:
		if (wdev->wiphy->features &
				NL80211_FEATURE_P2P_DEVICE_NEEDS_CHANNEL)
			*chanmode = CHAN_MODE_EXCLUSIVE;
		return;
	case NL80211_IFTYPE_UNSPECIFIED:
	case NUM_NL80211_IFTYPES:
		WARN_ON(1);
	}

	return;
}