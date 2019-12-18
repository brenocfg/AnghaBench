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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_port {size_t port; unsigned int rx_nfrags; unsigned int rx_data_size; unsigned int rx_pending; struct rx_ring_info* rx_ring; TYPE_1__* netdev; int /*<<< orphan*/  rx_le_map; scalar_t__ rx_next; scalar_t__ rx_put; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; int flags; int /*<<< orphan*/  pdev; } ;
struct rx_ring_info {int /*<<< orphan*/ * skb; int /*<<< orphan*/  frag_addr; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMU_WM_PEX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHIP_ID_YUKON_EC_U ; 
 scalar_t__ CHIP_REV_YU_EC_U_A1 ; 
 scalar_t__ CHIP_REV_YU_EC_U_B0 ; 
 int ENOMEM ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  F_M_RX_RAM_DIS ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int /*<<< orphan*/  Q_ADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_TEST ; 
 int /*<<< orphan*/  Q_WM ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_GMF_TR_THR ; 
 scalar_t__ RX_LE_SIZE ; 
 int /*<<< orphan*/  RX_TRUNC_OFF ; 
 int /*<<< orphan*/  RX_TRUNC_ON ; 
 int SKY2_HW_NEW_LE ; 
 int /*<<< orphan*/  SK_REG (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ VLAN_HLEN ; 
 unsigned int copybreak ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  rx_set_checksum (struct sky2_port*) ; 
 unsigned int* rxqaddr ; 
 int /*<<< orphan*/  sky2_prefetch_init (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sky2_qset (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/ * sky2_rx_alloc (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_rx_clean (struct sky2_port*) ; 
 scalar_t__ sky2_rx_map_skb (int /*<<< orphan*/ ,struct rx_ring_info*,unsigned int) ; 
 int /*<<< orphan*/  sky2_rx_submit (struct sky2_port*,struct rx_ring_info*) ; 
 int /*<<< orphan*/  sky2_rx_update (struct sky2_port*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_rx_start(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	struct rx_ring_info *re;
	unsigned rxq = rxqaddr[sky2->port];
	unsigned i, size, thresh;

	sky2->rx_put = sky2->rx_next = 0;
	sky2_qset(hw, rxq);

	/* On PCI express lowering the watermark gives better performance */
	if (pci_find_capability(hw->pdev, PCI_CAP_ID_EXP))
		sky2_write32(hw, Q_ADDR(rxq, Q_WM), BMU_WM_PEX);

	/* These chips have no ram buffer?
	 * MAC Rx RAM Read is controlled by hardware */
	if (hw->chip_id == CHIP_ID_YUKON_EC_U &&
	    (hw->chip_rev == CHIP_REV_YU_EC_U_A1
	     || hw->chip_rev == CHIP_REV_YU_EC_U_B0))
		sky2_write32(hw, Q_ADDR(rxq, Q_TEST), F_M_RX_RAM_DIS);

	sky2_prefetch_init(hw, rxq, sky2->rx_le_map, RX_LE_SIZE - 1);

	if (!(hw->flags & SKY2_HW_NEW_LE))
		rx_set_checksum(sky2);

	/* Space needed for frame data + headers rounded up */
	size = roundup(sky2->netdev->mtu + ETH_HLEN + VLAN_HLEN, 8);

	/* Stopping point for hardware truncation */
	thresh = (size - 8) / sizeof(u32);

	sky2->rx_nfrags = size >> PAGE_SHIFT;
	BUG_ON(sky2->rx_nfrags > ARRAY_SIZE(re->frag_addr));

	/* Compute residue after pages */
	size -= sky2->rx_nfrags << PAGE_SHIFT;

	/* Optimize to handle small packets and headers */
	if (size < copybreak)
		size = copybreak;
	if (size < ETH_HLEN)
		size = ETH_HLEN;

	sky2->rx_data_size = size;

	/* Fill Rx ring */
	for (i = 0; i < sky2->rx_pending; i++) {
		re = sky2->rx_ring + i;

		re->skb = sky2_rx_alloc(sky2);
		if (!re->skb)
			goto nomem;

		if (sky2_rx_map_skb(hw->pdev, re, sky2->rx_data_size)) {
			dev_kfree_skb(re->skb);
			re->skb = NULL;
			goto nomem;
		}

		sky2_rx_submit(sky2, re);
	}

	/*
	 * The receiver hangs if it receives frames larger than the
	 * packet buffer. As a workaround, truncate oversize frames, but
	 * the register is limited to 9 bits, so if you do frames > 2052
	 * you better get the MTU right!
	 */
	if (thresh > 0x1ff)
		sky2_write32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T), RX_TRUNC_OFF);
	else {
		sky2_write16(hw, SK_REG(sky2->port, RX_GMF_TR_THR), thresh);
		sky2_write32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T), RX_TRUNC_ON);
	}

	/* Tell chip about available buffers */
	sky2_rx_update(sky2, rxq);
	return 0;
nomem:
	sky2_rx_clean(sky2);
	return -ENOMEM;
}