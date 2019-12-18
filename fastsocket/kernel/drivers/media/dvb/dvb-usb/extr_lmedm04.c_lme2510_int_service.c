#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rc_dev {char* input_name; char* driver_name; int /*<<< orphan*/  input_id; int /*<<< orphan*/  map_name; int /*<<< orphan*/  input_phys; } ;
struct dvb_usb_device {struct rc_dev* rc_dev; int /*<<< orphan*/  udev; int /*<<< orphan*/  rc_phys; } ;
struct dvb_usb_adapter {struct dvb_usb_device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RC_MAP_LME2510 ; 
 int /*<<< orphan*/  info (char*) ; 
 int lme2510_int_read (struct dvb_usb_adapter*) ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  rc_unregister_device (struct rc_dev*) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lme2510_int_service(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap->dev;
	struct rc_dev *rc;
	int ret;

	info("STA Configuring Remote");

	rc = rc_allocate_device();
	if (!rc)
		return -ENOMEM;

	usb_make_path(d->udev, d->rc_phys, sizeof(d->rc_phys));
	strlcat(d->rc_phys, "/ir0", sizeof(d->rc_phys));

	rc->input_name = "LME2510 Remote Control";
	rc->input_phys = d->rc_phys;
	rc->map_name = RC_MAP_LME2510;
	rc->driver_name = "LME 2510";
	usb_to_input_id(d->udev, &rc->input_id);

	ret = rc_register_device(rc);
	if (ret) {
		rc_free_device(rc);
		return ret;
	}
	d->rc_dev = rc;

	/* Start the Interupt */
	ret = lme2510_int_read(adap);
	if (ret < 0) {
		rc_unregister_device(rc);
		info("INT Unable to start Interupt Service");
		return -ENODEV;
	}

	return 0;
}