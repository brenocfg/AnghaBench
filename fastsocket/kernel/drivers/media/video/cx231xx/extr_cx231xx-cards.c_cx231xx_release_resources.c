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
struct cx231xx {int devno; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_dev_uninit (struct cx231xx*) ; 
 int cx231xx_devused ; 
 int /*<<< orphan*/  cx231xx_ir_exit (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_release_analog_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_remove_from_devlist (struct cx231xx*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

void cx231xx_release_resources(struct cx231xx *dev)
{
	cx231xx_release_analog_resources(dev);

	cx231xx_remove_from_devlist(dev);

	/* Release I2C buses */
	cx231xx_dev_uninit(dev);

	cx231xx_ir_exit(dev);

	usb_put_dev(dev->udev);

	/* Mark device as unused */
	cx231xx_devused &= ~(1 << dev->devno);
}