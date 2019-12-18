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
struct usb_ftdi {int disconnected; int /*<<< orphan*/ * bulk_in_buffer; int /*<<< orphan*/  ftdi_list; TYPE_1__* udev; } ;
struct kref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,struct usb_ftdi*) ; 
 int ftdi_instances ; 
 int /*<<< orphan*/  ftdi_module_lock ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct usb_ftdi* kref_to_usb_ftdi (struct kref*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_1__*) ; 

__attribute__((used)) static void ftdi_elan_delete(struct kref *kref)
{
        struct usb_ftdi *ftdi = kref_to_usb_ftdi(kref);
        dev_warn(&ftdi->udev->dev, "FREEING ftdi=%p\n", ftdi);
        usb_put_dev(ftdi->udev);
        ftdi->disconnected += 1;
        mutex_lock(&ftdi_module_lock);
        list_del_init(&ftdi->ftdi_list);
        ftdi_instances -= 1;
        mutex_unlock(&ftdi_module_lock);
        kfree(ftdi->bulk_in_buffer);
        ftdi->bulk_in_buffer = NULL;
}