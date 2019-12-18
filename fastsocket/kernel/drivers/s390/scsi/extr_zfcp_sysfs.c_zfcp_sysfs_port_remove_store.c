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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_port {int /*<<< orphan*/  list; int /*<<< orphan*/  status; int /*<<< orphan*/  refcount; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  config_mutex; int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int ZFCP_STATUS_COMMON_REMOVE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_mask (int,int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_remove_lh ; 
 scalar_t__ strict_strtoull (char const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_port_shutdown (struct zfcp_port*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_port_dequeue (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_port_get (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_port_remove_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct zfcp_adapter *adapter = dev_get_drvdata(dev);
	struct zfcp_port *port;
	u64 wwpn;
	int retval = 0;
	LIST_HEAD(port_remove_lh);

	mutex_lock(&zfcp_data.config_mutex);
	if (atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_REMOVE) {
		retval = -EBUSY;
		goto out;
	}

	if (strict_strtoull(buf, 0, (unsigned long long *) &wwpn)) {
		retval = -EINVAL;
		goto out;
	}

	write_lock_irq(&zfcp_data.config_lock);
	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	if (port && (atomic_read(&port->refcount) == 0)) {
		zfcp_port_get(port);
		atomic_set_mask(ZFCP_STATUS_COMMON_REMOVE, &port->status);
		list_move(&port->list, &port_remove_lh);
	} else
		port = NULL;
	write_unlock_irq(&zfcp_data.config_lock);

	if (!port) {
		retval = -ENXIO;
		goto out;
	}

	zfcp_erp_port_shutdown(port, 0, "syprs_1", NULL);
	zfcp_erp_wait(adapter);
	zfcp_port_put(port);
	zfcp_port_dequeue(port);
 out:
	mutex_unlock(&zfcp_data.config_mutex);
	return retval ? retval : (ssize_t) count;
}