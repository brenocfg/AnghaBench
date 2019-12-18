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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct of_bus {unsigned int (* get_flags ) (int /*<<< orphan*/  const*) ;int /*<<< orphan*/  addresses; int /*<<< orphan*/  (* count_cells ) (struct device_node*,int*,int*) ;} ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_CHECK_COUNTS (int,int) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct of_bus* of_match_bus (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_read_number (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub1 (struct device_node*,int*,int*) ; 
 unsigned int stub2 (int /*<<< orphan*/  const*) ; 

const u32 *of_get_address(struct device_node *dev, int index, u64 *size,
		    unsigned int *flags)
{
	const u32 *prop;
	unsigned int psize;
	struct device_node *parent;
	struct of_bus *bus;
	int onesize, i, na, ns;

	/* Get parent & match bus type */
	parent = of_get_parent(dev);
	if (parent == NULL)
		return NULL;
	bus = of_match_bus(parent);
	bus->count_cells(dev, &na, &ns);
	of_node_put(parent);
	if (!OF_CHECK_COUNTS(na, ns))
		return NULL;

	/* Get "reg" or "assigned-addresses" property */
	prop = of_get_property(dev, bus->addresses, &psize);
	if (prop == NULL)
		return NULL;
	psize /= 4;

	onesize = na + ns;
	for (i = 0; psize >= onesize; psize -= onesize, prop += onesize, i++)
		if (i == index) {
			if (size)
				*size = of_read_number(prop + na, ns);
			if (flags)
				*flags = bus->get_flags(prop);
			return prop;
		}
	return NULL;
}