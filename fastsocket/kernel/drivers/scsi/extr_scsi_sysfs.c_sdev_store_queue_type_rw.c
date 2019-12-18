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
struct scsi_host_template {int (* change_queue_type ) (struct scsi_device*,int) ;} ;
struct scsi_device {int /*<<< orphan*/  tagged_supported; TYPE_1__* host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct scsi_host_template* hostt; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int MSG_ORDERED_TAG ; 
 int MSG_SIMPLE_TAG ; 
 int scsi_get_tag_type (struct scsi_device*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int stub1 (struct scsi_device*,int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_queue_type_rw(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct scsi_host_template *sht = sdev->host->hostt;
	int tag_type = 0, retval;
	int prev_tag_type = scsi_get_tag_type(sdev);

	if (!sdev->tagged_supported || !sht->change_queue_type)
		return -EINVAL;

	if (strncmp(buf, "ordered", 7) == 0)
		tag_type = MSG_ORDERED_TAG;
	else if (strncmp(buf, "simple", 6) == 0)
		tag_type = MSG_SIMPLE_TAG;
	else if (strncmp(buf, "none", 4) != 0)
		return -EINVAL;

	if (tag_type == prev_tag_type)
		return count;

	retval = sht->change_queue_type(sdev, tag_type);
	if (retval < 0)
		return retval;

	return count;
}