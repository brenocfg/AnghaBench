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
struct property {struct property* data; struct property* full_name; struct property* deadprops; struct property* value; struct property* name; struct property* next; int /*<<< orphan*/  kref; struct property* properties; } ;
struct kref {int dummy; } ;
struct device_node {struct device_node* data; struct device_node* full_name; struct device_node* deadprops; struct device_node* value; struct device_node* name; struct device_node* next; int /*<<< orphan*/  kref; struct device_node* properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_DETACHED ; 
 int /*<<< orphan*/  OF_DYNAMIC ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct property* kref_to_device_node (struct kref*) ; 
 int /*<<< orphan*/  of_node_check_flag (struct property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,struct property*) ; 

__attribute__((used)) static void of_node_release(struct kref *kref)
{
	struct device_node *node = kref_to_device_node(kref);
	struct property *prop = node->properties;

	/* We should never be releasing nodes that haven't been detached. */
	if (!of_node_check_flag(node, OF_DETACHED)) {
		printk("WARNING: Bad of_node_put() on %s\n", node->full_name);
		dump_stack();
		kref_init(&node->kref);
		return;
	}

	if (!of_node_check_flag(node, OF_DYNAMIC))
		return;

	while (prop) {
		struct property *next = prop->next;
		kfree(prop->name);
		kfree(prop->value);
		kfree(prop);
		prop = next;

		if (!prop) {
			prop = node->deadprops;
			node->deadprops = NULL;
		}
	}
	kfree(node->full_name);
	kfree(node->data);
	kfree(node);
}