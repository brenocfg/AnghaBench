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
typedef  int __u32 ;
struct TYPE_6__ {TYPE_1__* fprs; } ;
struct TYPE_7__ {TYPE_2__ fp_regs; } ;
struct TYPE_8__ {TYPE_3__ thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int DA_e ; 
 int /*<<< orphan*/  DA_s ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_UNPACK_RAW_DP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  _FP_EXPMAX_D 128 
 int _FP_FRAC_HIGH_RAW_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FP_FRAC_ZEROP_2 (int /*<<< orphan*/ ) ; 
 int _FP_QNANBIT_D ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  emu_set_CC (struct pt_regs*,int) ; 

__attribute__((used)) static int emu_tcdb (struct pt_regs *regs, int rx, long val) {
        FP_DECL_D(DA);
	int bit;

        FP_UNPACK_RAW_DP(DA, &current->thread.fp_regs.fprs[rx].d);
	switch (DA_e) {
	default:
		bit = 8;		/* normalized number */
		break;
	case 0:
		if (_FP_FRAC_ZEROP_2(DA))
			bit = 10;	/* zero */
		else
			bit = 6;	/* denormalized number */
		break;
	case _FP_EXPMAX_D:
		if (_FP_FRAC_ZEROP_2(DA))
			bit = 4;	/* infinity */
		else if (_FP_FRAC_HIGH_RAW_D(DA) & _FP_QNANBIT_D)
			bit = 2;	/* quiet NAN */
		else
			bit = 0;	/* signaling NAN */
		break;
	}
	if (!DA_s)
		bit++;
	emu_set_CC(regs, ((__u32) val >> bit) & 1);
        return 0;
}