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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int instruction; TYPE_1__ reloc; TYPE_2__* operands; } ;
struct TYPE_5__ {int shift_kind; int imm; scalar_t__ immisreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_SHIFT_IMM ; 
 int SHIFT_BY_REG ; 
 int SHIFT_ROR ; 
 int SHIFT_RRX ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
encode_arm_shift (int i)
{
  if (inst.operands[i].shift_kind == SHIFT_RRX)
    inst.instruction |= SHIFT_ROR << 5;
  else
    {
      inst.instruction |= inst.operands[i].shift_kind << 5;
      if (inst.operands[i].immisreg)
	{
	  inst.instruction |= SHIFT_BY_REG;
	  inst.instruction |= inst.operands[i].imm << 8;
	}
      else
	inst.reloc.type = BFD_RELOC_ARM_SHIFT_IMM;
    }
}