#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_10__ {TYPE_3__* fprs; } ;
typedef  TYPE_4__ s390_fp_regs ;
struct TYPE_7__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_11__ {int /*<<< orphan*/  ld; TYPE_1__ w; } ;
typedef  TYPE_5__ mathemu_ldcv ;
struct TYPE_8__ {TYPE_4__ fp_regs; } ;
struct TYPE_12__ {TYPE_2__ thread; } ;
struct TYPE_9__ {int /*<<< orphan*/  ui; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_QP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QA ; 
 int /*<<< orphan*/  QA_c ; 
 int /*<<< orphan*/  QA_s ; 
 int _fex ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  emu_set_CC_cs (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emu_ltxbr (struct pt_regs *regs, int rx, int ry) {
        s390_fp_regs *fp_regs = &current->thread.fp_regs;
	mathemu_ldcv cvt;
        FP_DECL_Q(QA);
        FP_DECL_EX;

        cvt.w.high = current->thread.fp_regs.fprs[ry].ui;
        cvt.w.low = current->thread.fp_regs.fprs[ry+2].ui;
        FP_UNPACK_QP(QA, &cvt.ld);
        fp_regs->fprs[rx].ui = fp_regs->fprs[ry].ui;
        fp_regs->fprs[rx+2].ui = fp_regs->fprs[ry+2].ui;
        emu_set_CC_cs(regs, QA_c, QA_s);
        return _fex;
}