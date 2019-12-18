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
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int EINVAL ; 
 int OF_IMAP_OLDWORLD_MAC ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 struct device_node* of_irq_find_parent (struct device_node*) ; 
 int of_irq_map_oldworld (struct device_node*,int,struct of_irq*) ; 
 int of_irq_map_raw (struct device_node*,int const*,int,int const*,struct of_irq*) ; 
 int of_irq_workarounds ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int of_irq_map_one(struct device_node *device, int index, struct of_irq *out_irq)
{
	struct device_node *p;
	const u32 *intspec, *tmp, *addr;
	u32 intsize, intlen;
	int res = -EINVAL;

	DBG("of_irq_map_one: dev=%s, index=%d\n", device->full_name, index);

	/* OldWorld mac stuff is "special", handle out of line */
	if (of_irq_workarounds & OF_IMAP_OLDWORLD_MAC)
		return of_irq_map_oldworld(device, index, out_irq);

	/* Get the interrupts property */
	intspec = of_get_property(device, "interrupts", &intlen);
	if (intspec == NULL)
		return -EINVAL;
	intlen /= sizeof(u32);

	/* Get the reg property (if any) */
	addr = of_get_property(device, "reg", NULL);

	/* Look for the interrupt parent. */
	p = of_irq_find_parent(device);
	if (p == NULL)
		return -EINVAL;

	/* Get size of interrupt specifier */
	tmp = of_get_property(p, "#interrupt-cells", NULL);
	if (tmp == NULL)
		goto out;
	intsize = *tmp;

	DBG(" intsize=%d intlen=%d\n", intsize, intlen);

	/* Check index */
	if ((index + 1) * intsize > intlen)
		goto out;

	/* Get new specifier and map it */
	res = of_irq_map_raw(p, intspec + index * intsize, intsize,
			     addr, out_irq);
out:
	of_node_put(p);
	return res;
}