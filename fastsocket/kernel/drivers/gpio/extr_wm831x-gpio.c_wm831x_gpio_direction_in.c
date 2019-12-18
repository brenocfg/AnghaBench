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
 unsigned int WM831X_GPIO1_CONTROL ; 
 int WM831X_GPN_DIR ; 
 int WM831X_GPN_TRI ; 
 struct wm831x_gpio* to_wm831x_gpio (struct gpio_chip*) ; 
 int wm831x_set_bits (struct wm831x*,unsigned int,int,int) ; 

__attribute__((used)) static int wm831x_gpio_direction_in(struct gpio_chip *chip, unsigned offset)
{
	struct wm831x_gpio *wm831x_gpio = to_wm831x_gpio(chip);
	struct wm831x *wm831x = wm831x_gpio->wm831x;

	return wm831x_set_bits(wm831x, WM831X_GPIO1_CONTROL + offset,
			       WM831X_GPN_DIR | WM831X_GPN_TRI,
			       WM831X_GPN_DIR);
}