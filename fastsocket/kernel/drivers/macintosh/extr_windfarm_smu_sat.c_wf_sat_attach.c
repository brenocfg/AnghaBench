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
struct pmac_i2c_bus {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 struct pmac_i2c_bus* pmac_i2c_adapter_to_bus (struct i2c_adapter*) ; 
 struct device_node* pmac_i2c_get_bus_node (struct pmac_i2c_bus*) ; 
 int /*<<< orphan*/  wf_sat_create (struct i2c_adapter*,struct device_node*) ; 

__attribute__((used)) static int wf_sat_attach(struct i2c_adapter *adapter)
{
	struct device_node *busnode, *dev = NULL;
	struct pmac_i2c_bus *bus;

	bus = pmac_i2c_adapter_to_bus(adapter);
	if (bus == NULL)
		return -ENODEV;
	busnode = pmac_i2c_get_bus_node(bus);

	while ((dev = of_get_next_child(busnode, dev)) != NULL)
		if (of_device_is_compatible(dev, "smu-sat"))
			wf_sat_create(adapter, dev);
	return 0;
}