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
struct TYPE_2__ {int* bssid; } ;
struct ieee80211_device {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  get_random_bytes (int*,int /*<<< orphan*/ ) ; 

inline void ieee80211_randomize_cell(struct ieee80211_device *ieee)
{

	get_random_bytes(ieee->current_network.bssid, ETH_ALEN);

	/* an IBSS cell address must have the two less significant
	 * bits of the first byte = 2
	 */
	ieee->current_network.bssid[0] &= ~0x01;
	ieee->current_network.bssid[0] |= 0x02;
}