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
struct TYPE_2__ {int /*<<< orphan*/  (* write_posted ) (struct e1000_hw*,int /*<<< orphan*/ *,int) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VF_SET_LPE ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ *,int) ; 

void e1000_rlpml_set_vf(struct e1000_hw *hw, u16 max_size)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];

	msgbuf[0] = E1000_VF_SET_LPE;
	msgbuf[1] = max_size;

	mbx->ops.write_posted(hw, msgbuf, 2);
}