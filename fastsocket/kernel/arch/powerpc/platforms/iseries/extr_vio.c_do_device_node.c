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
typedef  int /*<<< orphan*/  unit ;
typedef  int u32 ;
struct vio_resource {int* rsrcname; int* type; int* model; } ;
struct proc_dir_entry {int dummy; } ;
struct device_node {int /*<<< orphan*/  pde; int /*<<< orphan*/  full_name; void* type; void* name; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  add_raw_property (struct device_node*,char*,int,int*) ; 
 int /*<<< orphan*/  add_string_property (struct device_node*,char*,char const*) ; 
 int /*<<< orphan*/  free_node (struct device_node*) ; 
 struct device_node* new_node (char*,struct device_node*) ; 
 int /*<<< orphan*/  of_attach_node (struct device_node*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_device_tree_add_node (struct device_node*,struct proc_dir_entry*) ; 
 struct proc_dir_entry* proc_mkdir (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 scalar_t__ strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static struct device_node *do_device_node(struct device_node *parent,
		const char *name, u32 reg, u32 unit, const char *type,
		const char *compat, struct vio_resource *res)
{
	struct device_node *np;
	char path[32];

	snprintf(path, sizeof(path), "/vdevice/%s@%08x", name, reg);
	np = new_node(path, parent);
	if (!np)
		return NULL;
	if (!add_string_property(np, "name", name) ||
		!add_string_property(np, "device_type", type) ||
		!add_string_property(np, "compatible", compat) ||
		!add_raw_property(np, "reg", sizeof(reg), &reg) ||
		!add_raw_property(np, "linux,unit_address",
			sizeof(unit), &unit)) {
		goto node_free;
	}
	if (res) {
		if (!add_raw_property(np, "linux,vio_rsrcname",
				sizeof(res->rsrcname), res->rsrcname) ||
			!add_raw_property(np, "linux,vio_type",
				sizeof(res->type), res->type) ||
			!add_raw_property(np, "linux,vio_model",
				sizeof(res->model), res->model))
			goto node_free;
	}
	np->name = of_get_property(np, "name", NULL);
	np->type = of_get_property(np, "device_type", NULL);
	of_attach_node(np);
#ifdef CONFIG_PROC_DEVICETREE
	if (parent->pde) {
		struct proc_dir_entry *ent;

		ent = proc_mkdir(strrchr(np->full_name, '/') + 1, parent->pde);
		if (ent)
			proc_device_tree_add_node(np, ent);
	}
#endif
	return np;

 node_free:
	free_node(np);
	return NULL;
}