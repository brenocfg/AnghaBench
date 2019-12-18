#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct t10_alua_lu_gp_member {int /*<<< orphan*/  lu_gp_mem_lock; struct t10_alua_lu_gp* lu_gp; } ;
struct TYPE_6__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_id; TYPE_3__ lu_gp_group; } ;
struct TYPE_4__ {int /*<<< orphan*/  cg_item; } ;
struct se_hba {TYPE_1__ hba_group; } ;
struct TYPE_5__ {int /*<<< orphan*/  cg_item; } ;
struct se_device {TYPE_2__ dev_group; struct t10_alua_lu_gp_member* dev_alua_lu_gp_mem; struct se_hba* se_hba; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int LU_GROUP_NAME_BUF ; 
 int /*<<< orphan*/  __core_alua_attach_lu_gp_mem (struct t10_alua_lu_gp_member*,struct t10_alua_lu_gp*) ; 
 int /*<<< orphan*/  __core_alua_drop_lu_gp_mem (struct t10_alua_lu_gp_member*,struct t10_alua_lu_gp*) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 struct t10_alua_lu_gp* core_alua_get_lu_gp_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_alua_put_lu_gp_from_name (struct t10_alua_lu_gp*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (unsigned char*) ; 

__attribute__((used)) static ssize_t target_core_store_alua_lu_gp(
	void *p,
	const char *page,
	size_t count)
{
	struct se_device *dev = p;
	struct se_hba *hba = dev->se_hba;
	struct t10_alua_lu_gp *lu_gp = NULL, *lu_gp_new = NULL;
	struct t10_alua_lu_gp_member *lu_gp_mem;
	unsigned char buf[LU_GROUP_NAME_BUF];
	int move = 0;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	if (!lu_gp_mem)
		return 0;

	if (count > LU_GROUP_NAME_BUF) {
		pr_err("ALUA LU Group Alias too large!\n");
		return -EINVAL;
	}
	memset(buf, 0, LU_GROUP_NAME_BUF);
	memcpy(buf, page, count);
	/*
	 * Any ALUA logical unit alias besides "NULL" means we will be
	 * making a new group association.
	 */
	if (strcmp(strstrip(buf), "NULL")) {
		/*
		 * core_alua_get_lu_gp_by_name() will increment reference to
		 * struct t10_alua_lu_gp.  This reference is released with
		 * core_alua_get_lu_gp_by_name below().
		 */
		lu_gp_new = core_alua_get_lu_gp_by_name(strstrip(buf));
		if (!lu_gp_new)
			return -ENODEV;
	}

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	if (lu_gp) {
		/*
		 * Clearing an existing lu_gp association, and replacing
		 * with NULL
		 */
		if (!lu_gp_new) {
			pr_debug("Target_Core_ConfigFS: Releasing %s/%s"
				" from ALUA LU Group: core/alua/lu_gps/%s, ID:"
				" %hu\n",
				config_item_name(&hba->hba_group.cg_item),
				config_item_name(&dev->dev_group.cg_item),
				config_item_name(&lu_gp->lu_gp_group.cg_item),
				lu_gp->lu_gp_id);

			__core_alua_drop_lu_gp_mem(lu_gp_mem, lu_gp);
			spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

			return count;
		}
		/*
		 * Removing existing association of lu_gp_mem with lu_gp
		 */
		__core_alua_drop_lu_gp_mem(lu_gp_mem, lu_gp);
		move = 1;
	}
	/*
	 * Associate lu_gp_mem with lu_gp_new.
	 */
	__core_alua_attach_lu_gp_mem(lu_gp_mem, lu_gp_new);
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	pr_debug("Target_Core_ConfigFS: %s %s/%s to ALUA LU Group:"
		" core/alua/lu_gps/%s, ID: %hu\n",
		(move) ? "Moving" : "Adding",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		config_item_name(&lu_gp_new->lu_gp_group.cg_item),
		lu_gp_new->lu_gp_id);

	core_alua_put_lu_gp_from_name(lu_gp_new);
	return count;
}