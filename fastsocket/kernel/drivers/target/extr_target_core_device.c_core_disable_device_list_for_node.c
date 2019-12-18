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
typedef  size_t u32 ;
struct se_portal_group {int dummy; } ;
struct se_port {int /*<<< orphan*/  sep_alua_lock; } ;
struct se_node_acl {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;
struct se_lun_acl {int dummy; } ;
struct se_lun {int /*<<< orphan*/  lun_se_dev; struct se_port* lun_sep; } ;
struct se_dev_entry {int /*<<< orphan*/  attach_count; scalar_t__ creation_time; scalar_t__ lun_flags; int /*<<< orphan*/ * se_lun_acl; int /*<<< orphan*/ * se_lun; int /*<<< orphan*/  pr_ref_count; int /*<<< orphan*/  alua_port_list; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_scsi3_free_pr_reg_from_nacl (int /*<<< orphan*/ ,struct se_node_acl*) ; 
 int /*<<< orphan*/  core_scsi3_ua_release_all (struct se_dev_entry*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int core_disable_device_list_for_node(
	struct se_lun *lun,
	struct se_lun_acl *lun_acl,
	u32 mapped_lun,
	u32 lun_access,
	struct se_node_acl *nacl,
	struct se_portal_group *tpg)
{
	struct se_port *port = lun->lun_sep;
	struct se_dev_entry *deve = nacl->device_list[mapped_lun];

	/*
	 * If the MappedLUN entry is being disabled, the entry in
	 * port->sep_alua_list must be removed now before clearing the
	 * struct se_dev_entry pointers below as logic in
	 * core_alua_do_transition_tg_pt() depends on these being present.
	 *
	 * deve->se_lun_acl will be NULL for demo-mode created LUNs
	 * that have not been explicitly converted to MappedLUNs ->
	 * struct se_lun_acl, but we remove deve->alua_port_list from
	 * port->sep_alua_list. This also means that active UAs and
	 * NodeACL context specific PR metadata for demo-mode
	 * MappedLUN *deve will be released below..
	 */
	spin_lock_bh(&port->sep_alua_lock);
	list_del(&deve->alua_port_list);
	spin_unlock_bh(&port->sep_alua_lock);
	/*
	 * Wait for any in process SPEC_I_PT=1 or REGISTER_AND_MOVE
	 * PR operation to complete.
	 */
	while (atomic_read(&deve->pr_ref_count) != 0)
		cpu_relax();

	spin_lock_irq(&nacl->device_list_lock);
	/*
	 * Disable struct se_dev_entry LUN ACL mapping
	 */
	core_scsi3_ua_release_all(deve);
	deve->se_lun = NULL;
	deve->se_lun_acl = NULL;
	deve->lun_flags = 0;
	deve->creation_time = 0;
	deve->attach_count--;
	spin_unlock_irq(&nacl->device_list_lock);

	core_scsi3_free_pr_reg_from_nacl(lun->lun_se_dev, nacl);
	return 0;
}