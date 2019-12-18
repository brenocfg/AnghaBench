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
typedef  int /*<<< orphan*/  u16 ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_SYSTEM_CONTROL_2 ; 
 int /*<<< orphan*/  WM8350_WDOG_TO_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_mutex ; 
 int /*<<< orphan*/  wm8350_reg_lock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_unlock (struct wm8350*) ; 
 int wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_wdt_set_timeout(struct wm8350 *wm8350, u16 value)
{
	int ret;
	u16 reg;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_read(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_TO_MASK;
	reg |= value;
	ret = wm8350_reg_write(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	return ret;
}