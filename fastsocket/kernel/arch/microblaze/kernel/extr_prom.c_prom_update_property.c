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
struct property {struct property* next; } ;
struct device_node {scalar_t__ pde; struct property* deadprops; struct property* properties; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  proc_device_tree_update_prop (scalar_t__,struct property*,struct property*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int prom_update_property(struct device_node *np,
			 struct property *newprop,
			 struct property *oldprop)
{
	struct property **next;
	unsigned long flags;
	int found = 0;

	write_lock_irqsave(&devtree_lock, flags);
	next = &np->properties;
	while (*next) {
		if (*next == oldprop) {
			/* found the node */
			newprop->next = oldprop->next;
			*next = newprop;
			oldprop->next = np->deadprops;
			np->deadprops = oldprop;
			found = 1;
			break;
		}
		next = &(*next)->next;
	}
	write_unlock_irqrestore(&devtree_lock, flags);

	if (!found)
		return -ENODEV;

#ifdef CONFIG_PROC_DEVICETREE
	/* try to add to proc as well if it was initialized */
	if (np->pde)
		proc_device_tree_update_prop(np->pde, newprop, oldprop);
#endif /* CONFIG_PROC_DEVICETREE */

	return 0;
}