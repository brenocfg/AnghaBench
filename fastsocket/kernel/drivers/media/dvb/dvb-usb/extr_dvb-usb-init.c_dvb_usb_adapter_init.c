#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_adapters; scalar_t__ generic_bulk_ctrl_endpoint; int /*<<< orphan*/ * adapter; } ;
struct dvb_usb_device {TYPE_1__ props; TYPE_2__* udev; int /*<<< orphan*/  state; int /*<<< orphan*/  num_adapters_initialized; struct dvb_usb_adapter* adapter; } ;
struct dvb_usb_adapter_properties {int dummy; } ;
struct TYPE_8__ {int caps; int pid_filter_count; scalar_t__ size_of_priv; } ;
struct dvb_usb_adapter {int id; int pid_filtering; int max_feed_count; int /*<<< orphan*/ * priv; TYPE_5__ props; struct dvb_usb_device* dev; } ;
struct TYPE_7__ {scalar_t__ speed; } ;

/* Variables and functions */
 int DVB_USB_ADAP_HAS_PID_FILTER ; 
 int DVB_USB_ADAP_NEED_PID_FILTERING ; 
 int /*<<< orphan*/  DVB_USB_STATE_DVB ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_SPEED_FULL ; 
 int dvb_usb_adapter_dvb_init (struct dvb_usb_adapter*,short*) ; 
 int dvb_usb_adapter_frontend_init (struct dvb_usb_adapter*) ; 
 int dvb_usb_adapter_stream_init (struct dvb_usb_adapter*) ; 
 scalar_t__ dvb_usb_force_pid_filter_usage ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_clear_halt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int dvb_usb_adapter_init(struct dvb_usb_device *d, short *adapter_nrs)
{
	struct dvb_usb_adapter *adap;
	int ret, n;

	for (n = 0; n < d->props.num_adapters; n++) {
		adap = &d->adapter[n];
		adap->dev = d;
		adap->id  = n;

		memcpy(&adap->props, &d->props.adapter[n], sizeof(struct dvb_usb_adapter_properties));

		/* speed - when running at FULL speed we need a HW PID filter */
		if (d->udev->speed == USB_SPEED_FULL && !(adap->props.caps & DVB_USB_ADAP_HAS_PID_FILTER)) {
			err("This USB2.0 device cannot be run on a USB1.1 port. (it lacks a hardware PID filter)");
			return -ENODEV;
		}

		if ((d->udev->speed == USB_SPEED_FULL && adap->props.caps & DVB_USB_ADAP_HAS_PID_FILTER) ||
			(adap->props.caps & DVB_USB_ADAP_NEED_PID_FILTERING)) {
			info("will use the device's hardware PID filter (table count: %d).", adap->props.pid_filter_count);
			adap->pid_filtering  = 1;
			adap->max_feed_count = adap->props.pid_filter_count;
		} else {
			info("will pass the complete MPEG2 transport stream to the software demuxer.");
			adap->pid_filtering  = 0;
			adap->max_feed_count = 255;
		}

		if (!adap->pid_filtering &&
			dvb_usb_force_pid_filter_usage &&
			adap->props.caps & DVB_USB_ADAP_HAS_PID_FILTER) {
			info("pid filter enabled by module option.");
			adap->pid_filtering  = 1;
			adap->max_feed_count = adap->props.pid_filter_count;
		}

		if (adap->props.size_of_priv > 0) {
			adap->priv = kzalloc(adap->props.size_of_priv, GFP_KERNEL);
			if (adap->priv == NULL) {
				err("no memory for priv for adapter %d.", n);
				return -ENOMEM;
			}
		}

		if ((ret = dvb_usb_adapter_stream_init(adap)) ||
			(ret = dvb_usb_adapter_dvb_init(adap, adapter_nrs)) ||
			(ret = dvb_usb_adapter_frontend_init(adap))) {
			return ret;
		}

		d->num_adapters_initialized++;
		d->state |= DVB_USB_STATE_DVB;
	}

	/*
	 * when reloading the driver w/o replugging the device
	 * sometimes a timeout occures, this helps
	 */
	if (d->props.generic_bulk_ctrl_endpoint != 0) {
		usb_clear_halt(d->udev, usb_sndbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoint));
		usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, d->props.generic_bulk_ctrl_endpoint));
	}

	return 0;
}