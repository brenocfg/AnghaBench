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
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SLOT_TIME ; 
 int /*<<< orphan*/  RTS_THRESHOLD_DEF ; 
 int wl1251_acx_group_address_tbl (struct wl1251*) ; 
 int wl1251_acx_pd_threshold (struct wl1251*) ; 
 int wl1251_acx_rts_threshold (struct wl1251*,int /*<<< orphan*/ ) ; 
 int wl1251_acx_service_period_timeout (struct wl1251*) ; 
 int wl1251_acx_slot (struct wl1251*,int /*<<< orphan*/ ) ; 

int wl1251_hw_init_phy_config(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_acx_pd_threshold(wl);
	if (ret < 0)
		return ret;

	ret = wl1251_acx_slot(wl, DEFAULT_SLOT_TIME);
	if (ret < 0)
		return ret;

	ret = wl1251_acx_group_address_tbl(wl);
	if (ret < 0)
		return ret;

	ret = wl1251_acx_service_period_timeout(wl);
	if (ret < 0)
		return ret;

	ret = wl1251_acx_rts_threshold(wl, RTS_THRESHOLD_DEF);
	if (ret < 0)
		return ret;

	return 0;
}