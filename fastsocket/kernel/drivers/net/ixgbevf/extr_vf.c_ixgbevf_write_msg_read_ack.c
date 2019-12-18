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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_posted ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_posted ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct ixgbe_mbx_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_VFMAILBOX_SIZE ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_write_msg_read_ack(struct ixgbe_hw *hw,
					u32 *msg, u16 size)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	u32 retmsg[IXGBE_VFMAILBOX_SIZE];
	s32 retval = mbx->ops.write_posted(hw, msg, size);

	if (!retval)
		mbx->ops.read_posted(hw, retmsg, size);
}