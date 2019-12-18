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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct igb_ring {scalar_t__ next_to_use; scalar_t__ count; int reg_idx; int /*<<< orphan*/  flags; } ;
struct e1000_adv_tx_context_desc {void* mss_l4len_idx; void* type_tucmd_mlhl; scalar_t__ seqnum_seed; void* vlan_macip_lens; } ;

/* Variables and functions */
 int E1000_ADVTXD_DTYP_CTXT ; 
 int E1000_TXD_CMD_DEXT ; 
 int /*<<< orphan*/  IGB_RING_FLAG_TX_CTX_IDX ; 
 struct e1000_adv_tx_context_desc* IGB_TX_CTXTDESC (struct igb_ring*,scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_tx_ctxtdesc(struct igb_ring *tx_ring, u32 vlan_macip_lens,
			    u32 type_tucmd, u32 mss_l4len_idx)
{
	struct e1000_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;

	context_desc = IGB_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identify this as an advanced context descriptor */
	type_tucmd |= E1000_TXD_CMD_DEXT | E1000_ADVTXD_DTYP_CTXT;

	/* For 82575, context index must be unique per ring. */
	if (test_bit(IGB_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		mss_l4len_idx |= tx_ring->reg_idx << 4;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->seqnum_seed	= 0;
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);
}