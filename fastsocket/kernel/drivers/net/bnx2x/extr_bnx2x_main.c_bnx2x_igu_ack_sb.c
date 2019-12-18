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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int igu_base_addr; } ;

/* Variables and functions */
 int IGU_CMD_INT_ACK_BASE ; 
 int /*<<< orphan*/  bnx2x_igu_ack_sb_gen (struct bnx2x*,int,int,int /*<<< orphan*/ ,int,int,int) ; 

void bnx2x_igu_ack_sb(struct bnx2x *bp, u8 igu_sb_id, u8 segment,
		      u16 index, u8 op, u8 update)
{
	u32 igu_addr = bp->igu_base_addr;
	igu_addr += (IGU_CMD_INT_ACK_BASE + igu_sb_id)*8;
	bnx2x_igu_ack_sb_gen(bp, igu_sb_id, segment, index, op, update,
			     igu_addr);
}