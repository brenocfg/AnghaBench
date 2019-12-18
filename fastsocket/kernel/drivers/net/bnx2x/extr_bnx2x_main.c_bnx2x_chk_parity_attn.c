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
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct attn_route {void** sig; TYPE_1__ member_0; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_2_FUNC_0 ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_3_FUNC_0 ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_4_FUNC_0 ; 
 scalar_t__ MISC_REG_AEU_AFTER_INVERT_5_FUNC_0 ; 
 void* REG_RD (struct bnx2x*,scalar_t__) ; 
 int bnx2x_parity_attn (struct bnx2x*,int*,int,void**) ; 

bool bnx2x_chk_parity_attn(struct bnx2x *bp, bool *global, bool print)
{
	struct attn_route attn = { {0} };
	int port = BP_PORT(bp);

	attn.sig[0] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 +
			     port*4);
	attn.sig[1] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_2_FUNC_0 +
			     port*4);
	attn.sig[2] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_3_FUNC_0 +
			     port*4);
	attn.sig[3] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_4_FUNC_0 +
			     port*4);

	if (!CHIP_IS_E1x(bp))
		attn.sig[4] = REG_RD(bp,
			MISC_REG_AEU_AFTER_INVERT_5_FUNC_0 +
				     port*4);

	return bnx2x_parity_attn(bp, global, print, attn.sig);
}