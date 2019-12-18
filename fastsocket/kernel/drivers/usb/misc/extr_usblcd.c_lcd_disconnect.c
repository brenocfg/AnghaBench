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
struct usb_lcd {int /*<<< orphan*/  kref; } ;
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_class ; 
 int /*<<< orphan*/  lcd_delete ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_disc_mutex ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_lcd* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lcd_disconnect(struct usb_interface *interface)
{
	struct usb_lcd *dev;
        int minor = interface->minor;

	mutex_lock(&open_disc_mutex);
        dev = usb_get_intfdata(interface);
        usb_set_intfdata(interface, NULL);
	mutex_unlock(&open_disc_mutex);

        /* give back our minor */
        usb_deregister_dev(interface, &lcd_class);
 
	/* decrement our usage count */
	kref_put(&dev->kref, lcd_delete);

	dev_info(&interface->dev, "USB LCD #%d now disconnected\n", minor);
}