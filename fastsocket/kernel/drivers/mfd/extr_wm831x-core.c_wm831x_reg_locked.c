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
struct wm831x {int /*<<< orphan*/  locked; } ;

/* Variables and functions */
#define  WM831X_BACKUP_CHARGER_CONTROL 133 
#define  WM831X_CHARGER_CONTROL_1 132 
#define  WM831X_CHARGER_CONTROL_2 131 
#define  WM831X_DC4_CONTROL 130 
#define  WM831X_ON_PIN_CONTROL 129 
#define  WM831X_WATCHDOG 128 

__attribute__((used)) static int wm831x_reg_locked(struct wm831x *wm831x, unsigned short reg)
{
	if (!wm831x->locked)
		return 0;

	switch (reg) {
	case WM831X_WATCHDOG:
	case WM831X_DC4_CONTROL:
	case WM831X_ON_PIN_CONTROL:
	case WM831X_BACKUP_CHARGER_CONTROL:
	case WM831X_CHARGER_CONTROL_1:
	case WM831X_CHARGER_CONTROL_2:
		return 1;

	default:
		return 0;
	}
}