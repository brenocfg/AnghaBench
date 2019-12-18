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
struct TYPE_4__ {int instruction; int size_req; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; int imm; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_HIREG ; 
 int THUMB_OP16 (int) ; 
 int THUMB_OP32 (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_sxth (void)
{
  if (inst.instruction <= 0xffff && inst.size_req != 4
      && inst.operands[0].reg <= 7 && inst.operands[1].reg <= 7
      && (!inst.operands[2].present || inst.operands[2].imm == 0))
    {
      inst.instruction = THUMB_OP16 (inst.instruction);
      inst.instruction |= inst.operands[0].reg;
      inst.instruction |= inst.operands[1].reg << 3;
    }
  else if (unified_syntax)
    {
      if (inst.instruction <= 0xffff)
	inst.instruction = THUMB_OP32 (inst.instruction);
      inst.instruction |= inst.operands[0].reg << 8;
      inst.instruction |= inst.operands[1].reg;
      inst.instruction |= inst.operands[2].imm << 4;
    }
  else
    {
      constraint (inst.operands[2].present && inst.operands[2].imm != 0,
		  _("Thumb encoding does not support rotation"));
      constraint (1, BAD_HIREG);
    }
}