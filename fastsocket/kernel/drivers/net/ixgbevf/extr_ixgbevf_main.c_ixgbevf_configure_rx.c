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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_rx_queues; TYPE_1__* rx_ring; struct ixgbe_hw hw; } ;
struct TYPE_2__ {int count; int dma; int reg_idx; void* tail; void* head; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 void* IXGBE_VFPSRTYPE ; 
 void* IXGBE_VFRDBAH (int) ; 
 void* IXGBE_VFRDBAL (int) ; 
 void* IXGBE_VFRDH (int) ; 
 void* IXGBE_VFRDLEN (int) ; 
 void* IXGBE_VFRDT (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,void*,int) ; 
 int /*<<< orphan*/  ixgbevf_configure_srrctl (struct ixgbevf_adapter*,int) ; 
 int /*<<< orphan*/  ixgbevf_set_rx_buffer_len (struct ixgbevf_adapter*) ; 

__attribute__((used)) static void ixgbevf_configure_rx(struct ixgbevf_adapter *adapter)
{
	u64 rdba;
	struct ixgbe_hw *hw = &adapter->hw;
	int i, j;
	u32 rdlen;

	/* PSRTYPE must be initialized in 82599 */
	IXGBE_WRITE_REG(hw, IXGBE_VFPSRTYPE, 0);

	/* set_rx_buffer_len must be called before ring initialization */
	ixgbevf_set_rx_buffer_len(adapter);

	rdlen = adapter->rx_ring[0].count * sizeof(union ixgbe_adv_rx_desc);
	/* Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		rdba = adapter->rx_ring[i].dma;
		j = adapter->rx_ring[i].reg_idx;
		IXGBE_WRITE_REG(hw, IXGBE_VFRDBAL(j),
				(rdba & DMA_BIT_MASK(32)));
		IXGBE_WRITE_REG(hw, IXGBE_VFRDBAH(j), (rdba >> 32));
		IXGBE_WRITE_REG(hw, IXGBE_VFRDLEN(j), rdlen);
		IXGBE_WRITE_REG(hw, IXGBE_VFRDH(j), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VFRDT(j), 0);
		adapter->rx_ring[i].head = IXGBE_VFRDH(j);
		adapter->rx_ring[i].tail = IXGBE_VFRDT(j);

		ixgbevf_configure_srrctl(adapter, j);
	}
}