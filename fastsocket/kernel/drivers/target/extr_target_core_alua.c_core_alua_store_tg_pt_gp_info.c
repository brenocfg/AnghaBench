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
struct t10_alua_tg_pt_gp_member {int /*<<< orphan*/  tg_pt_gp_mem_lock; struct t10_alua_tg_pt_gp* tg_pt_gp; } ;
struct TYPE_8__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_id; TYPE_4__ tg_pt_gp_group; } ;
struct se_portal_group {TYPE_2__* se_tpg_tfo; } ;
struct se_port {struct t10_alua_tg_pt_gp_member* sep_alua_tg_pt_gp_mem; struct se_lun* sep_lun; struct se_portal_group* sep_tpg; } ;
struct TYPE_7__ {int /*<<< orphan*/  cg_item; } ;
struct se_lun {TYPE_3__ lun_group; struct se_device* lun_se_dev; } ;
struct TYPE_5__ {struct t10_alua_tg_pt_gp* default_tg_pt_gp; } ;
struct se_device {TYPE_1__ t10_alua; } ;
typedef  size_t ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* tpg_get_wwn ) (struct se_portal_group*) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int TG_PT_GROUP_NAME_BUF ; 
 int /*<<< orphan*/  __core_alua_attach_tg_pt_gp_mem (struct t10_alua_tg_pt_gp_member*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  __core_alua_drop_tg_pt_gp_mem (struct t10_alua_tg_pt_gp_member*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 struct t10_alua_tg_pt_gp* core_alua_get_tg_pt_gp_by_name (struct se_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_alua_put_tg_pt_gp_from_name (struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (unsigned char*) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub3 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub4 (struct se_portal_group*) ; 

ssize_t core_alua_store_tg_pt_gp_info(
	struct se_port *port,
	const char *page,
	size_t count)
{
	struct se_portal_group *tpg;
	struct se_lun *lun;
	struct se_device *dev = port->sep_lun->lun_se_dev;
	struct t10_alua_tg_pt_gp *tg_pt_gp = NULL, *tg_pt_gp_new = NULL;
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem;
	unsigned char buf[TG_PT_GROUP_NAME_BUF];
	int move = 0;

	tpg = port->sep_tpg;
	lun = port->sep_lun;

	tg_pt_gp_mem = port->sep_alua_tg_pt_gp_mem;
	if (!tg_pt_gp_mem)
		return 0;

	if (count > TG_PT_GROUP_NAME_BUF) {
		pr_err("ALUA Target Port Group alias too large!\n");
		return -EINVAL;
	}
	memset(buf, 0, TG_PT_GROUP_NAME_BUF);
	memcpy(buf, page, count);
	/*
	 * Any ALUA target port group alias besides "NULL" means we will be
	 * making a new group association.
	 */
	if (strcmp(strstrip(buf), "NULL")) {
		/*
		 * core_alua_get_tg_pt_gp_by_name() will increment reference to
		 * struct t10_alua_tg_pt_gp.  This reference is released with
		 * core_alua_put_tg_pt_gp_from_name() below.
		 */
		tg_pt_gp_new = core_alua_get_tg_pt_gp_by_name(dev,
					strstrip(buf));
		if (!tg_pt_gp_new)
			return -ENODEV;
	}

	spin_lock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
	tg_pt_gp = tg_pt_gp_mem->tg_pt_gp;
	if (tg_pt_gp) {
		/*
		 * Clearing an existing tg_pt_gp association, and replacing
		 * with the default_tg_pt_gp.
		 */
		if (!tg_pt_gp_new) {
			pr_debug("Target_Core_ConfigFS: Moving"
				" %s/tpgt_%hu/%s from ALUA Target Port Group:"
				" alua/%s, ID: %hu back to"
				" default_tg_pt_gp\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				tpg->se_tpg_tfo->tpg_get_tag(tpg),
				config_item_name(&lun->lun_group.cg_item),
				config_item_name(
					&tg_pt_gp->tg_pt_gp_group.cg_item),
				tg_pt_gp->tg_pt_gp_id);

			__core_alua_drop_tg_pt_gp_mem(tg_pt_gp_mem, tg_pt_gp);
			__core_alua_attach_tg_pt_gp_mem(tg_pt_gp_mem,
					dev->t10_alua.default_tg_pt_gp);
			spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);

			return count;
		}
		/*
		 * Removing existing association of tg_pt_gp_mem with tg_pt_gp
		 */
		__core_alua_drop_tg_pt_gp_mem(tg_pt_gp_mem, tg_pt_gp);
		move = 1;
	}
	/*
	 * Associate tg_pt_gp_mem with tg_pt_gp_new.
	 */
	__core_alua_attach_tg_pt_gp_mem(tg_pt_gp_mem, tg_pt_gp_new);
	spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
	pr_debug("Target_Core_ConfigFS: %s %s/tpgt_%hu/%s to ALUA"
		" Target Port Group: alua/%s, ID: %hu\n", (move) ?
		"Moving" : "Adding", tpg->se_tpg_tfo->tpg_get_wwn(tpg),
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		config_item_name(&lun->lun_group.cg_item),
		config_item_name(&tg_pt_gp_new->tg_pt_gp_group.cg_item),
		tg_pt_gp_new->tg_pt_gp_id);

	core_alua_put_tg_pt_gp_from_name(tg_pt_gp_new);
	return count;
}