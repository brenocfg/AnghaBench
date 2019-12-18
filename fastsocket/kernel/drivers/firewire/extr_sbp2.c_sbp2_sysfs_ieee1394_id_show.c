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
struct scsi_device {struct sbp2_logical_unit* hostdata; } ;
struct sbp2_logical_unit {int /*<<< orphan*/  lun; TYPE_1__* tgt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  directory_id; scalar_t__ guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t sbp2_sysfs_ieee1394_id_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct sbp2_logical_unit *lu;

	if (!sdev)
		return 0;

	lu = sdev->hostdata;

	return sprintf(buf, "%016llx:%06x:%04x\n",
			(unsigned long long)lu->tgt->guid,
			lu->tgt->directory_id, lu->lun);
}