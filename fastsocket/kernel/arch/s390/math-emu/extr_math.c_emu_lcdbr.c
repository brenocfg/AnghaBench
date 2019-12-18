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
struct TYPE_5__ {int fpc; TYPE_2__* fprs; } ;
struct TYPE_7__ {TYPE_1__ fp_regs; } ;
struct TYPE_8__ {TYPE_3__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  DR ; 
 int /*<<< orphan*/  DR_c ; 
 int /*<<< orphan*/  DR_s ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_NEG_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_PACK_DP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _fex ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  emu_set_CC_cs (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emu_lcdbr (struct pt_regs *regs, int rx, int ry) {
        FP_DECL_D(DA); FP_DECL_D(DR);
        FP_DECL_EX;
        int mode;

	mode = current->thread.fp_regs.fpc & 3;
        FP_UNPACK_DP(DA, &current->thread.fp_regs.fprs[ry].d);
	FP_NEG_D(DR, DA);
	FP_PACK_DP(&current->thread.fp_regs.fprs[rx].d, DR);
        emu_set_CC_cs(regs, DR_c, DR_s);
        return _fex;
}