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
struct TYPE_7__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_11__ {int /*<<< orphan*/  ld; TYPE_1__ w; } ;
typedef  TYPE_5__ mathemu_ldcv ;
typedef  int __u32 ;
struct TYPE_9__ {TYPE_2__* fprs; } ;
struct TYPE_10__ {TYPE_3__ fp_regs; } ;
struct TYPE_12__ {TYPE_4__ thread; } ;
struct TYPE_8__ {int /*<<< orphan*/  ui; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_DECL_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_QP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QA ; 
 int QA_e ; 
 int /*<<< orphan*/  QA_s ; 
#define  _FP_EXPMAX_Q 128 
 int _FP_FRAC_HIGH_RAW_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FP_FRAC_ZEROP_4 (int /*<<< orphan*/ ) ; 
 int _FP_QNANBIT_Q ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  emu_set_CC (struct pt_regs*,int) ; 

__attribute__((used)) static int emu_tcxb (struct pt_regs *regs, int rx, long val) {
        FP_DECL_Q(QA);
	mathemu_ldcv cvt;
	int bit;

        cvt.w.high = current->thread.fp_regs.fprs[rx].ui;
        cvt.w.low = current->thread.fp_regs.fprs[rx+2].ui;
        FP_UNPACK_RAW_QP(QA, &cvt.ld);
	switch (QA_e) {
	default:
		bit = 8;		/* normalized number */
		break;
	case 0:
		if (_FP_FRAC_ZEROP_4(QA))
			bit = 10;	/* zero */
		else
			bit = 6;	/* denormalized number */
		break;
	case _FP_EXPMAX_Q:
		if (_FP_FRAC_ZEROP_4(QA))
			bit = 4;	/* infinity */
		else if (_FP_FRAC_HIGH_RAW_Q(QA) & _FP_QNANBIT_Q)
			bit = 2;	/* quiet NAN */
		else
			bit = 0;	/* signaling NAN */
		break;
	}
	if (!QA_s)
		bit++;
	emu_set_CC(regs, ((__u32) val >> bit) & 1);
        return 0;
}