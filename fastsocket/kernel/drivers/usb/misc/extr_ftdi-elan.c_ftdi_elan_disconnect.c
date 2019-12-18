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
struct usb_interface {int minor; } ;
struct usb_ftdi {int disconnected; TYPE_1__* udev; scalar_t__ registered; scalar_t__ initialized; scalar_t__ enumerated; scalar_t__ synchronized; int /*<<< orphan*/  platform_dev; struct usb_class_driver* class; } ;
struct usb_class_driver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  command_queue ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftdi_command_cancel_work (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_elan_abandon_completions (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_elan_abandon_targets (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_elan_put_kref (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_response_cancel_work (struct usb_ftdi*) ; 
 int /*<<< orphan*/  ftdi_status_cancel_work (struct usb_ftdi*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  respond_queue ; 
 int /*<<< orphan*/  status_queue ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,struct usb_class_driver*) ; 
 struct usb_ftdi* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftdi_elan_disconnect(struct usb_interface *interface)
{
        struct usb_ftdi *ftdi = usb_get_intfdata(interface);
        ftdi->disconnected += 1;
        if (ftdi->class) {
                int minor = interface->minor;
                struct usb_class_driver *class = ftdi->class;
                usb_set_intfdata(interface, NULL);
                usb_deregister_dev(interface, class);
                dev_info(&ftdi->udev->dev, "USB FTDI U132 jtag interface on min"
                        "or %d now disconnected\n", minor);
        } else {
                ftdi_status_cancel_work(ftdi);
                ftdi_command_cancel_work(ftdi);
                ftdi_response_cancel_work(ftdi);
                ftdi_elan_abandon_completions(ftdi);
                ftdi_elan_abandon_targets(ftdi);
                if (ftdi->registered) {
                        platform_device_unregister(&ftdi->platform_dev);
                        ftdi->synchronized = 0;
                        ftdi->enumerated = 0;
                        ftdi->initialized = 0;
                        ftdi->registered = 0;
                }
                flush_workqueue(status_queue);
                flush_workqueue(command_queue);
                flush_workqueue(respond_queue);
                ftdi->disconnected += 1;
                usb_set_intfdata(interface, NULL);
                dev_info(&ftdi->udev->dev, "USB FTDI U132 host controller inter"
                        "face now disconnected\n");
        }
        ftdi_elan_put_kref(ftdi);
}