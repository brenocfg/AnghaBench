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
struct wl12xx_vif {int hw_queue_base; } ;

/* Variables and functions */
#define  CONF_TX_AC_BE 131 
#define  CONF_TX_AC_BK 130 
#define  CONF_TX_AC_VI 129 
#define  CONF_TX_AC_VO 128 

__attribute__((used)) static inline
int wlcore_tx_get_mac80211_queue(struct wl12xx_vif *wlvif, int queue)
{
	int mac_queue = wlvif->hw_queue_base;

	switch (queue) {
	case CONF_TX_AC_VO:
		return mac_queue + 0;
	case CONF_TX_AC_VI:
		return mac_queue + 1;
	case CONF_TX_AC_BE:
		return mac_queue + 2;
	case CONF_TX_AC_BK:
		return mac_queue + 3;
	default:
		return mac_queue + 2;
	}
}