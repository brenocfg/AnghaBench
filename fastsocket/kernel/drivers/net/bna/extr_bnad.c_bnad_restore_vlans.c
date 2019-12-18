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
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_1__* rx_info; int /*<<< orphan*/  vlan_grp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 scalar_t__ VLAN_GROUP_ARRAY_LEN ; 
 int /*<<< orphan*/  bna_rx_vlan_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vlan_group_get_device (int /*<<< orphan*/ ,scalar_t__) ; 

void
bnad_restore_vlans(struct bnad *bnad, u32 rx_id)
{
	u16 vlan_id;
	unsigned long flags;

	if (!bnad->vlan_grp)
		return;

	for (vlan_id = 0; vlan_id < VLAN_GROUP_ARRAY_LEN; vlan_id++) {
		if (!vlan_group_get_device(bnad->vlan_grp, vlan_id))
			continue;
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bna_rx_vlan_add(bnad->rx_info[rx_id].rx, vlan_id);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	}
}