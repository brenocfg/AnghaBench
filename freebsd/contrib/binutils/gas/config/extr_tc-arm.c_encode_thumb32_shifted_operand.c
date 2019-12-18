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
struct TYPE_6__ {unsigned int X_add_number; scalar_t__ X_op; } ;
struct TYPE_7__ {TYPE_2__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_3__ reloc; TYPE_1__* operands; } ;
struct TYPE_5__ {unsigned int shift_kind; int immisreg; int reg; } ;

/* Variables and functions */
 scalar_t__ O_constant ; 
 unsigned int SHIFT_LSL ; 
 int SHIFT_ROR ; 
 unsigned int SHIFT_RRX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
encode_thumb32_shifted_operand (int i)
{
  unsigned int value = inst.reloc.exp.X_add_number;
  unsigned int shift = inst.operands[i].shift_kind;

  constraint (inst.operands[i].immisreg,
	      _("shift by register not allowed in thumb mode"));
  inst.instruction |= inst.operands[i].reg;
  if (shift == SHIFT_RRX)
    inst.instruction |= SHIFT_ROR << 4;
  else
    {
      constraint (inst.reloc.exp.X_op != O_constant,
		  _("expression too complex"));

      constraint (value > 32
		  || (value == 32 && (shift == SHIFT_LSL
				      || shift == SHIFT_ROR)),
		  _("shift expression is too large"));

      if (value == 0)
	shift = SHIFT_LSL;
      else if (value == 32)
	value = 0;

      inst.instruction |= shift << 4;
      inst.instruction |= (value & 0x1c) << 10;
      inst.instruction |= (value & 0x03) << 6;
    }
}