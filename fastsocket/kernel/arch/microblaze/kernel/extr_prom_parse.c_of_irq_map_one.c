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
typedef  int u32 ;
struct of_irq {int dummy; } ;
struct device_node {int full_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int of_irq_map_raw (struct device_node*,int const*,int,int const*,struct of_irq*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,int const,int) ; 

int of_irq_map_one(struct device_node *device,
			int index, struct of_irq *out_irq)
{
	struct device_node *p;
	const u32 *intspec, *tmp, *addr;
	u32 intsize, intlen;
	int res;

	pr_debug("of_irq_map_one: dev=%s, index=%d\n",
			device->full_name, index);

	/* Get the interrupts property */
	intspec = of_get_property(device, "interrupts", (int *) &intlen);
	if (intspec == NULL)
		return -EINVAL;
	intlen /= sizeof(u32);

	pr_debug(" intspec=%d intlen=%d\n", *intspec, intlen);

	/* Get the reg property (if any) */
	addr = of_get_property(device, "reg", NULL);

	/* Look for the interrupt parent. */
	p = of_irq_find_parent(device);
	if (p == NULL)
		return -EINVAL;

	/* Get size of interrupt specifier */
	tmp = of_get_property(p, "#interrupt-cells", NULL);
	if (tmp == NULL) {
		of_node_put(p);
		return -EINVAL;
	}
	intsize = *tmp;

	pr_debug(" intsize=%d intlen=%d\n", intsize, intlen);

	/* Check index */
	if ((index + 1) * intsize > intlen)
		return -EINVAL;

	/* Get new specifier and map it */
	res = of_irq_map_raw(p, intspec + index * intsize, intsize,
				addr, out_irq);
	of_node_put(p);
	return res;
}