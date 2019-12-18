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
typedef  int u16 ;
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM831X_WATCHDOG ; 
 int WM831X_WDOG_RESET ; 
 int WM831X_WDOG_RST_SRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ update_gpio ; 
 int update_state ; 
 int /*<<< orphan*/  wdt_mutex ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_wdt_kick(struct wm831x *wm831x)
{
	int ret;
	u16 reg;

	mutex_lock(&wdt_mutex);

	if (update_gpio) {
		gpio_set_value_cansleep(update_gpio, update_state);
		update_state = !update_state;
		ret = 0;
		goto out;
	}


	reg = wm831x_reg_read(wm831x, WM831X_WATCHDOG);

	if (!(reg & WM831X_WDOG_RST_SRC)) {
		dev_err(wm831x->dev, "Hardware watchdog update unsupported\n");
		ret = -EINVAL;
		goto out;
	}

	reg |= WM831X_WDOG_RESET;

	ret = wm831x_reg_unlock(wm831x);
	if (ret == 0) {
		ret = wm831x_reg_write(wm831x, WM831X_WATCHDOG, reg);
		wm831x_reg_lock(wm831x);
	} else {
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	}

out:
	mutex_unlock(&wdt_mutex);

	return ret;
}