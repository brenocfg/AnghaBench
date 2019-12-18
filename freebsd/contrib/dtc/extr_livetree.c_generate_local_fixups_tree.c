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
struct dt_info {int /*<<< orphan*/  dt; } ;

/* Variables and functions */
 int /*<<< orphan*/  any_local_fixup_tree (struct dt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_root_node (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generate_local_fixups_tree_internal (struct dt_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void generate_local_fixups_tree(struct dt_info *dti, char *name)
{
	if (!any_local_fixup_tree(dti, dti->dt))
		return;
	generate_local_fixups_tree_internal(dti, build_root_node(dti->dt, name),
					    dti->dt);
}