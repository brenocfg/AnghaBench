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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;
struct TYPE_5__ {TYPE_3__ fp_regs; } ;
struct TYPE_8__ {TYPE_1__ thread; } ;
struct TYPE_6__ {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 scalar_t__ calc_addr (struct pt_regs*,int,int,int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  mathemu_copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int math_emu_ld(__u8 *opcode, struct pt_regs * regs) {
        s390_fp_regs *fp_regs = &current->thread.fp_regs;
        __u32 opc = *((__u32 *) opcode);
        __u64 *dxb;

        dxb = (__u64 *) calc_addr(regs, opc >> 16, opc >> 12, opc);
        mathemu_copy_from_user(&fp_regs->fprs[(opc >> 20) & 0xf].d, dxb, 8);
	return 0;
}