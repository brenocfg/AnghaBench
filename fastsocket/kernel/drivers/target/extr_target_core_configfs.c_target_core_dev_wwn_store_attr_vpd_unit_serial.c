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
struct t10_wwn {struct se_device* t10_dev; } ;
struct TYPE_2__ {unsigned char* unit_serial; } ;
struct se_device {int dev_flags; int export_count; TYPE_1__ t10_wwn; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int DF_EMULATED_VPD_UNIT_SERIAL ; 
 int DF_FIRMWARE_VPD_UNIT_SERIAL ; 
 size_t EINVAL ; 
 size_t EOPNOTSUPP ; 
 size_t EOVERFLOW ; 
 int INQUIRY_VPD_SERIAL_LEN ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 char* strstrip (unsigned char*) ; 

__attribute__((used)) static ssize_t target_core_dev_wwn_store_attr_vpd_unit_serial(
	struct t10_wwn *t10_wwn,
	const char *page,
	size_t count)
{
	struct se_device *dev = t10_wwn->t10_dev;
	unsigned char buf[INQUIRY_VPD_SERIAL_LEN];

	/*
	 * If Linux/SCSI subsystem_api_t plugin got a VPD Unit Serial
	 * from the struct scsi_device level firmware, do not allow
	 * VPD Unit Serial to be emulated.
	 *
	 * Note this struct scsi_device could also be emulating VPD
	 * information from its drivers/scsi LLD.  But for now we assume
	 * it is doing 'the right thing' wrt a world wide unique
	 * VPD Unit Serial Number that OS dependent multipath can depend on.
	 */
	if (dev->dev_flags & DF_FIRMWARE_VPD_UNIT_SERIAL) {
		pr_err("Underlying SCSI device firmware provided VPD"
			" Unit Serial, ignoring request\n");
		return -EOPNOTSUPP;
	}

	if (strlen(page) >= INQUIRY_VPD_SERIAL_LEN) {
		pr_err("Emulated VPD Unit Serial exceeds"
		" INQUIRY_VPD_SERIAL_LEN: %d\n", INQUIRY_VPD_SERIAL_LEN);
		return -EOVERFLOW;
	}
	/*
	 * Check to see if any active $FABRIC_MOD exports exist.  If they
	 * do exist, fail here as changing this information on the fly
	 * (underneath the initiator side OS dependent multipath code)
	 * could cause negative effects.
	 */
	if (dev->export_count) {
		pr_err("Unable to set VPD Unit Serial while"
			" active %d $FABRIC_MOD exports exist\n",
			dev->export_count);
		return -EINVAL;
	}

	/*
	 * This currently assumes ASCII encoding for emulated VPD Unit Serial.
	 *
	 * Also, strip any newline added from the userspace
	 * echo $UUID > $TARGET/$HBA/$STORAGE_OBJECT/wwn/vpd_unit_serial
	 */
	memset(buf, 0, INQUIRY_VPD_SERIAL_LEN);
	snprintf(buf, INQUIRY_VPD_SERIAL_LEN, "%s", page);
	snprintf(dev->t10_wwn.unit_serial, INQUIRY_VPD_SERIAL_LEN,
			"%s", strstrip(buf));
	dev->dev_flags |= DF_EMULATED_VPD_UNIT_SERIAL;

	pr_debug("Target_Core_ConfigFS: Set emulated VPD Unit Serial:"
			" %s\n", dev->t10_wwn.unit_serial);

	return count;
}