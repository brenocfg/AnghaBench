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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int E1000_V2PMAILBOX_VFU ; 
 int /*<<< orphan*/  V2PMAILBOX (int /*<<< orphan*/ ) ; 
 int e1000_read_v2p_mailbox (struct e1000_hw*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_obtain_mbx_lock_vf(struct e1000_hw *hw)
{
	s32 ret_val = -E1000_ERR_MBX;

	/* Take ownership of the buffer */
	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_VFU);

	/* reserve mailbox for vf use */
	if (e1000_read_v2p_mailbox(hw) & E1000_V2PMAILBOX_VFU)
		ret_val = E1000_SUCCESS;

	return ret_val;
}