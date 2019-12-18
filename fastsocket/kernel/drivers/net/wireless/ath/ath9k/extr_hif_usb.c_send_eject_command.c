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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {TYPE_1__* endpoint; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_eject_command(struct usb_interface *interface)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_host_interface *iface_desc = &interface->altsetting[0];
	struct usb_endpoint_descriptor *endpoint;
	unsigned char *cmd;
	u8 bulk_out_ep;
	int r;

	/* Find bulk out endpoint */
	for (r = 1; r >= 0; r--) {
		endpoint = &iface_desc->endpoint[r].desc;
		if (usb_endpoint_dir_out(endpoint) &&
		    usb_endpoint_xfer_bulk(endpoint)) {
			bulk_out_ep = endpoint->bEndpointAddress;
			break;
		}
	}
	if (r == -1) {
		dev_err(&udev->dev,
			"ath9k_htc: Could not find bulk out endpoint\n");
		return -ENODEV;
	}

	cmd = kzalloc(31, GFP_KERNEL);
	if (cmd == NULL)
		return -ENODEV;

	/* USB bulk command block */
	cmd[0] = 0x55;	/* bulk command signature */
	cmd[1] = 0x53;	/* bulk command signature */
	cmd[2] = 0x42;	/* bulk command signature */
	cmd[3] = 0x43;	/* bulk command signature */
	cmd[14] = 6;	/* command length */

	cmd[15] = 0x1b;	/* SCSI command: START STOP UNIT */
	cmd[19] = 0x2;	/* eject disc */

	dev_info(&udev->dev, "Ejecting storage device...\n");
	r = usb_bulk_msg(udev, usb_sndbulkpipe(udev, bulk_out_ep),
		cmd, 31, NULL, 2000);
	kfree(cmd);
	if (r)
		return r;

	/* At this point, the device disconnects and reconnects with the real
	 * ID numbers. */

	usb_set_intfdata(interface, NULL);
	return 0;
}