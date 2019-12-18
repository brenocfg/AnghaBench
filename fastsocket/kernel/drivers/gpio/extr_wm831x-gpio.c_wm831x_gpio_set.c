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
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm831x_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct wm831x_gpio *wm831x_gpio = to_wm831x_gpio(chip);
	struct wm831x *wm831x = wm831x_gpio->wm831x;

	wm831x_set_bits(wm831x, WM831X_GPIO_LEVEL, 1 << offset,
			value << offset);
}