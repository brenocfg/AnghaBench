#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct config_item {int dummy; } ;
struct config_group {struct config_group** default_groups; struct config_item cg_item; } ;
struct t10_alua_tg_pt_gp {struct config_group tg_pt_gp_group; } ;
struct se_subsystem_api {int dummy; } ;
struct se_hba {int /*<<< orphan*/  hba_access_mutex; struct se_subsystem_api* transport; } ;
struct TYPE_8__ {struct config_group stat_group; } ;
struct TYPE_7__ {struct config_group alua_tg_pt_gps_group; struct t10_alua_tg_pt_gp* default_tg_pt_gp; } ;
struct TYPE_6__ {struct config_group t10_wwn_group; } ;
struct TYPE_5__ {struct config_group da_group; } ;
struct se_device {TYPE_4__ dev_stat_grps; TYPE_3__ t10_alua; TYPE_2__ t10_wwn; struct config_group dev_pr_group; TYPE_1__ dev_attrib; struct config_group dev_group; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct config_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 struct t10_alua_tg_pt_gp* core_alua_allocate_tg_pt_gp (struct se_device*,char*,int) ; 
 int /*<<< orphan*/  core_alua_free_tg_pt_gp (struct t10_alua_tg_pt_gp*) ; 
 struct se_hba* item_to_hba (struct config_item*) ; 
 int /*<<< orphan*/  kfree (struct config_group**) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct se_device* target_alloc_device (struct se_hba*,char const*) ; 
 int /*<<< orphan*/  target_core_alua_tg_pt_gp_cit ; 
 int /*<<< orphan*/  target_core_alua_tg_pt_gps_cit ; 
 int /*<<< orphan*/  target_core_dev_attrib_cit ; 
 int /*<<< orphan*/  target_core_dev_cit ; 
 int /*<<< orphan*/  target_core_dev_pr_cit ; 
 int /*<<< orphan*/  target_core_dev_wwn_cit ; 
 int /*<<< orphan*/  target_core_stat_cit ; 
 int /*<<< orphan*/  target_free_device (struct se_device*) ; 
 int /*<<< orphan*/  target_stat_setup_dev_default_groups (struct se_device*) ; 

__attribute__((used)) static struct config_group *target_core_make_subdev(
	struct config_group *group,
	const char *name)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	struct se_subsystem_api *t;
	struct config_item *hba_ci = &group->cg_item;
	struct se_hba *hba = item_to_hba(hba_ci);
	struct se_device *dev;
	struct config_group *dev_cg = NULL, *tg_pt_gp_cg = NULL;
	struct config_group *dev_stat_grp = NULL;
	int errno = -ENOMEM, ret;

	ret = mutex_lock_interruptible(&hba->hba_access_mutex);
	if (ret)
		return ERR_PTR(ret);
	/*
	 * Locate the struct se_subsystem_api from parent's struct se_hba.
	 */
	t = hba->transport;

	dev = target_alloc_device(hba, name);
	if (!dev)
		goto out_unlock;

	dev_cg = &dev->dev_group;

	dev_cg->default_groups = kmalloc(sizeof(struct config_group *) * 6,
			GFP_KERNEL);
	if (!dev_cg->default_groups)
		goto out_free_device;

	config_group_init_type_name(dev_cg, name, &target_core_dev_cit);
	config_group_init_type_name(&dev->dev_attrib.da_group, "attrib",
			&target_core_dev_attrib_cit);
	config_group_init_type_name(&dev->dev_pr_group, "pr",
			&target_core_dev_pr_cit);
	config_group_init_type_name(&dev->t10_wwn.t10_wwn_group, "wwn",
			&target_core_dev_wwn_cit);
	config_group_init_type_name(&dev->t10_alua.alua_tg_pt_gps_group,
			"alua", &target_core_alua_tg_pt_gps_cit);
	config_group_init_type_name(&dev->dev_stat_grps.stat_group,
			"statistics", &target_core_stat_cit);

	dev_cg->default_groups[0] = &dev->dev_attrib.da_group;
	dev_cg->default_groups[1] = &dev->dev_pr_group;
	dev_cg->default_groups[2] = &dev->t10_wwn.t10_wwn_group;
	dev_cg->default_groups[3] = &dev->t10_alua.alua_tg_pt_gps_group;
	dev_cg->default_groups[4] = &dev->dev_stat_grps.stat_group;
	dev_cg->default_groups[5] = NULL;
	/*
	 * Add core/$HBA/$DEV/alua/default_tg_pt_gp
	 */
	tg_pt_gp = core_alua_allocate_tg_pt_gp(dev, "default_tg_pt_gp", 1);
	if (!tg_pt_gp)
		goto out_free_dev_cg_default_groups;
	dev->t10_alua.default_tg_pt_gp = tg_pt_gp;

	tg_pt_gp_cg = &dev->t10_alua.alua_tg_pt_gps_group;
	tg_pt_gp_cg->default_groups = kmalloc(sizeof(struct config_group *) * 2,
				GFP_KERNEL);
	if (!tg_pt_gp_cg->default_groups) {
		pr_err("Unable to allocate tg_pt_gp_cg->"
				"default_groups\n");
		goto out_free_tg_pt_gp;
	}

	config_group_init_type_name(&tg_pt_gp->tg_pt_gp_group,
			"default_tg_pt_gp", &target_core_alua_tg_pt_gp_cit);
	tg_pt_gp_cg->default_groups[0] = &tg_pt_gp->tg_pt_gp_group;
	tg_pt_gp_cg->default_groups[1] = NULL;
	/*
	 * Add core/$HBA/$DEV/statistics/ default groups
	 */
	dev_stat_grp = &dev->dev_stat_grps.stat_group;
	dev_stat_grp->default_groups = kmalloc(sizeof(struct config_group *) * 4,
				GFP_KERNEL);
	if (!dev_stat_grp->default_groups) {
		pr_err("Unable to allocate dev_stat_grp->default_groups\n");
		goto out_free_tg_pt_gp_cg_default_groups;
	}
	target_stat_setup_dev_default_groups(dev);

	mutex_unlock(&hba->hba_access_mutex);
	return dev_cg;

out_free_tg_pt_gp_cg_default_groups:
	kfree(tg_pt_gp_cg->default_groups);
out_free_tg_pt_gp:
	core_alua_free_tg_pt_gp(tg_pt_gp);
out_free_dev_cg_default_groups:
	kfree(dev_cg->default_groups);
out_free_device:
	target_free_device(dev);
out_unlock:
	mutex_unlock(&hba->hba_access_mutex);
	return ERR_PTR(errno);
}