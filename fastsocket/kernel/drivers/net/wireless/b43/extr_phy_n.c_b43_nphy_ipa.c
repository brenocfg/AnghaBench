#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* n; } ;
struct b43_wldev {TYPE_2__ phy; int /*<<< orphan*/  wl; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_3__ {scalar_t__ ipa5g_on; scalar_t__ ipa2g_on; } ;

/* Variables and functions */
 int IEEE80211_BAND_2GHZ ; 
 int IEEE80211_BAND_5GHZ ; 
 int b43_current_band (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool b43_nphy_ipa(struct b43_wldev *dev)
{
	enum ieee80211_band band = b43_current_band(dev->wl);
	return ((dev->phy.n->ipa2g_on && band == IEEE80211_BAND_2GHZ) ||
		(dev->phy.n->ipa5g_on && band == IEEE80211_BAND_5GHZ));
}