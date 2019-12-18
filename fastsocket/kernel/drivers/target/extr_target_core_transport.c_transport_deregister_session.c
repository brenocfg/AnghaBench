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
struct target_core_fabric_ops {int /*<<< orphan*/  (* get_fabric_name ) () ;int /*<<< orphan*/  (* tpg_release_fabric_acl ) (struct se_portal_group*,struct se_node_acl*) ;int /*<<< orphan*/  (* tpg_check_demo_mode_cache ) (struct se_portal_group*) ;} ;
struct se_session {struct se_node_acl* se_node_acl; int /*<<< orphan*/ * fabric_sess_ptr; struct se_portal_group* se_tpg; int /*<<< orphan*/  sess_list; } ;
struct se_portal_group {struct target_core_fabric_ops* se_tpg_tfo; int /*<<< orphan*/  acl_node_lock; int /*<<< orphan*/  num_node_acls; int /*<<< orphan*/  session_lock; } ;
struct se_node_acl {int /*<<< orphan*/  acl_list; scalar_t__ dynamic_node_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_free_device_list_for_node (struct se_node_acl*,struct se_portal_group*) ; 
 int /*<<< orphan*/  core_tpg_wait_for_nacl_pr_ref (struct se_node_acl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*,struct se_node_acl*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  target_put_nacl (struct se_node_acl*) ; 
 int /*<<< orphan*/  transport_free_session (struct se_session*) ; 

void transport_deregister_session(struct se_session *se_sess)
{
	struct se_portal_group *se_tpg = se_sess->se_tpg;
	struct target_core_fabric_ops *se_tfo;
	struct se_node_acl *se_nacl;
	unsigned long flags;
	bool comp_nacl = true;

	if (!se_tpg) {
		transport_free_session(se_sess);
		return;
	}
	se_tfo = se_tpg->se_tpg_tfo;

	spin_lock_irqsave(&se_tpg->session_lock, flags);
	list_del(&se_sess->sess_list);
	se_sess->se_tpg = NULL;
	se_sess->fabric_sess_ptr = NULL;
	spin_unlock_irqrestore(&se_tpg->session_lock, flags);

	/*
	 * Determine if we need to do extra work for this initiator node's
	 * struct se_node_acl if it had been previously dynamically generated.
	 */
	se_nacl = se_sess->se_node_acl;

	spin_lock_irqsave(&se_tpg->acl_node_lock, flags);
	if (se_nacl && se_nacl->dynamic_node_acl) {
		if (!se_tfo->tpg_check_demo_mode_cache(se_tpg)) {
			list_del(&se_nacl->acl_list);
			se_tpg->num_node_acls--;
			spin_unlock_irqrestore(&se_tpg->acl_node_lock, flags);
			core_tpg_wait_for_nacl_pr_ref(se_nacl);
			core_free_device_list_for_node(se_nacl, se_tpg);
			se_tfo->tpg_release_fabric_acl(se_tpg, se_nacl);

			comp_nacl = false;
			spin_lock_irqsave(&se_tpg->acl_node_lock, flags);
		}
	}
	spin_unlock_irqrestore(&se_tpg->acl_node_lock, flags);

	pr_debug("TARGET_CORE[%s]: Deregistered fabric_sess\n",
		se_tpg->se_tpg_tfo->get_fabric_name());
	/*
	 * If last kref is dropping now for an explict NodeACL, awake sleeping
	 * ->acl_free_comp caller to wakeup configfs se_node_acl->acl_group
	 * removal context.
	 */
	if (se_nacl && comp_nacl == true)
		target_put_nacl(se_nacl);

	transport_free_session(se_sess);
}