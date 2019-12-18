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
struct device_node {int /*<<< orphan*/  parent; int /*<<< orphan*/  kref; int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OF_DYNAMIC ; 
 int /*<<< orphan*/  kfree (struct device_node*) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct device_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_set_flag (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct device_node *new_node(const char *path,
		struct device_node *parent)
{
	struct device_node *np = kzalloc(sizeof(*np), GFP_KERNEL);

	if (!np)
		return NULL;
	np->full_name = kmalloc(strlen(path) + 1, GFP_KERNEL);
	if (!np->full_name) {
		kfree(np);
		return NULL;
	}
	strcpy(np->full_name, path);
	of_node_set_flag(np, OF_DYNAMIC);
	kref_init(&np->kref);
	np->parent = of_node_get(parent);
	return np;
}