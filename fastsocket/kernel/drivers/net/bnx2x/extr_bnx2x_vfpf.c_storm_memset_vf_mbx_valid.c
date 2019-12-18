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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ CSTORM_VF_PF_CHANNEL_VALID_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR8 (struct bnx2x*,scalar_t__,int) ; 

__attribute__((used)) static void storm_memset_vf_mbx_valid(struct bnx2x *bp, u16 abs_fid)
{
	u32 addr = BAR_CSTRORM_INTMEM +
		   CSTORM_VF_PF_CHANNEL_VALID_OFFSET(abs_fid);

	REG_WR8(bp, addr, 1);
}