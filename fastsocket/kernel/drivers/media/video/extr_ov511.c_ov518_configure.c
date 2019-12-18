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
struct usb_ov511 {scalar_t__ led_policy; int compress; scalar_t__ bridge; int packet_numbering; int maxwidth; int maxheight; int minwidth; int minheight; void* primary_i2c_slave; int /*<<< orphan*/  snap_enabled; TYPE_3__* dev; int /*<<< orphan*/  desc; } ;
struct usb_interface {int dummy; } ;
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct ov511_regvals {int const member_1; int member_2; int /*<<< orphan*/  const member_0; } ;
typedef  int __u16 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ BRG_OV518 ; 
 scalar_t__ BRG_OV518PLUS ; 
 int EBUSY ; 
 scalar_t__ LED_AUTO ; 
 scalar_t__ LED_OFF ; 
#define  OV511_DONE_BUS 132 
#define  OV511_REG_BUS 131 
 void* OV6xx0_SID ; 
 void* OV7xx0_SID ; 
 void* OV8xx0_SID ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  R511_SYS_CUST_ID ; 
#define  R51x_SYS_INIT 130 
#define  R51x_SYS_RESET 129 
#define  R51x_SYS_SNAP 128 
 int /*<<< orphan*/  camlist ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dumppix ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ init_ov_sensor (struct usb_ov511*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ov518_init_compression (struct usb_ov511*) ; 
 int /*<<< orphan*/  ov518_set_packet_size (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov51x_led_control (struct usb_ov511*,int) ; 
 scalar_t__ ov51x_set_slave_ids (struct usb_ov511*,void*) ; 
 scalar_t__ ov6xx0_configure (struct usb_ov511*) ; 
 scalar_t__ ov7xx0_configure (struct usb_ov511*) ; 
 int reg_r (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_w (struct usb_ov511*,int,int) ; 
 scalar_t__ reg_w_mask (struct usb_ov511*,int,int,int) ; 
 int /*<<< orphan*/  snapshot ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int) ; 
 struct usb_interface* usb_ifnum_to_if (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_regvals (struct usb_ov511*,struct ov511_regvals*) ; 

__attribute__((used)) static int
ov518_configure(struct usb_ov511 *ov)
{
	/* For 518 and 518+ */
	static struct ov511_regvals aRegvalsInit518[] = {
		{ OV511_REG_BUS, R51x_SYS_RESET,	0x40 },
		{ OV511_REG_BUS, R51x_SYS_INIT,		0xe1 },
		{ OV511_REG_BUS, R51x_SYS_RESET,	0x3e },
		{ OV511_REG_BUS, R51x_SYS_INIT,		0xe1 },
		{ OV511_REG_BUS, R51x_SYS_RESET,	0x00 },
		{ OV511_REG_BUS, R51x_SYS_INIT,		0xe1 },
		{ OV511_REG_BUS, 0x46,			0x00 },
		{ OV511_REG_BUS, 0x5d,			0x03 },
		{ OV511_DONE_BUS, 0x0, 0x00},
	};

	static struct ov511_regvals aRegvalsNorm518[] = {
		{ OV511_REG_BUS, R51x_SYS_SNAP,		0x02 }, /* Reset */
		{ OV511_REG_BUS, R51x_SYS_SNAP,		0x01 }, /* Enable */
		{ OV511_REG_BUS, 0x31, 			0x0f },
		{ OV511_REG_BUS, 0x5d,			0x03 },
		{ OV511_REG_BUS, 0x24,			0x9f },
		{ OV511_REG_BUS, 0x25,			0x90 },
		{ OV511_REG_BUS, 0x20,			0x00 },
		{ OV511_REG_BUS, 0x51,			0x04 },
		{ OV511_REG_BUS, 0x71,			0x19 },
		{ OV511_DONE_BUS, 0x0, 0x00 },
	};

	static struct ov511_regvals aRegvalsNorm518Plus[] = {
		{ OV511_REG_BUS, R51x_SYS_SNAP,		0x02 }, /* Reset */
		{ OV511_REG_BUS, R51x_SYS_SNAP,		0x01 }, /* Enable */
		{ OV511_REG_BUS, 0x31, 			0x0f },
		{ OV511_REG_BUS, 0x5d,			0x03 },
		{ OV511_REG_BUS, 0x24,			0x9f },
		{ OV511_REG_BUS, 0x25,			0x90 },
		{ OV511_REG_BUS, 0x20,			0x60 },
		{ OV511_REG_BUS, 0x51,			0x02 },
		{ OV511_REG_BUS, 0x71,			0x19 },
		{ OV511_REG_BUS, 0x40,			0xff },
		{ OV511_REG_BUS, 0x41,			0x42 },
		{ OV511_REG_BUS, 0x46,			0x00 },
		{ OV511_REG_BUS, 0x33,			0x04 },
		{ OV511_REG_BUS, 0x21,			0x19 },
		{ OV511_REG_BUS, 0x3f,			0x10 },
		{ OV511_DONE_BUS, 0x0, 0x00 },
	};

	PDEBUG(4, "");

	/* First 5 bits of custom ID reg are a revision ID on OV518 */
	dev_info(&ov->dev->dev, "Device revision %d\n",
		 0x1F & reg_r(ov, R511_SYS_CUST_ID));

	/* Give it the default description */
	ov->desc = symbolic(camlist, 0);

	if (write_regvals(ov, aRegvalsInit518))
		goto error;

	/* Set LED GPIO pin to output mode */
	if (reg_w_mask(ov, 0x57, 0x00, 0x02) < 0)
		goto error;

	/* LED is off by default with OV518; have to explicitly turn it on */
	if (ov->led_policy == LED_OFF || ov->led_policy == LED_AUTO)
		ov51x_led_control(ov, 0);
	else
		ov51x_led_control(ov, 1);

	/* Don't require compression if dumppix is enabled; otherwise it's
	 * required. OV518 has no uncompressed mode, to save RAM. */
	if (!dumppix && !ov->compress) {
		ov->compress = 1;
		dev_warn(&ov->dev->dev,
			 "Compression required with OV518...enabling\n");
	}

	if (ov->bridge == BRG_OV518) {
		if (write_regvals(ov, aRegvalsNorm518))
			goto error;
	} else if (ov->bridge == BRG_OV518PLUS) {
		if (write_regvals(ov, aRegvalsNorm518Plus))
			goto error;
	} else {
		err("Invalid bridge");
	}

	if (reg_w(ov, 0x2f, 0x80) < 0)
		goto error;

	if (ov518_init_compression(ov))
		goto error;

	if (ov->bridge == BRG_OV518)
	{
		struct usb_interface *ifp;
		struct usb_host_interface *alt;
		__u16 mxps = 0;

		ifp = usb_ifnum_to_if(ov->dev, 0);
		if (ifp) {
			alt = usb_altnum_to_altsetting(ifp, 7);
			if (alt)
				mxps = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
		}

		/* Some OV518s have packet numbering by default, some don't */
		if (mxps == 897)
			ov->packet_numbering = 1;
		else
			ov->packet_numbering = 0;
	} else {
		/* OV518+ has packet numbering turned on by default */
		ov->packet_numbering = 1;
	}

	ov518_set_packet_size(ov, 0);

	ov->snap_enabled = snapshot;

	/* Test for 76xx */
	ov->primary_i2c_slave = OV7xx0_SID;
	if (ov51x_set_slave_ids(ov, OV7xx0_SID) < 0)
		goto error;

	/* The OV518 must be more aggressive about sensor detection since
	 * I2C write will never fail if the sensor is not present. We have
	 * to try to initialize the sensor to detect its presence */

	if (init_ov_sensor(ov) < 0) {
		/* Test for 6xx0 */
		ov->primary_i2c_slave = OV6xx0_SID;
		if (ov51x_set_slave_ids(ov, OV6xx0_SID) < 0)
			goto error;

		if (init_ov_sensor(ov) < 0) {
			/* Test for 8xx0 */
			ov->primary_i2c_slave = OV8xx0_SID;
			if (ov51x_set_slave_ids(ov, OV8xx0_SID) < 0)
				goto error;

			if (init_ov_sensor(ov) < 0) {
				err("Can't determine sensor slave IDs");
				goto error;
			} else {
				err("Detected unsupported OV8xx0 sensor");
				goto error;
			}
		} else {
			if (ov6xx0_configure(ov) < 0) {
				err("Failed to configure OV6xx0");
				goto error;
			}
		}
	} else {
		if (ov7xx0_configure(ov) < 0) {
			err("Failed to configure OV7xx0");
			goto error;
		}
	}

	ov->maxwidth = 352;
	ov->maxheight = 288;

	// The OV518 cannot go as low as the sensor can
	ov->minwidth = 160;
	ov->minheight = 120;

	return 0;

error:
	err("OV518 Config failed");

	return -EBUSY;
}