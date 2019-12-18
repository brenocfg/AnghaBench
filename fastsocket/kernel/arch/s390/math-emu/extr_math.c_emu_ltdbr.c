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
struct TYPE_7__ {TYPE_2__* fprs; } ;
typedef  TYPE_3__ s390_fp_regs ;
struct TYPE_5__ {TYPE_3__ fp_regs; } ;
struct TYPE_8__ {TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  ui; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  DA_c ; 
 int /*<<< orphan*/  DA_s ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_UNPACK_DP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _fex ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  emu_set_CC_cs (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emu_ltdbr (struct pt_regs *regs, int rx, int ry) {
        s390_fp_regs *fp_regs = &current->thread.fp_regs;
        FP_DECL_D(DA);
        FP_DECL_EX;

        FP_UNPACK_DP(DA, &fp_regs->fprs[ry].d);
        fp_regs->fprs[rx].ui = fp_regs->fprs[ry].ui;
        emu_set_CC_cs(regs, DA_c, DA_s);
        return _fex;
}