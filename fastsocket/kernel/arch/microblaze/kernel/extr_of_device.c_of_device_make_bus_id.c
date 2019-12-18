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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct of_device {int /*<<< orphan*/  dev; struct device_node* node; } ;
struct device_node {int name; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ OF_BAD_ADDR ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,unsigned long long,int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_translate_address (struct device_node*,int /*<<< orphan*/  const*) ; 

void of_device_make_bus_id(struct of_device *dev)
{
	static atomic_t bus_no_reg_magic;
	struct device_node *node = dev->node;
	const u32 *reg;
	u64 addr;
	int magic;

	/*
	 * For MMIO, get the physical address
	 */
	reg = of_get_property(node, "reg", NULL);
	if (reg) {
		addr = of_translate_address(node, reg);
		if (addr != OF_BAD_ADDR) {
			dev_set_name(&dev->dev, "%llx.%s",
				     (unsigned long long)addr, node->name);
			return;
		}
	}

	/*
	 * No BusID, use the node name and add a globally incremented
	 * counter (and pray...)
	 */
	magic = atomic_add_return(1, &bus_no_reg_magic);
	dev_set_name(&dev->dev, "%s.%d", node->name, magic - 1);
}