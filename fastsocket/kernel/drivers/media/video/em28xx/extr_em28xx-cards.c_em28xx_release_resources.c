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
struct em28xx {int devno; int /*<<< orphan*/  udev; int /*<<< orphan*/  v4l2_dev; scalar_t__ ir; scalar_t__ sbutton_input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_deregister_snapshot_button (struct em28xx*) ; 
 int em28xx_devused ; 
 int /*<<< orphan*/  em28xx_i2c_unregister (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_ir_fini (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_release_analog_resources (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_remove_from_devlist (struct em28xx*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void em28xx_release_resources(struct em28xx *dev)
{
	if (dev->sbutton_input_dev)
		em28xx_deregister_snapshot_button(dev);

	if (dev->ir)
		em28xx_ir_fini(dev);

	/*FIXME: I2C IR should be disconnected */

	em28xx_release_analog_resources(dev);

	em28xx_remove_from_devlist(dev);

	em28xx_i2c_unregister(dev);

	v4l2_device_unregister(&dev->v4l2_dev);

	usb_put_dev(dev->udev);

	/* Mark device as unused */
	em28xx_devused &= ~(1 << dev->devno);
}