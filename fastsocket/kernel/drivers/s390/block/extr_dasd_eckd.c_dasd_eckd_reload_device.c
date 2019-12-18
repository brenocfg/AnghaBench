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
struct TYPE_3__ {int base_unit_addr; char* vduit; char* vendor; char* serial; int ssid; } ;
struct dasd_eckd_private {TYPE_1__ uid; } ;
struct dasd_device {TYPE_2__* cdev; scalar_t__ private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_alias_update_add_device (struct dasd_device*) ; 
 int dasd_eckd_generate_uid (struct dasd_device*) ; 
 int dasd_eckd_read_conf (struct dasd_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int,int,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int dasd_eckd_reload_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	int rc, old_base;
	char uid[60];

	private = (struct dasd_eckd_private *) device->private;
	old_base = private->uid.base_unit_addr;
	/* Read Configuration Data */
	rc = dasd_eckd_read_conf(device);
	if (rc)
		goto out_err;

	rc = dasd_eckd_generate_uid(device);
	if (rc)
		goto out_err;

	/*
	 * update unit address configuration and
	 * add device to alias management
	 */
	dasd_alias_update_add_device(device);

	if (old_base != private->uid.base_unit_addr) {
		if (strlen(private->uid.vduit) > 0)
			snprintf(uid, 60, "%s.%s.%04x.%02x.%s",
				 private->uid.vendor, private->uid.serial,
				 private->uid.ssid, private->uid.base_unit_addr,
				 private->uid.vduit);
		else
			snprintf(uid, 60, "%s.%s.%04x.%02x",
				 private->uid.vendor, private->uid.serial,
				 private->uid.ssid,
				 private->uid.base_unit_addr);

		dev_info(&device->cdev->dev,
			 "An Alias device was reassigned to a new base device "
			 "with UID: %s\n", uid);
	}
	return 0;

out_err:
	return -1;
}