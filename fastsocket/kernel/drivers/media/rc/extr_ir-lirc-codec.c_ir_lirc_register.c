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
struct rc_dev {char* driver_name; TYPE_2__* raw; int /*<<< orphan*/  dev; scalar_t__ max_timeout; scalar_t__ s_carrier_report; scalar_t__ s_learning_mode; scalar_t__ s_rx_carrier_range; scalar_t__ s_tx_duty_cycle; scalar_t__ s_tx_carrier; scalar_t__ s_tx_mask; scalar_t__ tx_ir; } ;
struct lirc_driver {int minor; unsigned long features; int code_length; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * set_use_dec; int /*<<< orphan*/ * set_use_inc; struct lirc_driver* rbuf; TYPE_1__* data; int /*<<< orphan*/  name; } ;
struct lirc_buffer {int minor; unsigned long features; int code_length; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * set_use_dec; int /*<<< orphan*/ * set_use_inc; struct lirc_buffer* rbuf; TYPE_1__* data; int /*<<< orphan*/  name; } ;
struct ir_raw_event {int dummy; } ;
struct TYPE_3__ {struct rc_dev* dev; struct lirc_driver* drv; } ;
struct TYPE_4__ {TYPE_1__ lirc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIRCBUF_SIZE ; 
 unsigned long LIRC_CAN_MEASURE_CARRIER ; 
 unsigned long LIRC_CAN_REC_MODE2 ; 
 unsigned long LIRC_CAN_SEND_PULSE ; 
 unsigned long LIRC_CAN_SET_REC_CARRIER ; 
 unsigned long LIRC_CAN_SET_REC_CARRIER_RANGE ; 
 unsigned long LIRC_CAN_SET_REC_TIMEOUT ; 
 unsigned long LIRC_CAN_SET_SEND_CARRIER ; 
 unsigned long LIRC_CAN_SET_SEND_DUTY_CYCLE ; 
 unsigned long LIRC_CAN_SET_TRANSMITTER_MASK ; 
 unsigned long LIRC_CAN_USE_WIDEBAND_RECEIVER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ir_lirc_close ; 
 int /*<<< orphan*/  ir_lirc_open ; 
 int /*<<< orphan*/  kfree (struct lirc_driver*) ; 
 struct lirc_driver* kzalloc (int,int /*<<< orphan*/ ) ; 
 int lirc_buffer_init (struct lirc_driver*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lirc_fops ; 
 int lirc_register_driver (struct lirc_driver*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int ir_lirc_register(struct rc_dev *dev)
{
	struct lirc_driver *drv;
	struct lirc_buffer *rbuf;
	int rc = -ENOMEM;
	unsigned long features;

	drv = kzalloc(sizeof(struct lirc_driver), GFP_KERNEL);
	if (!drv)
		return rc;

	rbuf = kzalloc(sizeof(struct lirc_buffer), GFP_KERNEL);
	if (!rbuf)
		goto rbuf_alloc_failed;

	rc = lirc_buffer_init(rbuf, sizeof(int), LIRCBUF_SIZE);
	if (rc)
		goto rbuf_init_failed;

	features = LIRC_CAN_REC_MODE2;
	if (dev->tx_ir) {
		features |= LIRC_CAN_SEND_PULSE;
		if (dev->s_tx_mask)
			features |= LIRC_CAN_SET_TRANSMITTER_MASK;
		if (dev->s_tx_carrier)
			features |= LIRC_CAN_SET_SEND_CARRIER;
		if (dev->s_tx_duty_cycle)
			features |= LIRC_CAN_SET_SEND_DUTY_CYCLE;
	}

	if (dev->s_rx_carrier_range)
		features |= LIRC_CAN_SET_REC_CARRIER |
			LIRC_CAN_SET_REC_CARRIER_RANGE;

	if (dev->s_learning_mode)
		features |= LIRC_CAN_USE_WIDEBAND_RECEIVER;

	if (dev->s_carrier_report)
		features |= LIRC_CAN_MEASURE_CARRIER;

	if (dev->max_timeout)
		features |= LIRC_CAN_SET_REC_TIMEOUT;

	snprintf(drv->name, sizeof(drv->name), "ir-lirc-codec (%s)",
		 dev->driver_name);
	drv->minor = -1;
	drv->features = features;
	drv->data = &dev->raw->lirc;
	drv->rbuf = rbuf;
	drv->set_use_inc = &ir_lirc_open;
	drv->set_use_dec = &ir_lirc_close;
	drv->code_length = sizeof(struct ir_raw_event) * 8;
	drv->fops = &lirc_fops;
	drv->dev = &dev->dev;
	drv->owner = THIS_MODULE;

	drv->minor = lirc_register_driver(drv);
	if (drv->minor < 0) {
		rc = -ENODEV;
		goto lirc_register_failed;
	}

	dev->raw->lirc.drv = drv;
	dev->raw->lirc.dev = dev;
	return 0;

lirc_register_failed:
rbuf_init_failed:
	kfree(rbuf);
rbuf_alloc_failed:
	kfree(drv);

	return rc;
}