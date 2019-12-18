#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  fpc; } ;
struct TYPE_5__ {TYPE_1__ fp_regs; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 scalar_t__ calc_addr (struct pt_regs*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  mathemu_put_user (int /*<<< orphan*/ ,int*) ; 

int math_emu_stfpc(__u8 *opcode, struct pt_regs *regs) {
        __u32 opc = *((__u32 *) opcode);
        __u32 *dxb;

        dxb= (__u32 *) calc_addr(regs, 0, opc>>12, opc);
        mathemu_put_user(current->thread.fp_regs.fpc, dxb);
        return 0;
}