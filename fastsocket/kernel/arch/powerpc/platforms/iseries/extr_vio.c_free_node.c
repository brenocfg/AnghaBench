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
struct device_node {struct device_node* full_name; int /*<<< orphan*/  parent; struct property* properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_property (struct property*) ; 
 int /*<<< orphan*/  kfree (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_node(struct device_node *np)
{
	struct property *next;
	struct property *prop;

	next = np->properties;
	while (next) {
		prop = next;
		next = prop->next;
		free_property(prop);
	}
	of_node_put(np->parent);
	kfree(np->full_name);
	kfree(np);
}