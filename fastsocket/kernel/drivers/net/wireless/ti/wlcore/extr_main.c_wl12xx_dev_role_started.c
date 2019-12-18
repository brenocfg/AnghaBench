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
struct wl12xx_vif {scalar_t__ dev_hlid; } ;

/* Variables and functions */
 scalar_t__ WL12XX_INVALID_LINK_ID ; 

__attribute__((used)) static bool wl12xx_dev_role_started(struct wl12xx_vif *wlvif)
{
	return wlvif->dev_hlid != WL12XX_INVALID_LINK_ID;
}