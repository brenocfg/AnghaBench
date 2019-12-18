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
struct se_node_acl {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;
struct se_dev_entry {size_t lun_flags; } ;

/* Variables and functions */
 size_t TRANSPORT_LUNFLAGS_READ_ONLY ; 
 size_t TRANSPORT_LUNFLAGS_READ_WRITE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void core_update_device_list_access(
	u32 mapped_lun,
	u32 lun_access,
	struct se_node_acl *nacl)
{
	struct se_dev_entry *deve;

	spin_lock_irq(&nacl->device_list_lock);
	deve = nacl->device_list[mapped_lun];
	if (lun_access & TRANSPORT_LUNFLAGS_READ_WRITE) {
		deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_ONLY;
		deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_WRITE;
	} else {
		deve->lun_flags &= ~TRANSPORT_LUNFLAGS_READ_WRITE;
		deve->lun_flags |= TRANSPORT_LUNFLAGS_READ_ONLY;
	}
	spin_unlock_irq(&nacl->device_list_lock);
}