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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_unit {TYPE_1__* port; } ;
struct zfcp_port {int /*<<< orphan*/  status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  config_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IS_ERR (struct zfcp_unit*) ; 
 int ZFCP_STATUS_COMMON_REMOVE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strict_strtoull (char const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 TYPE_2__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_unit_reopen (struct zfcp_unit*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_scsi_scan (struct zfcp_unit*) ; 
 struct zfcp_unit* zfcp_unit_enqueue (struct zfcp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_unit_put (struct zfcp_unit*) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_unit_add_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct zfcp_port *port = dev_get_drvdata(dev);
	struct zfcp_unit *unit;
	u64 fcp_lun;

	mutex_lock(&zfcp_data.config_mutex);
	if (atomic_read(&port->status) & ZFCP_STATUS_COMMON_REMOVE) {
		mutex_unlock(&zfcp_data.config_mutex);
		return -EBUSY;
	}

	if (strict_strtoull(buf, 0, (unsigned long long *) &fcp_lun)) {
		mutex_unlock(&zfcp_data.config_mutex);
		return -EINVAL;
	}

	unit = zfcp_unit_enqueue(port, fcp_lun);
	mutex_unlock(&zfcp_data.config_mutex);
	if (IS_ERR(unit))
		return -EINVAL;

	zfcp_erp_unit_reopen(unit, 0, "syuas_1", NULL);
	zfcp_erp_wait(unit->port->adapter);
	zfcp_scsi_scan(unit);
	zfcp_unit_put(unit);

	return (ssize_t) count;
}