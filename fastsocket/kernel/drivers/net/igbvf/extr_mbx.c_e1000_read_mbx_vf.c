#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/  msgs_rx; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct e1000_hw {TYPE_2__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_V2PMAILBOX_ACK ; 
 int /*<<< orphan*/  V2PMAILBOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMBMEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_er32 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ e1000_obtain_mbx_lock_vf (struct e1000_hw*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_read_mbx_vf(struct e1000_hw *hw, u32 *msg, u16 size)
{
	s32 err;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	err = e1000_obtain_mbx_lock_vf(hw);
	if (err)
		goto out_no_read;

	/* copy the message from the mailbox memory buffer */
	for (i = 0; i < size; i++)
		msg[i] = array_er32(VMBMEM(0), i);

	/* Acknowledge receipt and release mailbox, then we're done */
	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_ACK);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

out_no_read:
	return err;
}