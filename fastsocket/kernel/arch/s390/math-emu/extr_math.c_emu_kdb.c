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
struct TYPE_6__ {TYPE_1__* fprs; } ;
struct TYPE_7__ {TYPE_2__ fp_regs; } ;
struct TYPE_8__ {TYPE_3__ thread; } ;
struct TYPE_5__ {double d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  DB ; 
 int /*<<< orphan*/  FP_CMP_D (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_EX_INVALID ; 
 int /*<<< orphan*/  FP_SET_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_DP (int /*<<< orphan*/ ,double*) ; 
 int _fex ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  emu_set_CC (struct pt_regs*,int) ; 

__attribute__((used)) static int emu_kdb (struct pt_regs *regs, int rx, double *val) {
        FP_DECL_D(DA); FP_DECL_D(DB);
        FP_DECL_EX;
        int IR;

        FP_UNPACK_RAW_DP(DA, &current->thread.fp_regs.fprs[rx].d);
        FP_UNPACK_RAW_DP(DB, val);
        FP_CMP_D(IR, DA, DB, 3);
        /*
         * IR == -1 if DA < DB, IR == 0 if DA == DB,
         * IR == 1 if DA > DB and IR == 3 if unorderded
         */
        emu_set_CC(regs, (IR == -1) ? 1 : (IR == 1) ? 2 : IR);
        if (IR == 3)
                FP_SET_EXCEPTION (FP_EX_INVALID);
        return _fex;
}