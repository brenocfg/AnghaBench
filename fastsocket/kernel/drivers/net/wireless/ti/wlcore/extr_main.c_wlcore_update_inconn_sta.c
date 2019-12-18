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
struct wl12xx_vif {scalar_t__ inconn_count; int /*<<< orphan*/  role_id; } ;
struct wl1271_station {int in_connection; } ;
struct wl1271 {int /*<<< orphan*/  roc_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl12xx_croc (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_roc_if_possible (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static void wlcore_update_inconn_sta(struct wl1271 *wl,
				     struct wl12xx_vif *wlvif,
				     struct wl1271_station *wl_sta,
				     bool in_connection)
{
	if (in_connection) {
		if (WARN_ON(wl_sta->in_connection))
			return;
		wl_sta->in_connection = true;
		if (!wlvif->inconn_count++)
			wlcore_roc_if_possible(wl, wlvif);
	} else {
		if (!wl_sta->in_connection)
			return;

		wl_sta->in_connection = false;
		wlvif->inconn_count--;
		if (WARN_ON(wlvif->inconn_count < 0))
			return;

		if (!wlvif->inconn_count)
			if (test_bit(wlvif->role_id, wl->roc_map))
				wl12xx_croc(wl, wlvif->role_id);
	}
}