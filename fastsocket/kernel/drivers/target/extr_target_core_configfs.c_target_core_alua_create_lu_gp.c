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
struct config_item {int dummy; } ;
struct config_group {struct config_item cg_item; } ;
struct t10_alua_lu_gp {struct config_group lu_gp_group; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct t10_alua_lu_gp*) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_item_name (struct config_item*) ; 
 struct t10_alua_lu_gp* core_alua_allocate_lu_gp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_core_alua_lu_gp_cit ; 

__attribute__((used)) static struct config_group *target_core_alua_create_lu_gp(
	struct config_group *group,
	const char *name)
{
	struct t10_alua_lu_gp *lu_gp;
	struct config_group *alua_lu_gp_cg = NULL;
	struct config_item *alua_lu_gp_ci = NULL;

	lu_gp = core_alua_allocate_lu_gp(name, 0);
	if (IS_ERR(lu_gp))
		return NULL;

	alua_lu_gp_cg = &lu_gp->lu_gp_group;
	alua_lu_gp_ci = &alua_lu_gp_cg->cg_item;

	config_group_init_type_name(alua_lu_gp_cg, name,
			&target_core_alua_lu_gp_cit);

	pr_debug("Target_Core_ConfigFS: Allocated ALUA Logical Unit"
		" Group: core/alua/lu_gps/%s\n",
		config_item_name(alua_lu_gp_ci));

	return alua_lu_gp_cg;

}