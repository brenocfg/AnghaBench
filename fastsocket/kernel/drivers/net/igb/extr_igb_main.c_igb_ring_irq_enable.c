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
struct TYPE_2__ {scalar_t__ ring; } ;
struct igb_q_vector {int /*<<< orphan*/  eims_value; TYPE_1__ rx; struct igb_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int rx_itr_setting; int tx_itr_setting; int num_q_vectors; scalar_t__ msix_entries; int /*<<< orphan*/  state; int /*<<< orphan*/  vf_data; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  igb_irq_enable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_itr (struct igb_q_vector*) ; 
 int /*<<< orphan*/  igb_update_ring_itr (struct igb_q_vector*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_ring_irq_enable(struct igb_q_vector *q_vector)
{
	struct igb_adapter *adapter = q_vector->adapter;
	struct e1000_hw *hw = &adapter->hw;

	if ((q_vector->rx.ring && (adapter->rx_itr_setting & 3)) ||
	    (!q_vector->rx.ring && (adapter->tx_itr_setting & 3))) {
		if ((adapter->num_q_vectors == 1) && !adapter->vf_data)
			igb_set_itr(q_vector);
		else
			igb_update_ring_itr(q_vector);
	}

	if (!test_bit(__IGB_DOWN, &adapter->state)) {
		if (adapter->msix_entries)
			wr32(E1000_EIMS, q_vector->eims_value);
		else
			igb_irq_enable(adapter);
	}
}