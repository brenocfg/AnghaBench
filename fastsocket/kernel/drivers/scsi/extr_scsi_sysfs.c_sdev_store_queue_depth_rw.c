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
struct scsi_host_template {int (* change_queue_depth ) (struct scsi_device*,int,int /*<<< orphan*/ ) ;} ;
struct scsi_device {int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  max_queue_depth; TYPE_1__* host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct scsi_host_template* hostt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCSI_QDEPTH_DEFAULT ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct scsi_device*,int,int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_queue_depth_rw(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	int depth, retval;
	struct scsi_device *sdev = to_scsi_device(dev);
	struct scsi_host_template *sht = sdev->host->hostt;

	if (!sht->change_queue_depth)
		return -EINVAL;

	depth = simple_strtoul(buf, NULL, 0);

	if (depth < 1)
		return -EINVAL;

	retval = sht->change_queue_depth(sdev, depth,
					 SCSI_QDEPTH_DEFAULT);
	if (retval < 0)
		return retval;

	sdev->max_queue_depth = sdev->queue_depth;

	return count;
}