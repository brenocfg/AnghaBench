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
typedef  int u8 ;
struct wl1271 {int fw_type; int last_vif_count; scalar_t__ state; int /*<<< orphan*/  mr_fw_name; int /*<<< orphan*/  flags; } ;
struct vif_counter_data {int counter; int /*<<< orphan*/  cur_vif_running; } ;
typedef  enum wl12xx_fw_type { ____Placeholder_wl12xx_fw_type } wl12xx_fw_type ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_VIF_CHANGE_IN_PROGRESS ; 
 int WL12XX_FW_TYPE_MULTI ; 
 int WL12XX_FW_TYPE_NORMAL ; 
 scalar_t__ WLCORE_STATE_OFF ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool wl12xx_need_fw_change(struct wl1271 *wl,
				  struct vif_counter_data vif_counter_data,
				  bool add)
{
	enum wl12xx_fw_type current_fw = wl->fw_type;
	u8 vif_count = vif_counter_data.counter;

	if (test_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags))
		return false;

	/* increase the vif count if this is a new vif */
	if (add && !vif_counter_data.cur_vif_running)
		vif_count++;

	wl->last_vif_count = vif_count;

	/* no need for fw change if the device is OFF */
	if (wl->state == WLCORE_STATE_OFF)
		return false;

	/* no need for fw change if a single fw is used */
	if (!wl->mr_fw_name)
		return false;

	if (vif_count > 1 && current_fw == WL12XX_FW_TYPE_NORMAL)
		return true;
	if (vif_count <= 1 && current_fw == WL12XX_FW_TYPE_MULTI)
		return true;

	return false;
}