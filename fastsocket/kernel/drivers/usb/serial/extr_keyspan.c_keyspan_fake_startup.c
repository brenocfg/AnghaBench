#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial {TYPE_2__* dev; } ;
struct ihex_binrec {int /*<<< orphan*/  len; scalar_t__ data; int /*<<< orphan*/  addr; } ;
struct firmware {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  bcdDevice; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int ezusb_set_reset (struct usb_serial*,int) ; 
 int ezusb_writememory (struct usb_serial*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
#define  keyspan_mpr_pre_product_id 139 
#define  keyspan_usa18x_pre_product_id 138 
#define  keyspan_usa19_pre_product_id 137 
#define  keyspan_usa19qi_pre_product_id 136 
#define  keyspan_usa19qw_pre_product_id 135 
#define  keyspan_usa19w_pre_product_id 134 
#define  keyspan_usa28_pre_product_id 133 
#define  keyspan_usa28x_pre_product_id 132 
#define  keyspan_usa28xa_pre_product_id 131 
#define  keyspan_usa28xb_pre_product_id 130 
#define  keyspan_usa49w_pre_product_id 129 
#define  keyspan_usa49wlc_pre_product_id 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_ihex_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keyspan_fake_startup(struct usb_serial *serial)
{
	int 				response;
	const struct ihex_binrec 	*record;
	char				*fw_name;
	const struct firmware		*fw;

	dbg("Keyspan startup version %04x product %04x",
	    le16_to_cpu(serial->dev->descriptor.bcdDevice),
	    le16_to_cpu(serial->dev->descriptor.idProduct));

	if ((le16_to_cpu(serial->dev->descriptor.bcdDevice) & 0x8000)
								!= 0x8000) {
		dbg("Firmware already loaded.  Quitting.");
		return 1;
	}

		/* Select firmware image on the basis of idProduct */
	switch (le16_to_cpu(serial->dev->descriptor.idProduct)) {
	case keyspan_usa28_pre_product_id:
		fw_name = "keyspan/usa28.fw";
		break;

	case keyspan_usa28x_pre_product_id:
		fw_name = "keyspan/usa28x.fw";
		break;

	case keyspan_usa28xa_pre_product_id:
		fw_name = "keyspan/usa28xa.fw";
		break;

	case keyspan_usa28xb_pre_product_id:
		fw_name = "keyspan/usa28xb.fw";
		break;

	case keyspan_usa19_pre_product_id:
		fw_name = "keyspan/usa19.fw";
		break;

	case keyspan_usa19qi_pre_product_id:
		fw_name = "keyspan/usa19qi.fw";
		break;

	case keyspan_mpr_pre_product_id:
		fw_name = "keyspan/mpr.fw";
		break;

	case keyspan_usa19qw_pre_product_id:
		fw_name = "keyspan/usa19qw.fw";
		break;

	case keyspan_usa18x_pre_product_id:
		fw_name = "keyspan/usa18x.fw";
		break;

	case keyspan_usa19w_pre_product_id:
		fw_name = "keyspan/usa19w.fw";
		break;

	case keyspan_usa49w_pre_product_id:
		fw_name = "keyspan/usa49w.fw";
		break;

	case keyspan_usa49wlc_pre_product_id:
		fw_name = "keyspan/usa49wlc.fw";
		break;

	default:
		dev_err(&serial->dev->dev, "Unknown product ID (%04x)\n",
			le16_to_cpu(serial->dev->descriptor.idProduct));
		return 1;
	}

	if (request_ihex_firmware(&fw, fw_name, &serial->dev->dev)) {
		dev_err(&serial->dev->dev, "Required keyspan firmware image (%s) unavailable.\n", fw_name);
		return(1);
	}

	dbg("Uploading Keyspan %s firmware.", fw_name);

		/* download the firmware image */
	response = ezusb_set_reset(serial, 1);

	record = (const struct ihex_binrec *)fw->data;

	while (record) {
		response = ezusb_writememory(serial, be32_to_cpu(record->addr),
					     (unsigned char *)record->data,
					     be16_to_cpu(record->len), 0xa0);
		if (response < 0) {
			dev_err(&serial->dev->dev, "ezusb_writememory failed for Keyspan firmware (%d %04X %p %d)\n",
				response, be32_to_cpu(record->addr),
				record->data, be16_to_cpu(record->len));
			break;
		}
		record = ihex_next_binrec(record);
	}
	release_firmware(fw);
		/* bring device out of reset. Renumeration will occur in a
		   moment and the new device will bind to the real driver */
	response = ezusb_set_reset(serial, 0);

	/* we don't want this device to have a driver assigned to it. */
	return 1;
}