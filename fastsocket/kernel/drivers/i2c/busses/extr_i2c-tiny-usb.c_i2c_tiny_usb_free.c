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
struct i2c_tiny_usb {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct i2c_tiny_usb*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_tiny_usb_free(struct i2c_tiny_usb *dev)
{
	usb_put_dev(dev->usb_dev);
	kfree(dev);
}