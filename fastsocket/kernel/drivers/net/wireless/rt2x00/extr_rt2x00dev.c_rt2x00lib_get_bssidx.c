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
typedef  int u32 ;
struct rt2x00_dev {TYPE_1__* ops; scalar_t__ intf_sta_count; } ;
struct ieee80211_vif {int* addr; } ;
struct TYPE_2__ {int max_ap_intf; } ;

/* Variables and functions */

u32 rt2x00lib_get_bssidx(struct rt2x00_dev *rt2x00dev,
			 struct ieee80211_vif *vif)
{
	/*
	 * When in STA mode, bssidx is always 0 otherwise local_address[5]
	 * contains the bss number, see BSS_ID_MASK comments for details.
	 */
	if (rt2x00dev->intf_sta_count)
		return 0;
	return vif->addr[5] & (rt2x00dev->ops->max_ap_intf - 1);
}