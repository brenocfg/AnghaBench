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
struct device_node {struct device_node* allnext; } ;

/* Variables and functions */
 struct device_node* allnodes ; 
 int /*<<< orphan*/  devtree_lock ; 
 scalar_t__ of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct device_node *of_find_all_nodes(struct device_node *prev)
{
	struct device_node *np;

	read_lock(&devtree_lock);
	np = prev ? prev->allnext : allnodes;
	for (; np != 0; np = np->allnext)
		if (of_node_get(np))
			break;
	of_node_put(prev);
	read_unlock(&devtree_lock);
	return np;
}