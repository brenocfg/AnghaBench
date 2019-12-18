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
struct TYPE_3__ {int reg; int imm; scalar_t__ isvec; } ;

/* Variables and functions */
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_co_reg (void)
{
  inst.instruction |= inst.operands[0].reg << 8;
  inst.instruction |= inst.operands[1].imm << 21;
  /* If this is a vector we are using the APSR_nzcv syntax, encode as r15 */
  if (inst.operands[2].isvec != 0)
    inst.instruction |= 15 << 12;
  else
    inst.instruction |= inst.operands[2].reg << 12;
  inst.instruction |= inst.operands[3].reg << 16;
  inst.instruction |= inst.operands[4].reg;
  inst.instruction |= inst.operands[5].imm << 5;
}