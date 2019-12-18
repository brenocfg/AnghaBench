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
struct se_port {int /*<<< orphan*/  sep_alua_lock; int /*<<< orphan*/  sep_alua_list; } ;
struct se_node_acl {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;
struct se_lun_acl {int dummy; } ;
struct se_lun {struct se_port* lun_sep; } ;
struct se_dev_entry {int lun_flags; size_t mapped_lun; int /*<<< orphan*/  alua_port_list; int /*<<< orphan*/  attach_count; int /*<<< orphan*/  creation_time; struct se_lun_acl* se_lun_acl; struct se_lun* se_lun; } ;

/* Variables and functions */
 int EINVAL ; 
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 int TRANSPORT_LUNFLAGS_READ_ONLY ; 
 size_t TRANSPORT_LUNFLAGS_READ_WRITE ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int core_enable_device_list_for_node(
	struct se_lun *lun,
	struct se_lun_acl *lun_acl,
	u32 mapped_lun,
	u32 lun_access,
	struct se_node_acl *nacl,
	struct se_portal_group *tpg)
{
	struct se_port *port = lun->lun_sep;
	struct se_dev_entry *deve;

	spin_lock_irq(&nacl->device_list_lock);

	deve = nacl->device_list[mapped_lun];

	/*
	 * Check if the call is handling demo mode -> explict LUN ACL
	 * transition.  This transition must be for the same struct se_lun
	 * + mapped_lun that was setup in demo mode..
	 */
	if (deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS) {
		if (deve->se_lun_acl != NULL) {
			pr_err("struct se_dev_entry->se_lun_acl"
			       " already set for demo mode -> explict"
			       " LUN ACL transition\n");
			spin_unlock_irq(&nacl->device_list_lock);
			return -EINVAL;
		}
		if (deve->se_lun != lun) {
			pr_err("struct se_dev_entry->se_lun does"
			       " match passed struct se_lun for demo mode"
			       " -> explict LUN ACL transition\n");
			spin_unlock_irq(&nacl->device_list_lock);
			return -EINVAL;
		}
		deve->se_lun_acl = lun_acl;

		if (lun_access & TRANSPORT_LUNFLAGS_READ_WRITE) {
			deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_ONLY;
			deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_WRITE;
		} else {
			deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_WRITE;
			deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_ONLY;
		}

		spin_unlock_irq(&nacl->device_list_lock);
		return 0;
	}

	deve->se_lun = lun;
	deve->se_lun_acl = lun_acl;
	deve->mapped_lun = mapped_lun;
	deve->lun_flags |= TRANSPORT_LUNFLAGS_INITIATOR_ACCESS;

	if (lun_access & TRANSPORT_LUNFLAGS_READ_WRITE) {
		deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_ONLY;
		deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_WRITE;
	} else {
		deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_WRITE;
		deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_ONLY;
	}

	deve->creation_time = get_jiffies_64();
	deve->attach_count++;
	spin_unlock_irq(&nacl->device_list_lock);

	spin_lock_bh(&port->sep_alua_lock);
	list_add_tail(&deve->alua_port_list, &port->sep_alua_list);
	spin_unlock_bh(&port->sep_alua_lock);

	return 0;
}