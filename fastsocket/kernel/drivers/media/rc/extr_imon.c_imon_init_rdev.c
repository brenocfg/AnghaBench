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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rc_dev {int allowed_protos; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  change_protocol; int /*<<< orphan*/  driver_type; struct imon_context* priv; TYPE_1__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  input_name; } ;
struct imon_context {int vendor; int product; int rc_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  usbdev_intf0; int /*<<< orphan*/  phys_rdev; int /*<<< orphan*/  name_rdev; } ;
typedef  int /*<<< orphan*/  fp_packet ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_NAME ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 int /*<<< orphan*/  RC_MAP_IMON_MCE ; 
 int /*<<< orphan*/  RC_MAP_IMON_PAD ; 
 int RC_TYPE_OTHER ; 
 int RC_TYPE_RC6 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imon_get_ffdc_type (struct imon_context*) ; 
 int /*<<< orphan*/  imon_ir_change_protocol ; 
 int /*<<< orphan*/  imon_set_display_type (struct imon_context*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const**,int) ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int send_packet (struct imon_context*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rc_dev *imon_init_rdev(struct imon_context *ictx)
{
	struct rc_dev *rdev;
	int ret;
	const unsigned char fp_packet[] = { 0x40, 0x00, 0x00, 0x00,
					    0x00, 0x00, 0x00, 0x88 };

	rdev = rc_allocate_device();
	if (!rdev) {
		dev_err(ictx->dev, "remote control dev allocation failed\n");
		goto out;
	}

	snprintf(ictx->name_rdev, sizeof(ictx->name_rdev),
		 "iMON Remote (%04x:%04x)", ictx->vendor, ictx->product);
	usb_make_path(ictx->usbdev_intf0, ictx->phys_rdev,
		      sizeof(ictx->phys_rdev));
	strlcat(ictx->phys_rdev, "/input0", sizeof(ictx->phys_rdev));

	rdev->input_name = ictx->name_rdev;
	rdev->input_phys = ictx->phys_rdev;
	usb_to_input_id(ictx->usbdev_intf0, &rdev->input_id);
	rdev->dev.parent = ictx->dev;

	rdev->priv = ictx;
	rdev->driver_type = RC_DRIVER_SCANCODE;
	rdev->allowed_protos = RC_TYPE_OTHER | RC_TYPE_RC6; /* iMON PAD or MCE */
	rdev->change_protocol = imon_ir_change_protocol;
	rdev->driver_name = MOD_NAME;

	/* Enable front-panel buttons and/or knobs */
	memcpy(ictx->usb_tx_buf, &fp_packet, sizeof(fp_packet));
	ret = send_packet(ictx);
	/* Not fatal, but warn about it */
	if (ret)
		dev_info(ictx->dev, "panel buttons/knobs setup failed\n");

	if (ictx->product == 0xffdc) {
		imon_get_ffdc_type(ictx);
		rdev->allowed_protos = ictx->rc_type;
	}

	imon_set_display_type(ictx);

	if (ictx->rc_type == RC_TYPE_RC6)
		rdev->map_name = RC_MAP_IMON_MCE;
	else
		rdev->map_name = RC_MAP_IMON_PAD;

	ret = rc_register_device(rdev);
	if (ret < 0) {
		dev_err(ictx->dev, "remote input dev register failed\n");
		goto out;
	}

	return rdev;

out:
	rc_free_device(rdev);
	return NULL;
}