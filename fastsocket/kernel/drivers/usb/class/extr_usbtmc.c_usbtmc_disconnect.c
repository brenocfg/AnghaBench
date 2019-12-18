#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbtmc_device_data {int zombie; int /*<<< orphan*/  kref; int /*<<< orphan*/  io_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  capability_attr_grp ; 
 int /*<<< orphan*/  data_attr_grp ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usbtmc_device_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbtmc_class ; 
 int /*<<< orphan*/  usbtmc_delete ; 

__attribute__((used)) static void usbtmc_disconnect(struct usb_interface *intf)
{
	struct usbtmc_device_data *data;

	dev_dbg(&intf->dev, "usbtmc_disconnect called\n");

	data = usb_get_intfdata(intf);
	usb_deregister_dev(intf, &usbtmc_class);
	sysfs_remove_group(&intf->dev.kobj, &capability_attr_grp);
	sysfs_remove_group(&intf->dev.kobj, &data_attr_grp);
	mutex_lock(&data->io_mutex);
	data->zombie = 1;
	mutex_unlock(&data->io_mutex);
	kref_put(&data->kref, usbtmc_delete);
}