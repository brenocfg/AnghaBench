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
struct device_node {scalar_t__ type; struct device_node* allnext; } ;

/* Variables and functions */
 struct device_node* allnodes ; 
 int /*<<< orphan*/  devtree_lock ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char const*) ; 
 scalar_t__ of_node_cmp (scalar_t__,char const*) ; 
 scalar_t__ of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct device_node *of_find_compatible_node(struct device_node *from,
	const char *type, const char *compatible)
{
	struct device_node *np;

	read_lock(&devtree_lock);
	np = from ? from->allnext : allnodes;
	for (; np; np = np->allnext) {
		if (type
		    && !(np->type && (of_node_cmp(np->type, type) == 0)))
			continue;
		if (of_device_is_compatible(np, compatible) && of_node_get(np))
			break;
	}
	of_node_put(from);
	read_unlock(&devtree_lock);
	return np;
}