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
typedef  size_t u8 ;
struct cfg80211_bss_ies {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {int /*<<< orphan*/  ies; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 size_t* cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,size_t const*) ; 
 scalar_t__ memcmp (size_t const*,size_t const*,size_t) ; 
 struct cfg80211_bss_ies* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_bss(struct cfg80211_bss *a, const u8 *bssid,
		   const u8 *ssid, size_t ssid_len)
{
	const struct cfg80211_bss_ies *ies;
	const u8 *ssidie;

	if (bssid && !ether_addr_equal(a->bssid, bssid))
		return false;

	if (!ssid)
		return true;

	ies = rcu_access_pointer(a->ies);
	if (!ies)
		return false;
	ssidie = cfg80211_find_ie(WLAN_EID_SSID, ies->data, ies->len);
	if (!ssidie)
		return false;
	if (ssidie[1] != ssid_len)
		return false;
	return memcmp(ssidie + 2, ssid, ssid_len) == 0;
}