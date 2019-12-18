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
struct bnx2 {int /*<<< orphan*/  indirect_lock; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int /*<<< orphan*/  BNX2_CTX_CTX_CTRL ; 
 int BNX2_CTX_CTX_CTRL_WRITE_REQ ; 
 int /*<<< orphan*/  BNX2_CTX_CTX_DATA ; 
 int /*<<< orphan*/  BNX2_CTX_DATA ; 
 int /*<<< orphan*/  BNX2_CTX_DATA_ADR ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
bnx2_ctx_wr(struct bnx2 *bp, u32 cid_addr, u32 offset, u32 val)
{
	offset += cid_addr;
	spin_lock_bh(&bp->indirect_lock);
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		int i;

		BNX2_WR(bp, BNX2_CTX_CTX_DATA, val);
		BNX2_WR(bp, BNX2_CTX_CTX_CTRL,
			offset | BNX2_CTX_CTX_CTRL_WRITE_REQ);
		for (i = 0; i < 5; i++) {
			val = BNX2_RD(bp, BNX2_CTX_CTX_CTRL);
			if ((val & BNX2_CTX_CTX_CTRL_WRITE_REQ) == 0)
				break;
			udelay(5);
		}
	} else {
		BNX2_WR(bp, BNX2_CTX_DATA_ADR, offset);
		BNX2_WR(bp, BNX2_CTX_DATA, val);
	}
	spin_unlock_bh(&bp->indirect_lock);
}