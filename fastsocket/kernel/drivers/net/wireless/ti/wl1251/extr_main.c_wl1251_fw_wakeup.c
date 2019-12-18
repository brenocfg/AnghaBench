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
typedef  int u32 ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int ELPCTRL_WAKE_UP ; 
 int ELPCTRL_WLAN_READY ; 
 int /*<<< orphan*/  HW_ACCESS_ELP_CTRL_REG_ADDR ; 
 int wl1251_read_elp (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 
 int /*<<< orphan*/  wl1251_write_elp (struct wl1251*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wl1251_fw_wakeup(struct wl1251 *wl)
{
	u32 elp_reg;

	elp_reg = ELPCTRL_WAKE_UP;
	wl1251_write_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR, elp_reg);
	elp_reg = wl1251_read_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);

	if (!(elp_reg & ELPCTRL_WLAN_READY))
		wl1251_warning("WLAN not ready");
}