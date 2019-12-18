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
struct wm831x_gpio {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_GPIO_LEVEL ; 
 struct wm831x_gpio* to_wm831x_gpio (struct gpio_chip*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct wm831x_gpio *wm831x_gpio = to_wm831x_gpio(chip);
	struct wm831x *wm831x = wm831x_gpio->wm831x;
	int ret;

	ret = wm831x_reg_read(wm831x, WM831X_GPIO_LEVEL);
	if (ret < 0)
		return ret;

	if (ret & 1 << offset)
		return 1;
	else
		return 0;
}