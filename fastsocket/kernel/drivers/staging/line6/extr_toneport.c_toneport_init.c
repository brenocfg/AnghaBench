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
struct usb_line6 {struct usb_device* usbdev; } ;
struct usb_line6_toneport {int /*<<< orphan*/  firmware_version; int /*<<< orphan*/  serial_number; struct usb_line6 line6; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RETURN (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ LINE6_DEVID_GUITARPORT ; 
 int /*<<< orphan*/  dev_attr_led_green ; 
 int /*<<< orphan*/  dev_attr_led_red ; 
 int /*<<< orphan*/  device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_seconds () ; 
 int line6_init_audio (struct usb_line6*) ; 
 int line6_init_pcm (struct usb_line6*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_read_data (struct usb_line6*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  line6_read_serial_number (struct usb_line6*,int /*<<< orphan*/ *) ; 
 int line6_register_audio (struct usb_line6*) ; 
 int /*<<< orphan*/  line6_write_data (struct usb_line6*,int,int*,int) ; 
 int /*<<< orphan*/  toneport_destruct (struct usb_interface*) ; 
 int /*<<< orphan*/  toneport_pcm_properties ; 
 int /*<<< orphan*/  toneport_send_cmd (struct usb_device*,int,int) ; 
 int /*<<< orphan*/  toneport_update_led (int /*<<< orphan*/ *) ; 

int toneport_init(struct usb_interface *interface,
		  struct usb_line6_toneport *toneport)
{
	int err, ticks;
	struct usb_line6 *line6 = &toneport->line6;
	struct usb_device *usbdev;

	if ((interface == NULL) || (toneport == NULL))
		return -ENODEV;

	/* initialize audio system: */
	err = line6_init_audio(line6);
	if (err < 0) {
		toneport_destruct(interface);
		return err;
	}

	/* initialize PCM subsystem: */
	err = line6_init_pcm(line6, &toneport_pcm_properties);
	if (err < 0) {
		toneport_destruct(interface);
		return err;
	}

	/* register audio system: */
	err = line6_register_audio(line6);
	if (err < 0) {
		toneport_destruct(interface);
		return err;
	}

	usbdev = line6->usbdev;
	line6_read_serial_number(line6, &toneport->serial_number);
	line6_read_data(line6, 0x80c2, &toneport->firmware_version, 1);

	/* sync time on device with host: */
	ticks = (int)get_seconds();
	line6_write_data(line6, 0x80c6, &ticks, 4);

	/*
	seems to work without the first two...
	*/
	/* toneport_send_cmd(usbdev, 0x0201, 0x0002); */
	/* toneport_send_cmd(usbdev, 0x0801, 0x0000); */
	/* only one that works for me; on GP, TP might be different? */
	toneport_send_cmd(usbdev, 0x0301, 0x0000);

	if (usbdev->descriptor.idProduct != LINE6_DEVID_GUITARPORT) {
		CHECK_RETURN(device_create_file(&interface->dev, &dev_attr_led_red));
		CHECK_RETURN(device_create_file(&interface->dev, &dev_attr_led_green));
		toneport_update_led(&usbdev->dev);
	}

	return 0;
}