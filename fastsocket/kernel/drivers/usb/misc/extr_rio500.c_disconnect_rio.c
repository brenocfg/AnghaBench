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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct rio_usb_data {int /*<<< orphan*/  lock; scalar_t__ present; int /*<<< orphan*/  obuf; int /*<<< orphan*/  ibuf; int /*<<< orphan*/ * rio_dev; scalar_t__ isopen; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct rio_usb_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_rio_class ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disconnect_rio(struct usb_interface *intf)
{
	struct rio_usb_data *rio = usb_get_intfdata (intf);

	usb_set_intfdata (intf, NULL);
	if (rio) {
		usb_deregister_dev(intf, &usb_rio_class);

		mutex_lock(&(rio->lock));
		if (rio->isopen) {
			rio->isopen = 0;
			/* better let it finish - the release will do whats needed */
			rio->rio_dev = NULL;
			mutex_unlock(&(rio->lock));
			return;
		}
		kfree(rio->ibuf);
		kfree(rio->obuf);

		dev_info(&intf->dev, "USB Rio disconnected.\n");

		rio->present = 0;
		mutex_unlock(&(rio->lock));
	}
}