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
typedef  scalar_t__ u8 ;
struct pmac_i2c_bus {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int ENODEV ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct pmac_i2c_bus* pmac_i2c_adapter_to_bus (struct i2c_adapter*) ; 
 struct device_node* pmac_i2c_get_bus_node (struct pmac_i2c_bus*) ; 
 scalar_t__ pmac_i2c_get_dev_addr (struct device_node*) ; 
 int /*<<< orphan*/  pmac_i2c_match_adapter (struct device_node*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  wf_lm75_create (struct i2c_adapter*,scalar_t__,int,char const*) ; 

__attribute__((used)) static int wf_lm75_attach(struct i2c_adapter *adapter)
{
	struct device_node *busnode, *dev;
	struct pmac_i2c_bus *bus;

	DBG("wf_lm75: adapter %s detected\n", adapter->name);

	bus = pmac_i2c_adapter_to_bus(adapter);
	if (bus == NULL)
		return -ENODEV;
	busnode = pmac_i2c_get_bus_node(bus);

	DBG("wf_lm75: bus found, looking for device...\n");

	/* Now look for lm75(s) in there */
	for (dev = NULL;
	     (dev = of_get_next_child(busnode, dev)) != NULL;) {
		const char *loc =
			of_get_property(dev, "hwsensor-location", NULL);
		u8 addr;

		/* We must re-match the adapter in order to properly check
		 * the channel on multibus setups
		 */
		if (!pmac_i2c_match_adapter(dev, adapter))
			continue;
		addr = pmac_i2c_get_dev_addr(dev);
		if (loc == NULL || addr == 0)
			continue;
		/* real lm75 */
		if (of_device_is_compatible(dev, "lm75"))
			wf_lm75_create(adapter, addr, 0, loc);
		/* ds1775 (compatible, better resolution */
		else if (of_device_is_compatible(dev, "ds1775"))
			wf_lm75_create(adapter, addr, 1, loc);
	}
	return 0;
}