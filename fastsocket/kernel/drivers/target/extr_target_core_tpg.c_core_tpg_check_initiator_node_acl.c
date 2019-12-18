#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct se_portal_group {TYPE_1__* se_tpg_tfo; int /*<<< orphan*/  acl_node_lock; int /*<<< orphan*/  num_node_acls; int /*<<< orphan*/  acl_node_list; } ;
struct se_node_acl {int dynamic_node_acl; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  acl_list; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  acl_index; struct se_portal_group* se_tpg; int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  acl_pr_ref_count; int /*<<< orphan*/  nacl_sess_lock; int /*<<< orphan*/  device_list_lock; int /*<<< orphan*/  acl_free_comp; int /*<<< orphan*/  acl_kref; int /*<<< orphan*/  acl_sess_list; } ;
struct TYPE_2__ {int (* tpg_check_demo_mode_login_only ) (struct se_portal_group*) ;int /*<<< orphan*/  (* get_fabric_name ) () ;int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* tpg_release_fabric_acl ) (struct se_portal_group*,struct se_node_acl*) ;int /*<<< orphan*/  (* set_default_node_attributes ) (struct se_node_acl*) ;int /*<<< orphan*/  (* tpg_get_default_depth ) (struct se_portal_group*) ;struct se_node_acl* (* tpg_alloc_fabric_acl ) (struct se_portal_group*) ;int /*<<< orphan*/  (* tpg_check_demo_mode ) (struct se_portal_group*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCSI_AUTH_INTR_INDEX ; 
 int /*<<< orphan*/  TRANSPORT_IQN_LEN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ core_create_device_list_for_node (struct se_node_acl*) ; 
 int /*<<< orphan*/  core_free_device_list_for_node (struct se_node_acl*,struct se_portal_group*) ; 
 scalar_t__ core_set_queue_depth_for_node (struct se_portal_group*,struct se_node_acl*) ; 
 int /*<<< orphan*/  core_tpg_add_node_to_devs (struct se_node_acl*,struct se_portal_group*) ; 
 struct se_node_acl* core_tpg_get_initiator_node_acl (struct se_portal_group*,unsigned char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  scsi_get_new_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub10 () ; 
 struct se_node_acl* stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub3 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub4 (struct se_node_acl*) ; 
 int /*<<< orphan*/  stub5 (struct se_portal_group*,struct se_node_acl*) ; 
 int /*<<< orphan*/  stub6 (struct se_portal_group*,struct se_node_acl*) ; 
 int stub7 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub8 () ; 
 int /*<<< orphan*/  stub9 (struct se_portal_group*) ; 

struct se_node_acl *core_tpg_check_initiator_node_acl(
	struct se_portal_group *tpg,
	unsigned char *initiatorname)
{
	struct se_node_acl *acl;

	acl = core_tpg_get_initiator_node_acl(tpg, initiatorname);
	if (acl)
		return acl;

	if (!tpg->se_tpg_tfo->tpg_check_demo_mode(tpg))
		return NULL;

	acl =  tpg->se_tpg_tfo->tpg_alloc_fabric_acl(tpg);
	if (!acl)
		return NULL;

	INIT_LIST_HEAD(&acl->acl_list);
	INIT_LIST_HEAD(&acl->acl_sess_list);
	kref_init(&acl->acl_kref);
	init_completion(&acl->acl_free_comp);
	spin_lock_init(&acl->device_list_lock);
	spin_lock_init(&acl->nacl_sess_lock);
	atomic_set(&acl->acl_pr_ref_count, 0);
	acl->queue_depth = tpg->se_tpg_tfo->tpg_get_default_depth(tpg);
	snprintf(acl->initiatorname, TRANSPORT_IQN_LEN, "%s", initiatorname);
	acl->se_tpg = tpg;
	acl->acl_index = scsi_get_new_index(SCSI_AUTH_INTR_INDEX);
	spin_lock_init(&acl->stats_lock);
	acl->dynamic_node_acl = 1;

	tpg->se_tpg_tfo->set_default_node_attributes(acl);

	if (core_create_device_list_for_node(acl) < 0) {
		tpg->se_tpg_tfo->tpg_release_fabric_acl(tpg, acl);
		return NULL;
	}

	if (core_set_queue_depth_for_node(tpg, acl) < 0) {
		core_free_device_list_for_node(acl, tpg);
		tpg->se_tpg_tfo->tpg_release_fabric_acl(tpg, acl);
		return NULL;
	}
	/*
	 * Here we only create demo-mode MappedLUNs from the active
	 * TPG LUNs if the fabric is not explicitly asking for
	 * tpg_check_demo_mode_login_only() == 1.
	 */
	if ((tpg->se_tpg_tfo->tpg_check_demo_mode_login_only == NULL) ||
	    (tpg->se_tpg_tfo->tpg_check_demo_mode_login_only(tpg) != 1))
		core_tpg_add_node_to_devs(acl, tpg);

	spin_lock_irq(&tpg->acl_node_lock);
	list_add_tail(&acl->acl_list, &tpg->acl_node_list);
	tpg->num_node_acls++;
	spin_unlock_irq(&tpg->acl_node_lock);

	pr_debug("%s_TPG[%u] - Added DYNAMIC ACL with TCQ Depth: %d for %s"
		" Initiator Node: %s\n", tpg->se_tpg_tfo->get_fabric_name(),
		tpg->se_tpg_tfo->tpg_get_tag(tpg), acl->queue_depth,
		tpg->se_tpg_tfo->get_fabric_name(), initiatorname);

	return acl;
}