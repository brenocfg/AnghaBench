#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct cm109_dev {int /*<<< orphan*/  pm_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_stop_traffic (struct cm109_dev*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cm109_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int cm109_usb_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct cm109_dev *dev = usb_get_intfdata(intf);

	dev_info(&intf->dev, "cm109: usb_suspend (event=%d)\n", message.event);

	mutex_lock(&dev->pm_mutex);
	cm109_stop_traffic(dev);
	mutex_unlock(&dev->pm_mutex);

	return 0;
}