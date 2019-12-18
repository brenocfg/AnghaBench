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
struct property {int /*<<< orphan*/  name; struct property* next; } ;
struct device_node {struct property* properties; struct device_node* allnext; } ;

/* Variables and functions */
 struct device_node* allnodes ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_prop_cmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct device_node *of_find_node_with_property(struct device_node *from,
	const char *prop_name)
{
	struct device_node *np;
	struct property *pp;

	read_lock(&devtree_lock);
	np = from ? from->allnext : allnodes;
	for (; np; np = np->allnext) {
		for (pp = np->properties; pp != 0; pp = pp->next) {
			if (of_prop_cmp(pp->name, prop_name) == 0) {
				of_node_get(np);
				goto out;
			}
		}
	}
out:
	of_node_put(from);
	read_unlock(&devtree_lock);
	return np;
}