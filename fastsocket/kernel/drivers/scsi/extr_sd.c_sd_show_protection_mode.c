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
struct scsi_disk {int /*<<< orphan*/  protection_type; struct scsi_device* device; } ;
struct scsi_device {int /*<<< orphan*/  host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SD_DIF_TYPE0_PROTECTION ; 
 unsigned int scsi_host_dif_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int scsi_host_dix_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
sd_show_protection_mode(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;
	unsigned int dif, dix;

	dif = scsi_host_dif_capable(sdp->host, sdkp->protection_type);
	dix = scsi_host_dix_capable(sdp->host, sdkp->protection_type);

	if (!dix && scsi_host_dix_capable(sdp->host, SD_DIF_TYPE0_PROTECTION)) {
		dif = 0;
		dix = 1;
	}

	if (!dif && !dix)
		return snprintf(buf, 20, "none\n");

	return snprintf(buf, 20, "%s%u\n", dix ? "dix" : "dif", dif);
}