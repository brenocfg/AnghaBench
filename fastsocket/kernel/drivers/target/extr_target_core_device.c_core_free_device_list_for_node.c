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
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {struct se_dev_entry** device_list; int /*<<< orphan*/  device_list_lock; } ;
struct se_lun {int dummy; } ;
struct se_dev_entry {int lun_flags; int /*<<< orphan*/  mapped_lun; struct se_lun* se_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 int /*<<< orphan*/  TRANSPORT_LUNFLAGS_NO_ACCESS ; 
 size_t TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  array_free (struct se_dev_entry**,size_t) ; 
 int /*<<< orphan*/  core_disable_device_list_for_node (struct se_lun*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct se_node_acl*,struct se_portal_group*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

int core_free_device_list_for_node(
	struct se_node_acl *nacl,
	struct se_portal_group *tpg)
{
	struct se_dev_entry *deve;
	struct se_lun *lun;
	u32 i;

	if (!nacl->device_list)
		return 0;

	spin_lock_irq(&nacl->device_list_lock);
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		deve = nacl->device_list[i];

		if (!(deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS))
			continue;

		if (!deve->se_lun) {
			pr_err("%s device entries device pointer is"
				" NULL, but Initiator has access.\n",
				tpg->se_tpg_tfo->get_fabric_name());
			continue;
		}
		lun = deve->se_lun;

		spin_unlock_irq(&nacl->device_list_lock);
		core_disable_device_list_for_node(lun, NULL, deve->mapped_lun,
			TRANSPORT_LUNFLAGS_NO_ACCESS, nacl, tpg);
		spin_lock_irq(&nacl->device_list_lock);
	}
	spin_unlock_irq(&nacl->device_list_lock);

	array_free(nacl->device_list, TRANSPORT_MAX_LUNS_PER_TPG);
	nacl->device_list = NULL;

	return 0;
}