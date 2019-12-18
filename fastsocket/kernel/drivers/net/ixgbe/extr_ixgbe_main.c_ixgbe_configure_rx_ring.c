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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_ring {int dma; int count; scalar_t__ tail; int /*<<< orphan*/  reg_idx; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; scalar_t__ hw_addr; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 scalar_t__ IXGBE_RDBAH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_RDT (int /*<<< orphan*/ ) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,scalar_t__) ; 
 scalar_t__ IXGBE_RXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  ixgbe_alloc_rx_buffers (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_configure_rscctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_configure_srrctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_desc_unused (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_disable_rx_queue (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_rx_desc_queue_enable (struct ixgbe_adapter*,struct ixgbe_ring*) ; 

void ixgbe_configure_rx_ring(struct ixgbe_adapter *adapter,
			     struct ixgbe_ring *ring)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u64 rdba = ring->dma;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to avoid issues while updating state */
	rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
	ixgbe_disable_rx_queue(adapter, ring);

	IXGBE_WRITE_REG(hw, IXGBE_RDBAL(reg_idx), (rdba & DMA_BIT_MASK(32)));
	IXGBE_WRITE_REG(hw, IXGBE_RDBAH(reg_idx), (rdba >> 32));
	IXGBE_WRITE_REG(hw, IXGBE_RDLEN(reg_idx),
			ring->count * sizeof(union ixgbe_adv_rx_desc));
	IXGBE_WRITE_REG(hw, IXGBE_RDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_RDT(reg_idx), 0);
	ring->tail = hw->hw_addr + IXGBE_RDT(reg_idx);

	ixgbe_configure_srrctl(adapter, ring);
	ixgbe_configure_rscctl(adapter, ring);

	if (hw->mac.type == ixgbe_mac_82598EB) {
		/*
		 * enable cache line friendly hardware writes:
		 * PTHRESH=32 descriptors (half the internal cache),
		 * this also removes ugly rx_no_buffer_count increment
		 * HTHRESH=4 descriptors (to minimize latency on fetch)
		 * WTHRESH=8 burst writeback up to two cache lines
		 */
		rxdctl &= ~0x3FFFFF;
		rxdctl |=  0x080420;
	}

	/* enable receive descriptor ring */
	rxdctl |= IXGBE_RXDCTL_ENABLE;
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);

	ixgbe_rx_desc_queue_enable(adapter, ring);
	ixgbe_alloc_rx_buffers(ring, ixgbe_desc_unused(ring));
}