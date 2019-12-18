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
struct ieee80211_network {scalar_t__ ssid_len; scalar_t__ channel; int capability; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {scalar_t__ iw_mode; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ IW_MODE_INFRA ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int is_same_network(struct ieee80211_network *src,
                                  struct ieee80211_network *dst,
				  struct ieee80211_device *ieee)
{
        /* A network is only a duplicate if the channel, BSSID, ESSID
         * and the capability field (in particular IBSS and BSS) all match.
         * We treat all <hidden> with the same BSSID and channel
         * as one network */
        return (((src->ssid_len == dst->ssid_len)||(ieee->iw_mode == IW_MODE_INFRA)) &&  //YJ,mod, 080819,for hidden ap
			//((src->ssid_len == dst->ssid_len) &&
			(src->channel == dst->channel) &&
			!memcmp(src->bssid, dst->bssid, ETH_ALEN) &&
			(!memcmp(src->ssid, dst->ssid, src->ssid_len)||(ieee->iw_mode == IW_MODE_INFRA)) &&  //YJ,mod, 080819,for hidden ap
			//!memcmp(src->ssid, dst->ssid, src->ssid_len) &&
			((src->capability & WLAN_CAPABILITY_IBSS) ==
			(dst->capability & WLAN_CAPABILITY_IBSS)) &&
			((src->capability & WLAN_CAPABILITY_BSS) ==
			(dst->capability & WLAN_CAPABILITY_BSS)));
}