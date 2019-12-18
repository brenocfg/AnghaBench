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
struct TYPE_6__ {int fpc; TYPE_1__* fprs; } ;
struct TYPE_7__ {TYPE_2__ fp_regs; } ;
struct TYPE_8__ {TYPE_3__ thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_ADD_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_MUL_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_PACK_SP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_SP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA ; 
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SC ; 
 int /*<<< orphan*/  SR ; 
 int _fex ; 
 TYPE_4__* current ; 

__attribute__((used)) static int emu_maebr (struct pt_regs *regs, int rx, int ry, int rz) {
        FP_DECL_S(SA); FP_DECL_S(SB); FP_DECL_S(SC); FP_DECL_S(SR);
        FP_DECL_EX;
        int mode;

	mode = current->thread.fp_regs.fpc & 3;
        FP_UNPACK_SP(SA, &current->thread.fp_regs.fprs[rx].f);
        FP_UNPACK_SP(SB, &current->thread.fp_regs.fprs[ry].f);
        FP_UNPACK_SP(SC, &current->thread.fp_regs.fprs[rz].f);
        FP_MUL_S(SR, SA, SB);
        FP_ADD_S(SR, SR, SC);
	FP_PACK_SP(&current->thread.fp_regs.fprs[rz].f, SR);
        return _fex;
}