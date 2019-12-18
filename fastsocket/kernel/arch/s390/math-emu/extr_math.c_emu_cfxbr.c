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
struct pt_regs {int /*<<< orphan*/ * gprs; } ;
struct TYPE_7__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_11__ {int /*<<< orphan*/  ld; TYPE_1__ w; } ;
typedef  TYPE_5__ mathemu_ldcv ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_9__ {int fpc; TYPE_2__* fprs; } ;
struct TYPE_10__ {TYPE_3__ fp_regs; } ;
struct TYPE_12__ {TYPE_4__ thread; } ;
struct TYPE_8__ {int /*<<< orphan*/  ui; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int FP_RND_NEAREST ; 
 int /*<<< orphan*/  FP_TO_INT_ROUND_Q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FP_UNPACK_QP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QA ; 
 int /*<<< orphan*/  QA_c ; 
 int /*<<< orphan*/  QA_s ; 
 int _fex ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  emu_set_CC_cs (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emu_cfxbr (struct pt_regs *regs, int rx, int ry, int mask) {
        FP_DECL_Q(QA);
        FP_DECL_EX;
	mathemu_ldcv cvt;
        __s32 si;
        int mode;

	if (mask == 0)
		mode = current->thread.fp_regs.fpc & 3;
	else if (mask == 1)
		mode = FP_RND_NEAREST;
	else
		mode = mask - 4;
        cvt.w.high = current->thread.fp_regs.fprs[ry].ui;
        cvt.w.low = current->thread.fp_regs.fprs[ry+2].ui;
        FP_UNPACK_QP(QA, &cvt.ld);
        FP_TO_INT_ROUND_Q(si, QA, 32, 1);
        regs->gprs[rx] = si;
        emu_set_CC_cs(regs, QA_c, QA_s);
        return _fex;
}