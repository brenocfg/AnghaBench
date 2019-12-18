#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* adapter; int /*<<< orphan*/  generic_bulk_ctrl_endpoint; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; TYPE_3__ props; int /*<<< orphan*/  udev; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; struct dvb_usb_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  endpoint; } ;
struct TYPE_5__ {TYPE_1__ stream; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cxusb_d680_dmb_drain_message (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  cxusb_d680_dmb_drain_video (struct dvb_usb_device*) ; 
 scalar_t__ cxusb_d680_dmb_gpio_tuner (struct dvb_usb_device*,int,int) ; 
 int /*<<< orphan*/  d680_lgs8gl5_cfg ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  lgs8gxx_attach ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_d680_dmb_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap->dev;
	int n;

	/* Select required USB configuration */
	if (usb_set_interface(d->udev, 0, 0) < 0)
		err("set interface failed");

	/* Unblock all USB pipes */
	usb_clear_halt(d->udev,
		usb_sndbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoint));
	usb_clear_halt(d->udev,
		usb_rcvbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoint));
	usb_clear_halt(d->udev,
		usb_rcvbulkpipe(d->udev, d->props.adapter[0].stream.endpoint));

	/* Drain USB pipes to avoid hang after reboot */
	for (n = 0;  n < 5;  n++) {
		cxusb_d680_dmb_drain_message(d);
		cxusb_d680_dmb_drain_video(d);
		msleep(200);
	}

	/* Reset the tuner */
	if (cxusb_d680_dmb_gpio_tuner(d, 0x07, 0) < 0) {
		err("clear tuner gpio failed");
		return -EIO;
	}
	msleep(100);
	if (cxusb_d680_dmb_gpio_tuner(d, 0x07, 1) < 0) {
		err("set tuner gpio failed");
		return -EIO;
	}
	msleep(100);

	/* Attach frontend */
	adap->fe = dvb_attach(lgs8gxx_attach, &d680_lgs8gl5_cfg, &d->i2c_adap);
	if (adap->fe == NULL)
		return -EIO;

	return 0;
}