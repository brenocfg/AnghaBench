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
struct cfg80211_scan_request {TYPE_1__** channels; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  PHY_BAND_24 ; 
 int /*<<< orphan*/  PHY_BAND_5 ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le32
iwl_mvm_scan_rxon_flags(struct cfg80211_scan_request *req)
{
	if (req->channels[0]->band == IEEE80211_BAND_2GHZ)
		return cpu_to_le32(PHY_BAND_24);
	else
		return cpu_to_le32(PHY_BAND_5);
}