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
struct TYPE_5__ {scalar_t__ X_op; int X_add_number; } ;
struct TYPE_6__ {TYPE_1__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_3__* operands; TYPE_2__ reloc; } ;
struct TYPE_7__ {int reg; int imm; int postind; scalar_t__ preind; scalar_t__ writeback; } ;

/* Variables and functions */
 int CP_T_X ; 
 int CP_T_Y ; 
 int INDEX_UP ; 
 scalar_t__ O_constant ; 
 int PRE_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_arm_cp_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
do_fpa_ldmstm (void)
{
  inst.instruction |= inst.operands[0].reg << 12;
  switch (inst.operands[1].imm)
    {
    case 1: inst.instruction |= CP_T_X;		 break;
    case 2: inst.instruction |= CP_T_Y;		 break;
    case 3: inst.instruction |= CP_T_Y | CP_T_X; break;
    case 4:					 break;
    default: abort ();
    }

  if (inst.instruction & (PRE_INDEX | INDEX_UP))
    {
      /* The instruction specified "ea" or "fd", so we can only accept
	 [Rn]{!}.  The instruction does not really support stacking or
	 unstacking, so we have to emulate these by setting appropriate
	 bits and offsets.  */
      constraint (inst.reloc.exp.X_op != O_constant
		  || inst.reloc.exp.X_add_number != 0,
		  _("this instruction does not support indexing"));

      if ((inst.instruction & PRE_INDEX) || inst.operands[2].writeback)
	inst.reloc.exp.X_add_number = 12 * inst.operands[1].imm;

      if (!(inst.instruction & INDEX_UP))
	inst.reloc.exp.X_add_number = -inst.reloc.exp.X_add_number;

      if (!(inst.instruction & PRE_INDEX) && inst.operands[2].writeback)
	{
	  inst.operands[2].preind = 0;
	  inst.operands[2].postind = 1;
	}
    }

  encode_arm_cp_address (2, TRUE, TRUE, 0);
}