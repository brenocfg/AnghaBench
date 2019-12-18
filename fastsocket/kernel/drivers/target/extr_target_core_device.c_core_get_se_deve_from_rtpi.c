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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_port {scalar_t__ sep_rtpi; } ;
struct se_node_acl {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; struct se_portal_group* se_tpg; } ;
struct se_lun {struct se_port* lun_sep; } ;
struct se_dev_entry {int lun_flags; int /*<<< orphan*/  pr_ref_count; struct se_lun* se_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 size_t TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_inc () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

struct se_dev_entry *core_get_se_deve_from_rtpi(
	struct se_node_acl *nacl,
	u16 rtpi)
{
	struct se_dev_entry *deve;
	struct se_lun *lun;
	struct se_port *port;
	struct se_portal_group *tpg = nacl->se_tpg;
	u32 i;

	spin_lock_irq(&nacl->device_list_lock);
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		deve = nacl->device_list[i];

		if (!(deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS))
			continue;

		lun = deve->se_lun;
		if (!lun) {
			pr_err("%s device entries device pointer is"
				" NULL, but Initiator has access.\n",
				tpg->se_tpg_tfo->get_fabric_name());
			continue;
		}
		port = lun->lun_sep;
		if (!port) {
			pr_err("%s device entries device pointer is"
				" NULL, but Initiator has access.\n",
				tpg->se_tpg_tfo->get_fabric_name());
			continue;
		}
		if (port->sep_rtpi != rtpi)
			continue;

		atomic_inc(&deve->pr_ref_count);
		smp_mb__after_atomic_inc();
		spin_unlock_irq(&nacl->device_list_lock);

		return deve;
	}
	spin_unlock_irq(&nacl->device_list_lock);

	return NULL;
}