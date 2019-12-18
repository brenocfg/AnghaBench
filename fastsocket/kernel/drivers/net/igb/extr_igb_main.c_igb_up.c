#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int get_link_status; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int num_q_vectors; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  netdev; scalar_t__ vfs_allocated_count; TYPE_2__** q_vector; scalar_t__ msix_entries; int /*<<< orphan*/  state; struct e1000_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_PFRSTD ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_assign_vector (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_configure (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_configure_msix (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_irq_enable (struct igb_adapter*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int igb_up(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	int i;

	/* hardware has been reset, we need to reload some things */
	igb_configure(adapter);

	clear_bit(__IGB_DOWN, &adapter->state);

	for (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&(adapter->q_vector[i]->napi));

	if (adapter->msix_entries)
		igb_configure_msix(adapter);
	else
		igb_assign_vector(adapter->q_vector[0], 0);

	/* Clear any pending interrupts. */
	rd32(E1000_ICR);
	igb_irq_enable(adapter);

	/* notify VFs that reset has been completed */
	if (adapter->vfs_allocated_count) {
		u32 reg_data = rd32(E1000_CTRL_EXT);
		reg_data |= E1000_CTRL_EXT_PFRSTD;
		wr32(E1000_CTRL_EXT, reg_data);
	}

	netif_tx_start_all_queues(adapter->netdev);

	/* start the watchdog. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchdog_task);

	return 0;
}