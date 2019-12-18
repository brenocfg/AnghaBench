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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct igu_regular {int sb_id_and_flags; } ;
struct cnic_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_IGU_INTMEM ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,scalar_t__,int) ; 
 int IGU_CMD_INT_ACK_BASE ; 
 int IGU_REGULAR_BUPDATE_SHIFT ; 
 int IGU_REGULAR_ENABLE_INT_SHIFT ; 
 int IGU_REGULAR_SB_INDEX_SHIFT ; 
 int IGU_REGULAR_SEGMENT_ACCESS_SHIFT ; 

__attribute__((used)) static void cnic_ack_igu_sb(struct cnic_dev *dev, u8 igu_sb_id, u8 segment,
			    u16 index, u8 op, u8 update)
{
	struct igu_regular cmd_data;
	u32 igu_addr = BAR_IGU_INTMEM + (IGU_CMD_INT_ACK_BASE + igu_sb_id) * 8;

	cmd_data.sb_id_and_flags =
		(index << IGU_REGULAR_SB_INDEX_SHIFT) |
		(segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
		(update << IGU_REGULAR_BUPDATE_SHIFT) |
		(op << IGU_REGULAR_ENABLE_INT_SHIFT);


	CNIC_WR(dev, igu_addr, cmd_data.sb_id_and_flags);
}