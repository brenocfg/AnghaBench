#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {void* lo; void* hi; } ;
struct TYPE_6__ {TYPE_2__ update_data_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; void* conn_and_cmd_data; } ;
struct eth_spe {TYPE_3__ data; TYPE_1__ hdr; } ;
struct bnx2x {int /*<<< orphan*/  spq_lock; int /*<<< orphan*/  eq_spq_left; int /*<<< orphan*/  cq_spq_left; scalar_t__ spq; scalar_t__ spq_prod_bd; int /*<<< orphan*/  spq_mapping; int /*<<< orphan*/  spq_prod_idx; int /*<<< orphan*/  panic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EIO ; 
 int HW_CID (struct bnx2x*,int) ; 
 int SPE_HDR_CMD_ID_SHIFT ; 
 int SPE_HDR_CONN_TYPE ; 
 int SPE_HDR_CONN_TYPE_SHIFT ; 
 int SPE_HDR_FUNCTION_ID ; 
 int SPE_HDR_FUNCTION_ID_SHIFT ; 
 scalar_t__ U64_HI (int /*<<< orphan*/ ) ; 
 int U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int bnx2x_is_contextless_ramrod (int,int) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 struct eth_spe* bnx2x_sp_get_next (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_sp_prod_update (struct bnx2x*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int bnx2x_sp_post(struct bnx2x *bp, int command, int cid,
		  u32 data_hi, u32 data_lo, int cmd_type)
{
	struct eth_spe *spe;
	u16 type;
	bool common = bnx2x_is_contextless_ramrod(command, cmd_type);

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic)) {
		BNX2X_ERR("Can't post SP when there is panic\n");
		return -EIO;
	}
#endif

	spin_lock_bh(&bp->spq_lock);

	if (common) {
		if (!atomic_read(&bp->eq_spq_left)) {
			BNX2X_ERR("BUG! EQ ring full!\n");
			spin_unlock_bh(&bp->spq_lock);
			bnx2x_panic();
			return -EBUSY;
		}
	} else if (!atomic_read(&bp->cq_spq_left)) {
			BNX2X_ERR("BUG! SPQ ring full!\n");
			spin_unlock_bh(&bp->spq_lock);
			bnx2x_panic();
			return -EBUSY;
	}

	spe = bnx2x_sp_get_next(bp);

	/* CID needs port number to be encoded int it */
	spe->hdr.conn_and_cmd_data =
			cpu_to_le32((command << SPE_HDR_CMD_ID_SHIFT) |
				    HW_CID(bp, cid));

	type = (cmd_type << SPE_HDR_CONN_TYPE_SHIFT) & SPE_HDR_CONN_TYPE;

	type |= ((BP_FUNC(bp) << SPE_HDR_FUNCTION_ID_SHIFT) &
		 SPE_HDR_FUNCTION_ID);

	spe->hdr.type = cpu_to_le16(type);

	spe->data.update_data_addr.hi = cpu_to_le32(data_hi);
	spe->data.update_data_addr.lo = cpu_to_le32(data_lo);

	/*
	 * It's ok if the actual decrement is issued towards the memory
	 * somewhere between the spin_lock and spin_unlock. Thus no
	 * more explicit memory barrier is needed.
	 */
	if (common)
		atomic_dec(&bp->eq_spq_left);
	else
		atomic_dec(&bp->cq_spq_left);

	DP(BNX2X_MSG_SP,
	   "SPQE[%x] (%x:%x)  (cmd, common?) (%d,%d)  hw_cid %x  data (%x:%x) type(0x%x) left (CQ, EQ) (%x,%x)\n",
	   bp->spq_prod_idx, (u32)U64_HI(bp->spq_mapping),
	   (u32)(U64_LO(bp->spq_mapping) +
	   (void *)bp->spq_prod_bd - (void *)bp->spq), command, common,
	   HW_CID(bp, cid), data_hi, data_lo, type,
	   atomic_read(&bp->cq_spq_left), atomic_read(&bp->eq_spq_left));

	bnx2x_sp_prod_update(bp);
	spin_unlock_bh(&bp->spq_lock);
	return 0;
}