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
typedef  int /*<<< orphan*/  u32 ;
struct ehea_port {TYPE_1__* netdev; } ;
struct ehea_adapter {struct ehea_port** port; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EHEA_MAX_PORTS ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ehea_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ehea_error (char*,int /*<<< orphan*/ ) ; 
 struct ehea_port* ehea_get_port (struct ehea_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_remove_adapter_mr (struct ehea_adapter*) ; 
 int /*<<< orphan*/  ehea_shutdown_single_port (struct ehea_port*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ehea_remove_port(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct ehea_adapter *adapter = dev_get_drvdata(dev);
	struct ehea_port *port;
	int i;
	u32 logical_port_id;

	sscanf(buf, "%d", &logical_port_id);

	port = ehea_get_port(adapter, logical_port_id);

	if (port) {
		ehea_info("removed %s (logical port id=%d)", port->netdev->name,
			  logical_port_id);

		ehea_shutdown_single_port(port);

		for (i = 0; i < EHEA_MAX_PORTS; i++)
			if (adapter->port[i] == port) {
				adapter->port[i] = NULL;
				break;
			}
	} else {
		ehea_error("removing port with logical port id=%d failed. port "
			   "not configured.", logical_port_id);
		return -EINVAL;
	}

	ehea_remove_adapter_mr(adapter);

	return (ssize_t) count;
}