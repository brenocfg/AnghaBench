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
struct usb_lcd {struct usb_lcd* bulk_in_buffer; int /*<<< orphan*/  udev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_lcd*) ; 
 struct usb_lcd* to_lcd_dev (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcd_delete(struct kref *kref)
{
	struct usb_lcd *dev = to_lcd_dev(kref);

	usb_put_dev(dev->udev);
	kfree (dev->bulk_in_buffer);
	kfree (dev);
}