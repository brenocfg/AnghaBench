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
struct TYPE_3__ {int reg; unsigned int imm; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int REG_PC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_bfi (void)
{
  unsigned int msb;

  /* #0 in second position is alternative syntax for bfc, which is
     the same instruction but with REG_PC in the Rm field.  */
  if (!inst.operands[1].isreg)
    inst.operands[1].reg = REG_PC;

  msb = inst.operands[2].imm + inst.operands[3].imm;
  constraint (msb > 32, _("bit-field extends past end of register"));
  /* The instruction encoding stores the LSB and MSB,
     not the LSB and width.  */
  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= inst.operands[1].reg;
  inst.instruction |= inst.operands[2].imm << 7;
  inst.instruction |= (msb - 1) << 16;
}