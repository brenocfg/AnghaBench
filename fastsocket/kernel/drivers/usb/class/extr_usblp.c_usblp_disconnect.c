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
struct usblp {int /*<<< orphan*/  used; int /*<<< orphan*/  mut; int /*<<< orphan*/  rwait; int /*<<< orphan*/  wwait; scalar_t__ present; int /*<<< orphan*/  dev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  dev_attr_ieee1284_id ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usblp* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usblp_class ; 
 int /*<<< orphan*/  usblp_cleanup (struct usblp*) ; 
 int /*<<< orphan*/  usblp_mutex ; 
 int /*<<< orphan*/  usblp_unlink_urbs (struct usblp*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usblp_disconnect(struct usb_interface *intf)
{
	struct usblp *usblp = usb_get_intfdata (intf);

	usb_deregister_dev(intf, &usblp_class);

	if (!usblp || !usblp->dev) {
		dev_err(&intf->dev, "bogus disconnect\n");
		BUG ();
	}

	device_remove_file(&intf->dev, &dev_attr_ieee1284_id);

	mutex_lock (&usblp_mutex);
	mutex_lock (&usblp->mut);
	usblp->present = 0;
	wake_up(&usblp->wwait);
	wake_up(&usblp->rwait);
	usb_set_intfdata (intf, NULL);

	usblp_unlink_urbs(usblp);
	mutex_unlock (&usblp->mut);

	if (!usblp->used)
		usblp_cleanup (usblp);
	mutex_unlock (&usblp_mutex);
}