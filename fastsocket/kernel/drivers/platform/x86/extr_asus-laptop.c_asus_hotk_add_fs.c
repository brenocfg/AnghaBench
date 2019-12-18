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

/* Variables and functions */
 int /*<<< orphan*/  ASUS_SET_DEVICE_ATTR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bluetooth ; 
 scalar_t__ bt_switch_handle ; 
 int /*<<< orphan*/  display ; 
 scalar_t__ display_get_handle ; 
 scalar_t__ display_set_handle ; 
 int /*<<< orphan*/  gps ; 
 scalar_t__ gps_off_handle ; 
 scalar_t__ gps_on_handle ; 
 scalar_t__ gps_status_handle ; 
 int /*<<< orphan*/  infos ; 
 int /*<<< orphan*/  ledd ; 
 scalar_t__ ledd_set_handle ; 
 int /*<<< orphan*/  ls_level ; 
 scalar_t__ ls_level_handle ; 
 int /*<<< orphan*/  ls_switch ; 
 scalar_t__ ls_switch_handle ; 
 int /*<<< orphan*/ * show_bluetooth ; 
 int /*<<< orphan*/ * show_disp ; 
 int /*<<< orphan*/ * show_gps ; 
 int /*<<< orphan*/ * show_infos ; 
 int /*<<< orphan*/ * show_ledd ; 
 int /*<<< orphan*/ * show_lslvl ; 
 int /*<<< orphan*/ * show_lssw ; 
 int /*<<< orphan*/ * show_wlan ; 
 int /*<<< orphan*/ * store_bluetooth ; 
 int /*<<< orphan*/ * store_disp ; 
 int /*<<< orphan*/ * store_gps ; 
 int /*<<< orphan*/ * store_ledd ; 
 int /*<<< orphan*/ * store_lslvl ; 
 int /*<<< orphan*/ * store_lssw ; 
 int /*<<< orphan*/ * store_wlan ; 
 scalar_t__ wl_switch_handle ; 
 int /*<<< orphan*/  wlan ; 

__attribute__((used)) static void asus_hotk_add_fs(void)
{
	ASUS_SET_DEVICE_ATTR(infos, 0444, show_infos, NULL);

	if (wl_switch_handle)
		ASUS_SET_DEVICE_ATTR(wlan, 0644, show_wlan, store_wlan);

	if (bt_switch_handle)
		ASUS_SET_DEVICE_ATTR(bluetooth, 0644,
				     show_bluetooth, store_bluetooth);

	if (display_set_handle && display_get_handle)
		ASUS_SET_DEVICE_ATTR(display, 0644, show_disp, store_disp);
	else if (display_set_handle)
		ASUS_SET_DEVICE_ATTR(display, 0200, NULL, store_disp);

	if (ledd_set_handle)
		ASUS_SET_DEVICE_ATTR(ledd, 0644, show_ledd, store_ledd);

	if (ls_switch_handle && ls_level_handle) {
		ASUS_SET_DEVICE_ATTR(ls_level, 0644, show_lslvl, store_lslvl);
		ASUS_SET_DEVICE_ATTR(ls_switch, 0644, show_lssw, store_lssw);
	}

	if (gps_status_handle && gps_on_handle && gps_off_handle)
		ASUS_SET_DEVICE_ATTR(gps, 0644, show_gps, store_gps);
}