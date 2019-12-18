#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_interface {int num_altsetting; int needs_remote_wakeup; int /*<<< orphan*/  dev; TYPE_4__* cur_altsetting; TYPE_2__* altsetting; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct hso_shared_int {int dummy; } ;
struct hso_device {int dummy; } ;
struct TYPE_7__ {int bInterfaceClass; } ;
struct TYPE_8__ {TYPE_3__ desc; } ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
#define  HSO_INTF_BULK 129 
 int HSO_INTF_MASK ; 
#define  HSO_INTF_MUX 128 
 int HSO_PORT_MASK ; 
 int HSO_PORT_NETWORK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disable_net ; 
 struct hso_device* hso_create_bulk_serial_device (struct usb_interface*,int) ; 
 struct hso_device* hso_create_mux_serial_device (struct usb_interface*,int,struct hso_shared_int*) ; 
 struct hso_device* hso_create_net_device (struct usb_interface*,int) ; 
 struct hso_shared_int* hso_create_shared_int (struct usb_interface*) ; 
 int /*<<< orphan*/  hso_free_interface (struct usb_interface*) ; 
 int hso_get_config_data (struct usb_interface*) ; 
 int /*<<< orphan*/  hso_get_mux_ports (struct usb_interface*,unsigned char*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct hso_device*) ; 

__attribute__((used)) static int hso_probe(struct usb_interface *interface,
		     const struct usb_device_id *id)
{
	int mux, i, if_num, port_spec;
	unsigned char port_mask;
	struct hso_device *hso_dev = NULL;
	struct hso_shared_int *shared_int;
	struct hso_device *tmp_dev = NULL;

	if_num = interface->altsetting->desc.bInterfaceNumber;

	/* Get the interface/port specification from either driver_info or from
	 * the device itself */
	if (id->driver_info)
		port_spec = ((u32 *)(id->driver_info))[if_num];
	else
		port_spec = hso_get_config_data(interface);

	if (interface->cur_altsetting->desc.bInterfaceClass != 0xFF) {
		dev_err(&interface->dev, "Not our interface\n");
		return -ENODEV;
	}
	/* Check if we need to switch to alt interfaces prior to port
	 * configuration */
	if (interface->num_altsetting > 1)
		usb_set_interface(interface_to_usbdev(interface), if_num, 1);
	interface->needs_remote_wakeup = 1;

	/* Allocate new hso device(s) */
	switch (port_spec & HSO_INTF_MASK) {
	case HSO_INTF_MUX:
		if ((port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK) {
			/* Create the network device */
			if (!disable_net) {
				hso_dev = hso_create_net_device(interface,
								port_spec);
				if (!hso_dev)
					goto exit;
				tmp_dev = hso_dev;
			}
		}

		if (hso_get_mux_ports(interface, &port_mask))
			/* TODO: de-allocate everything */
			goto exit;

		shared_int = hso_create_shared_int(interface);
		if (!shared_int)
			goto exit;

		for (i = 1, mux = 0; i < 0x100; i = i << 1, mux++) {
			if (port_mask & i) {
				hso_dev = hso_create_mux_serial_device(
						interface, i, shared_int);
				if (!hso_dev)
					goto exit;
			}
		}

		if (tmp_dev)
			hso_dev = tmp_dev;
		break;

	case HSO_INTF_BULK:
		/* It's a regular bulk interface */
		if (((port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK)
		    && !disable_net)
			hso_dev = hso_create_net_device(interface, port_spec);
		else
			hso_dev =
			    hso_create_bulk_serial_device(interface, port_spec);
		if (!hso_dev)
			goto exit;
		break;
	default:
		goto exit;
	}

	/* save our data pointer in this device */
	usb_set_intfdata(interface, hso_dev);

	/* done */
	return 0;
exit:
	hso_free_interface(interface);
	return -ENODEV;
}