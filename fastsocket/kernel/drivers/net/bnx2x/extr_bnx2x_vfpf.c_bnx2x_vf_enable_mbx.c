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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_vf_enable_access (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_flr_clnup_epilog (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_vf_mbx_ack (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_vf_mbx_valid (struct bnx2x*,int /*<<< orphan*/ ) ; 

void bnx2x_vf_enable_mbx(struct bnx2x *bp, u8 abs_vfid)
{
	bnx2x_vf_flr_clnup_epilog(bp, abs_vfid);

	/* enable the mailbox in the FW */
	storm_memset_vf_mbx_ack(bp, abs_vfid);
	storm_memset_vf_mbx_valid(bp, abs_vfid);

	/* enable the VF access to the mailbox */
	bnx2x_vf_enable_access(bp, abs_vfid);
}