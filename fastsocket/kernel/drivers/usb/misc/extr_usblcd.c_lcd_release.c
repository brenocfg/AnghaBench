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
struct usb_lcd {int /*<<< orphan*/  kref; int /*<<< orphan*/  interface; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_delete ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcd_release(struct inode *inode, struct file *file)
{
	struct usb_lcd *dev;

	dev = (struct usb_lcd *)file->private_data;
	if (dev == NULL)
		return -ENODEV;

	/* decrement the count on our device */
	usb_autopm_put_interface(dev->interface);
	kref_put(&dev->kref, lcd_delete);
	return 0;
}