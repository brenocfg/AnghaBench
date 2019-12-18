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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {int bss_type; int /*<<< orphan*/  p2p; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
#define  BSS_TYPE_AP_BSS 130 
#define  BSS_TYPE_IBSS 129 
#define  BSS_TYPE_STA_BSS 128 
 int /*<<< orphan*/  WL1271_ROLE_AP ; 
 int /*<<< orphan*/  WL1271_ROLE_IBSS ; 
 int /*<<< orphan*/  WL1271_ROLE_P2P_CL ; 
 int /*<<< orphan*/  WL1271_ROLE_P2P_GO ; 
 int /*<<< orphan*/  WL1271_ROLE_STA ; 
 int /*<<< orphan*/  WL12XX_INVALID_ROLE_TYPE ; 
 int /*<<< orphan*/  wl1271_error (char*,int) ; 

__attribute__((used)) static u8 wl12xx_get_role_type(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	switch (wlvif->bss_type) {
	case BSS_TYPE_AP_BSS:
		if (wlvif->p2p)
			return WL1271_ROLE_P2P_GO;
		else
			return WL1271_ROLE_AP;

	case BSS_TYPE_STA_BSS:
		if (wlvif->p2p)
			return WL1271_ROLE_P2P_CL;
		else
			return WL1271_ROLE_STA;

	case BSS_TYPE_IBSS:
		return WL1271_ROLE_IBSS;

	default:
		wl1271_error("invalid bss_type: %d", wlvif->bss_type);
	}
	return WL12XX_INVALID_ROLE_TYPE;
}