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
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct urb {TYPE_1__* dev; scalar_t__ setup_packet; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,...) ; 

__attribute__((used)) static int tweak_set_configuration_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;
	__u16 config;

	req = (struct usb_ctrlrequest *) urb->setup_packet;
	config = le16_to_cpu(req->wValue);

	/*
	 * I have never seen a multi-config device. Very rare.
	 * For most devices, this will be called to choose a default
	 * configuration only once in an initialization phase.
	 *
	 * set_configuration may change a device configuration and its device
	 * drivers will be unbound and assigned for a new device configuration.
	 * This means this usbip driver will be also unbound when called, then
	 * eventually reassigned to the device as far as driver matching
	 * condition is kept.
	 *
	 * Unfortunatelly, an existing usbip connection will be dropped
	 * due to this driver unbinding. So, skip here.
	 * A user may need to set a special configuration value before
	 * exporting the device.
	 */
	usbip_uinfo("set_configuration (%d) to %s\n", config,
						dev_name(&urb->dev->dev));
	usbip_uinfo("but, skip!\n");

	return 0;
	/* return usb_driver_set_configuration(urb->dev, config); */
}