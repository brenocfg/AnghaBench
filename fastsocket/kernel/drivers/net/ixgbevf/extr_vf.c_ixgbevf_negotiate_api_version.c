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
typedef  int u32 ;
struct TYPE_3__ {int (* write_posted ) (struct ixgbe_hw*,int*,int) ;int (* read_posted ) (struct ixgbe_hw*,int*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {int api_version; TYPE_2__ mbx; } ;

/* Variables and functions */
 int IXGBE_ERR_INVALID_ARGUMENT ; 
 int IXGBE_VF_API_NEGOTIATE ; 
 int IXGBE_VT_MSGTYPE_ACK ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int stub1 (struct ixgbe_hw*,int*,int) ; 
 int stub2 (struct ixgbe_hw*,int*,int) ; 

int ixgbevf_negotiate_api_version(struct ixgbe_hw *hw, int api)
{
	int err;
	u32 msg[3];

	/* Negotiate the mailbox API version */
	msg[0] = IXGBE_VF_API_NEGOTIATE;
	msg[1] = api;
	msg[2] = 0;
	err = hw->mbx.ops.write_posted(hw, msg, 3);

	if (!err)
		err = hw->mbx.ops.read_posted(hw, msg, 3);

	if (!err) {
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* Store value and return 0 on success */
		if (msg[0] == (IXGBE_VF_API_NEGOTIATE | IXGBE_VT_MSGTYPE_ACK)) {
			hw->api_version = api;
			return 0;
		}

		err = IXGBE_ERR_INVALID_ARGUMENT;
	}

	return err;
}