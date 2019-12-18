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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2 {int /*<<< orphan*/  indirect_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_PCICFG_REG_WINDOW ; 
 int /*<<< orphan*/  BNX2_PCICFG_REG_WINDOW_ADDRESS ; 
 int /*<<< orphan*/  BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
bnx2_reg_rd_ind(struct bnx2 *bp, u32 offset)
{
	u32 val;

	spin_lock_bh(&bp->indirect_lock);
	BNX2_WR(bp, BNX2_PCICFG_REG_WINDOW_ADDRESS, offset);
	val = BNX2_RD(bp, BNX2_PCICFG_REG_WINDOW);
	spin_unlock_bh(&bp->indirect_lock);
	return val;
}