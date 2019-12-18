#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct device* parent; } ;
struct rc_dev {scalar_t__ map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  s_tx_mask; int /*<<< orphan*/  timeout; int /*<<< orphan*/  allowed_protos; int /*<<< orphan*/  driver_type; struct mceusb_dev* priv; TYPE_2__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  input_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  no_tx; } ;
struct mceusb_dev {size_t model; TYPE_3__ flags; TYPE_4__* usbdev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_11__ {char* name; scalar_t__ rc_map; } ;
struct TYPE_7__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_10__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 scalar_t__ RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_TYPE_ALL ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_6__* mceusb_model ; 
 int /*<<< orphan*/  mceusb_set_tx_carrier ; 
 int /*<<< orphan*/  mceusb_set_tx_mask ; 
 int /*<<< orphan*/  mceusb_tx_ir ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  usb_make_path (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rc_dev *mceusb_init_rc_dev(struct mceusb_dev *ir)
{
	struct device *dev = ir->dev;
	struct rc_dev *rc;
	int ret;

	rc = rc_allocate_device();
	if (!rc) {
		dev_err(dev, "remote dev allocation failed\n");
		goto out;
	}

	snprintf(ir->name, sizeof(ir->name), "%s (%04x:%04x)",
		 mceusb_model[ir->model].name ?
			mceusb_model[ir->model].name :
			"Media Center Ed. eHome Infrared Remote Transceiver",
		 le16_to_cpu(ir->usbdev->descriptor.idVendor),
		 le16_to_cpu(ir->usbdev->descriptor.idProduct));

	usb_make_path(ir->usbdev, ir->phys, sizeof(ir->phys));

	rc->input_name = ir->name;
	rc->input_phys = ir->phys;
	usb_to_input_id(ir->usbdev, &rc->input_id);
	rc->dev.parent = dev;
	rc->priv = ir;
	rc->driver_type = RC_DRIVER_IR_RAW;
	rc->allowed_protos = RC_TYPE_ALL;
	rc->timeout = US_TO_NS(1000);
	if (!ir->flags.no_tx) {
		rc->s_tx_mask = mceusb_set_tx_mask;
		rc->s_tx_carrier = mceusb_set_tx_carrier;
		rc->tx_ir = mceusb_tx_ir;
	}
	rc->driver_name = DRIVER_NAME;
	rc->map_name = mceusb_model[ir->model].rc_map ?
			mceusb_model[ir->model].rc_map : RC_MAP_RC6_MCE;

	ret = rc_register_device(rc);
	if (ret < 0) {
		dev_err(dev, "remote dev registration failed\n");
		goto out;
	}

	return rc;

out:
	rc_free_device(rc);
	return NULL;
}