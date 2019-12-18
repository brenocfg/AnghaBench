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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ieee80211_hdr {scalar_t__* addr3; scalar_t__* addr2; } ;
struct atmel_private {int BSS_list_entries; TYPE_1__* BSSinfo; } ;
struct TYPE_2__ {scalar_t__ RSSI; int beacon_period; int UsingWEP; int /*<<< orphan*/  preamble; int /*<<< orphan*/  BSStype; scalar_t__ SSIDsize; int /*<<< orphan*/  SSID; scalar_t__ channel; int /*<<< orphan*/  BSSID; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  LONG_PREAMBLE ; 
 int MAX_BSS_ENTRIES ; 
 int /*<<< orphan*/  SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void store_bss_info(struct atmel_private *priv,
			   struct ieee80211_hdr *header, u16 capability,
			   u16 beacon_period, u8 channel, u8 rssi, u8 ssid_len,
			   u8 *ssid, int is_beacon)
{
	u8 *bss = capability & WLAN_CAPABILITY_ESS ? header->addr2 : header->addr3;
	int i, index;

	for (index = -1, i = 0; i < priv->BSS_list_entries; i++)
		if (memcmp(bss, priv->BSSinfo[i].BSSID, 6) == 0)
			index = i;

	/* If we process a probe and an entry from this BSS exists
	   we will update the BSS entry with the info from this BSS.
	   If we process a beacon we will only update RSSI */

	if (index == -1) {
		if (priv->BSS_list_entries == MAX_BSS_ENTRIES)
			return;
		index = priv->BSS_list_entries++;
		memcpy(priv->BSSinfo[index].BSSID, bss, 6);
		priv->BSSinfo[index].RSSI = rssi;
	} else {
		if (rssi > priv->BSSinfo[index].RSSI)
			priv->BSSinfo[index].RSSI = rssi;
		if (is_beacon)
			return;
	}

	priv->BSSinfo[index].channel = channel;
	priv->BSSinfo[index].beacon_period = beacon_period;
	priv->BSSinfo[index].UsingWEP = capability & WLAN_CAPABILITY_PRIVACY;
	memcpy(priv->BSSinfo[index].SSID, ssid, ssid_len);
	priv->BSSinfo[index].SSIDsize = ssid_len;

	if (capability & WLAN_CAPABILITY_IBSS)
		priv->BSSinfo[index].BSStype = IW_MODE_ADHOC;
	else if (capability & WLAN_CAPABILITY_ESS)
		priv->BSSinfo[index].BSStype = IW_MODE_INFRA;

	priv->BSSinfo[index].preamble = capability & WLAN_CAPABILITY_SHORT_PREAMBLE ?
		SHORT_PREAMBLE : LONG_PREAMBLE;
}