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
struct wl12xx_vif {scalar_t__ role_id; int /*<<< orphan*/  channel; int /*<<< orphan*/  band; } ;
struct wl1271 {int /*<<< orphan*/  roc_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 scalar_t__ WL12XX_MAX_ROLES ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl12xx_roc (struct wl1271*,struct wl12xx_vif*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlcore_roc_if_possible(struct wl1271 *wl,
				   struct wl12xx_vif *wlvif)
{
	if (find_first_bit(wl->roc_map,
			   WL12XX_MAX_ROLES) < WL12XX_MAX_ROLES)
		return;

	if (WARN_ON(wlvif->role_id == WL12XX_INVALID_ROLE_ID))
		return;

	wl12xx_roc(wl, wlvif, wlvif->role_id, wlvif->band, wlvif->channel);
}