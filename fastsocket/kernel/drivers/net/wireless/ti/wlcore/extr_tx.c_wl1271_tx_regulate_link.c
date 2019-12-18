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
typedef  size_t u8 ;
struct wl12xx_vif {unsigned long* links_map; } ;
struct wl1271 {int active_link_count; TYPE_1__* links; int /*<<< orphan*/  ap_fw_ps_map; } ;
struct TYPE_2__ {size_t allocated_pkts; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 size_t WL1271_PS_STA_MAX_PACKETS ; 
 int test_bit (size_t,unsigned long*) ; 
 int /*<<< orphan*/  wl12xx_ps_link_start (struct wl1271*,struct wl12xx_vif*,size_t,int) ; 

__attribute__((used)) static void wl1271_tx_regulate_link(struct wl1271 *wl,
				    struct wl12xx_vif *wlvif,
				    u8 hlid)
{
	bool fw_ps;
	u8 tx_pkts;

	if (WARN_ON(!test_bit(hlid, wlvif->links_map)))
		return;

	fw_ps = test_bit(hlid, (unsigned long *)&wl->ap_fw_ps_map);
	tx_pkts = wl->links[hlid].allocated_pkts;

	/*
	 * if in FW PS and there is enough data in FW we can put the link
	 * into high-level PS and clean out its TX queues.
	 * Make an exception if this is the only connected link. In this
	 * case FW-memory congestion is less of a problem.
	 * Note that a single connected STA means 3 active links, since we must
	 * account for the global and broadcast AP links. The "fw_ps" check
	 * assures us the third link is a STA connected to the AP. Otherwise
	 * the FW would not set the PSM bit.
	 */
	if (wl->active_link_count > 3 && fw_ps &&
	    tx_pkts >= WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_start(wl, wlvif, hlid, true);
}