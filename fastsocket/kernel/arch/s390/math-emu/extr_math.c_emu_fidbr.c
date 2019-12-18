#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_7__ {int fpc; TYPE_1__* fprs; } ;
typedef  TYPE_3__ s390_fp_regs ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_6__ {TYPE_3__ fp_regs; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_PACK_DP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FP_RND_NEAREST ; 
 int /*<<< orphan*/  FP_TO_FPINT_ROUND_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _fex ; 
 TYPE_4__* current ; 

__attribute__((used)) static int emu_fidbr (struct pt_regs *regs, int rx, int ry, int mask) {
	/* FIXME: rounding mode !! */
        s390_fp_regs *fp_regs = &current->thread.fp_regs;
        FP_DECL_D(DA);
        FP_DECL_EX;
        __s32 si;
        int mode;

	if (mask == 0)
		mode = fp_regs->fpc & 3;
	else if (mask == 1)
		mode = FP_RND_NEAREST;
	else
		mode = mask - 4;
        FP_UNPACK_DP(DA, &fp_regs->fprs[ry].d);
	FP_TO_FPINT_ROUND_D(DA);
	FP_PACK_DP(&fp_regs->fprs[rx].d, DA);
        return _fex;
}