#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {TYPE_3__* ring; } ;
struct TYPE_7__ {TYPE_1__* ring; } ;
struct igb_q_vector {int eims_value; int set_itr; TYPE_4__ tx; TYPE_2__ rx; struct igb_adapter* adapter; } ;
struct TYPE_10__ {int type; } ;
struct e1000_hw {TYPE_5__ mac; } ;
struct igb_adapter {int eims_enable_mask; int /*<<< orphan*/  msix_entries; struct e1000_hw hw; } ;
struct TYPE_8__ {int reg_idx; } ;
struct TYPE_6__ {int reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int E1000_EICR_RX_QUEUE0 ; 
 int E1000_EICR_TX_QUEUE0 ; 
 int E1000_EIMS_OTHER ; 
 int /*<<< orphan*/  E1000_MSIXBM (int /*<<< orphan*/ ) ; 
 int IGB_N0_QUEUE ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,int,int) ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  igb_write_ivar (struct e1000_hw*,int,int,int) ; 

__attribute__((used)) static void igb_assign_vector(struct igb_q_vector *q_vector, int msix_vector)
{
	struct igb_adapter *adapter = q_vector->adapter;
	struct e1000_hw *hw = &adapter->hw;
	int rx_queue = IGB_N0_QUEUE;
	int tx_queue = IGB_N0_QUEUE;
	u32 msixbm = 0;

	if (q_vector->rx.ring)
		rx_queue = q_vector->rx.ring->reg_idx;
	if (q_vector->tx.ring)
		tx_queue = q_vector->tx.ring->reg_idx;

	switch (hw->mac.type) {
	case e1000_82575:
		/* The 82575 assigns vectors using a bitmask, which matches the
		 * bitmask for the EICR/EIMS/EIMC registers.  To assign one
		 * or more queues to a vector, we write the appropriate bits
		 * into the MSIXBM register for that vector.
		 */
		if (rx_queue > IGB_N0_QUEUE)
			msixbm = E1000_EICR_RX_QUEUE0 << rx_queue;
		if (tx_queue > IGB_N0_QUEUE)
			msixbm |= E1000_EICR_TX_QUEUE0 << tx_queue;
		if (!adapter->msix_entries && msix_vector == 0)
			msixbm |= E1000_EIMS_OTHER;
		array_wr32(E1000_MSIXBM(0), msix_vector, msixbm);
		q_vector->eims_value = msixbm;
		break;
	case e1000_82576:
		/* 82576 uses a table that essentially consists of 2 columns
		 * with 8 rows.  The ordering is column-major so we use the
		 * lower 3 bits as the row index, and the 4th bit as the
		 * column offset.
		 */
		if (rx_queue > IGB_N0_QUEUE)
			igb_write_ivar(hw, msix_vector,
				       rx_queue & 0x7,
				       (rx_queue & 0x8) << 1);
		if (tx_queue > IGB_N0_QUEUE)
			igb_write_ivar(hw, msix_vector,
				       tx_queue & 0x7,
				       ((tx_queue & 0x8) << 1) + 8);
		q_vector->eims_value = 1 << msix_vector;
		break;
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		/* On 82580 and newer adapters the scheme is similar to 82576
		 * however instead of ordering column-major we have things
		 * ordered row-major.  So we traverse the table by using
		 * bit 0 as the column offset, and the remaining bits as the
		 * row index.
		 */
		if (rx_queue > IGB_N0_QUEUE)
			igb_write_ivar(hw, msix_vector,
				       rx_queue >> 1,
				       (rx_queue & 0x1) << 4);
		if (tx_queue > IGB_N0_QUEUE)
			igb_write_ivar(hw, msix_vector,
				       tx_queue >> 1,
				       ((tx_queue & 0x1) << 4) + 8);
		q_vector->eims_value = 1 << msix_vector;
		break;
	default:
		BUG();
		break;
	}

	/* add q_vector eims value to global eims_enable_mask */
	adapter->eims_enable_mask |= q_vector->eims_value;

	/* configure q_vector to set itr on first interrupt */
	q_vector->set_itr = 1;
}