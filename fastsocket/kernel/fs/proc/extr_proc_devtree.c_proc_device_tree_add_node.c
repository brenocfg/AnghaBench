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
struct property {char* name; struct property* next; } ;
struct proc_dir_entry {int dummy; } ;
struct device_node {char* full_name; struct property* properties; } ;

/* Variables and functions */
 struct proc_dir_entry* __proc_device_tree_add_prop (struct proc_dir_entry*,struct property*,char const*) ; 
 scalar_t__ duplicate_name (struct proc_dir_entry*,char const*) ; 
 char* fixup_name (struct device_node*,struct proc_dir_entry*,char const*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct proc_dir_entry* proc_mkdir (char const*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  set_node_proc_entry (struct device_node*,struct proc_dir_entry*) ; 
 char* strrchr (char*,char) ; 

void proc_device_tree_add_node(struct device_node *np,
			       struct proc_dir_entry *de)
{
	struct property *pp;
	struct proc_dir_entry *ent;
	struct device_node *child;
	const char *p;

	set_node_proc_entry(np, de);
	for (child = NULL; (child = of_get_next_child(np, child));) {
		/* Use everything after the last slash, or the full name */
		p = strrchr(child->full_name, '/');
		if (!p)
			p = child->full_name;
		else
			++p;

		if (duplicate_name(de, p))
			p = fixup_name(np, de, p);

		ent = proc_mkdir(p, de);
		if (ent == NULL)
			break;
		proc_device_tree_add_node(child, ent);
	}
	of_node_put(child);

	for (pp = np->properties; pp != NULL; pp = pp->next) {
		p = pp->name;

		if (duplicate_name(de, p))
			p = fixup_name(np, de, p);

		ent = __proc_device_tree_add_prop(de, pp, p);
		if (ent == NULL)
			break;
	}
}