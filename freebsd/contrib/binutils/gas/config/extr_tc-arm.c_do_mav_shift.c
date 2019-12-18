#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; int reg; } ;

/* Variables and functions */
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_mav_shift (void)
{
  int imm = inst.operands[2].imm;

  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= inst.operands[1].reg << 16;

  /* Bits 0-3 of the insn should have bits 0-3 of the immediate.
     Bits 5-7 of the insn should have bits 4-6 of the immediate.
     Bit 4 should be 0.	 */
  imm = (imm & 0xf) | ((imm & 0x70) << 1);

  inst.instruction |= imm;
}