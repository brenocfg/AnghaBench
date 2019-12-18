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
typedef  int bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int instruction; int size_req; TYPE_2__* operands; TYPE_1__ reloc; } ;
struct TYPE_5__ {int reg; scalar_t__ shifted; int /*<<< orphan*/  isreg; scalar_t__ immisreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_HIREG ; 
 int /*<<< orphan*/  BAD_THUMB32 ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_T32_IMMEDIATE ; 
 int FALSE ; 
 void* THUMB_OP16 (int) ; 
 void* THUMB_OP32 (int) ; 
 scalar_t__ THUMB_SETS_FLAGS (int) ; 
 int TRUE ; 
 int T_MNEM_cmn ; 
 int T_MNEM_mvn ; 
 int T_MNEM_mvns ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 scalar_t__ current_it_mask ; 
 int /*<<< orphan*/  encode_thumb32_shifted_operand (int) ; 
 TYPE_3__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_mvn_tst (void)
{
  if (unified_syntax)
    {
      int r0off = (inst.instruction == T_MNEM_mvn
		   || inst.instruction == T_MNEM_mvns) ? 8 : 16;
      bfd_boolean narrow;

      if (inst.size_req == 4
	  || inst.instruction > 0xffff
	  || inst.operands[1].shifted
	  || inst.operands[0].reg > 7 || inst.operands[1].reg > 7)
	narrow = FALSE;
      else if (inst.instruction == T_MNEM_cmn)
	narrow = TRUE;
      else if (THUMB_SETS_FLAGS (inst.instruction))
	narrow = (current_it_mask == 0);
      else
	narrow = (current_it_mask != 0);

      if (!inst.operands[1].isreg)
	{
	  /* For an immediate, we always generate a 32-bit opcode;
	     section relaxation will shrink it later if possible.  */
	  if (inst.instruction < 0xffff)
	    inst.instruction = THUMB_OP32 (inst.instruction);
	  inst.instruction = (inst.instruction & 0xe1ffffff) | 0x10000000;
	  inst.instruction |= inst.operands[0].reg << r0off;
	  inst.reloc.type = BFD_RELOC_ARM_T32_IMMEDIATE;
	}
      else
	{
	  /* See if we can do this with a 16-bit instruction.  */
	  if (narrow)
	    {
	      inst.instruction = THUMB_OP16 (inst.instruction);
	      inst.instruction |= inst.operands[0].reg;
	      inst.instruction |= inst.operands[1].reg << 3;
	    }
	  else
	    {
	      constraint (inst.operands[1].shifted
			  && inst.operands[1].immisreg,
			  _("shift must be constant"));
	      if (inst.instruction < 0xffff)
		inst.instruction = THUMB_OP32 (inst.instruction);
	      inst.instruction |= inst.operands[0].reg << r0off;
	      encode_thumb32_shifted_operand (1);
	    }
	}
    }
  else
    {
      constraint (inst.instruction > 0xffff
		  || inst.instruction == T_MNEM_mvns, BAD_THUMB32);
      constraint (!inst.operands[1].isreg || inst.operands[1].shifted,
		  _("unshifted register required"));
      constraint (inst.operands[0].reg > 7 || inst.operands[1].reg > 7,
		  BAD_HIREG);

      inst.instruction = THUMB_OP16 (inst.instruction);
      inst.instruction |= inst.operands[0].reg;
      inst.instruction |= inst.operands[1].reg << 3;
    }
}