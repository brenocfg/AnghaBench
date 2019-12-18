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
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wm831x*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_irq_exit (struct wm831x*) ; 
 int /*<<< orphan*/  wm831x_otp_exit (struct wm831x*) ; 

__attribute__((used)) static void wm831x_device_exit(struct wm831x *wm831x)
{
	wm831x_otp_exit(wm831x);
	mfd_remove_devices(wm831x->dev);
	wm831x_irq_exit(wm831x);
	kfree(wm831x);
}