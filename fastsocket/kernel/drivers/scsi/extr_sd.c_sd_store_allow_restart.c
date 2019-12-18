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
struct scsi_disk {struct scsi_device* device; } ;
struct scsi_device {scalar_t__ type; int /*<<< orphan*/  allow_restart; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
sd_store_allow_restart(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (sdp->type != TYPE_DISK)
		return -EINVAL;

	sdp->allow_restart = simple_strtoul(buf, NULL, 10);

	return count;
}