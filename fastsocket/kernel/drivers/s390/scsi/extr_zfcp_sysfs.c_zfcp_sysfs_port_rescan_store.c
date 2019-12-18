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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int ZFCP_STATUS_COMMON_REMOVE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_port_rescan_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct zfcp_adapter *adapter = dev_get_drvdata(dev);

	if (atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_REMOVE)
		return -EBUSY;

	/* sync the user-space- with the kernel-invocation of scan_work */
	queue_work(adapter->work_queue, &adapter->scan_work);
	flush_work(&adapter->scan_work);

	return (ssize_t) count;
}