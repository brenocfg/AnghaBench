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
struct usb_interface {int dummy; } ;
struct usb_host_interface {TYPE_3__* endpoint; } ;
struct TYPE_5__ {int /*<<< orphan*/  alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;
struct sd {TYPE_4__* sensor; TYPE_1__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_8__ {int (* start ) (struct sd*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_7__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_STREAM ; 
 int EIO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STV_ISO_ENABLE ; 
 int /*<<< orphan*/  STV_ISO_SIZE_L ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct sd*) ; 
 int stv06xx_write_bridge (struct sd*,int /*<<< orphan*/ ,int) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv06xx_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct usb_host_interface *alt;
	struct usb_interface *intf;
	int err, packet_size;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	alt = usb_altnum_to_altsetting(intf, sd->gspca_dev.alt);
	if (!alt) {
		PDEBUG(D_ERR, "Couldn't get altsetting");
		return -EIO;
	}

	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	err = stv06xx_write_bridge(sd, STV_ISO_SIZE_L, packet_size);
	if (err < 0)
		return err;

	/* Prepare the sensor for start */
	err = sd->sensor->start(sd);
	if (err < 0)
		goto out;

	/* Start isochronous streaming */
	err = stv06xx_write_bridge(sd, STV_ISO_ENABLE, 1);

out:
	if (err < 0)
		PDEBUG(D_STREAM, "Starting stream failed");
	else
		PDEBUG(D_STREAM, "Started streaming");

	return (err < 0) ? err : 0;
}