#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp_rdc_data ;
struct dasd_uid {int dummy; } ;
struct dasd_eckd_private {int /*<<< orphan*/  rdc_data; int /*<<< orphan*/  uid; } ;
struct dasd_eckd_characteristics {int dummy; } ;
struct dasd_device {TYPE_1__* cdev; scalar_t__ private; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FLAGS_FAILFAST ; 
 int /*<<< orphan*/  DASD_ECKD_MAGIC ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  dasd_alias_add_device (struct dasd_device*) ; 
 int dasd_alias_make_device_known_to_lcu (struct dasd_device*) ; 
 int dasd_eckd_generate_uid (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eckd_get_uid (struct dasd_device*,struct dasd_uid*) ; 
 int /*<<< orphan*/  dasd_eckd_read_conf (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eckd_read_features (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eckd_validate_server (struct dasd_device*,unsigned long) ; 
 int dasd_generic_read_dev_chars (struct dasd_device*,int /*<<< orphan*/ ,struct dasd_eckd_characteristics*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct dasd_uid*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dasd_eckd_characteristics*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dasd_eckd_restore_device(struct dasd_device *device)
{
	struct dasd_eckd_private *private;
	struct dasd_eckd_characteristics temp_rdc_data;
	int rc;
	struct dasd_uid temp_uid;
	unsigned long flags;
	unsigned long cqr_flags = 0;

	private = (struct dasd_eckd_private *) device->private;

	/* Read Configuration Data */
	dasd_eckd_read_conf(device);

	dasd_eckd_get_uid(device, &temp_uid);
	/* Generate device unique id */
	rc = dasd_eckd_generate_uid(device);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	if (memcmp(&private->uid, &temp_uid, sizeof(struct dasd_uid)) != 0)
		dev_err(&device->cdev->dev, "The UID of the DASD has "
			"changed\n");
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	if (rc)
		goto out_err;

	/* register lcu with alias handling, enable PAV if this is a new lcu */
	rc = dasd_alias_make_device_known_to_lcu(device);
	if (rc)
		return rc;

	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr_flags);
	dasd_eckd_validate_server(device, cqr_flags);

	/* RE-Read Configuration Data */
	dasd_eckd_read_conf(device);

	/* Read Feature Codes */
	dasd_eckd_read_features(device);

	/* Read Device Characteristics */
	rc = dasd_generic_read_dev_chars(device, DASD_ECKD_MAGIC,
					 &temp_rdc_data, 64);
	if (rc) {
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Read device characteristic failed, rc=%d", rc);
		goto out_err;
	}
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	memcpy(&private->rdc_data, &temp_rdc_data, sizeof(temp_rdc_data));
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/* add device to alias management */
	dasd_alias_add_device(device);

	return 0;

out_err:
	return -1;
}