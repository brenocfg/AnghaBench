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
typedef  scalar_t__ bfd_boolean ;
struct TYPE_5__ {scalar_t__ X_op; int X_add_number; } ;
struct TYPE_7__ {int pc_rel; int /*<<< orphan*/  type; TYPE_1__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_3__ reloc; TYPE_2__* operands; void* error; } ;
struct TYPE_6__ {int reg; int isreg; int preind; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_HWLITERAL ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_LITERAL ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_THUMB_OFFSET ; 
 int DATA_OP_SHIFT ; 
 int FAIL ; 
 int INST_IMMEDIATE ; 
 int LITERAL_MASK ; 
 unsigned long LOAD_BIT ; 
 int OPCODE_MOV ; 
 int OPCODE_MVN ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 
 int REG_PC ; 
 unsigned long THUMB2_LOAD_BIT ; 
 unsigned long THUMB_LOAD_BIT ; 
 int T_OPCODE_MOV_I8 ; 
 void* _ (char*) ; 
 int add_to_lit_pool () ; 
 int encode_arm_immediate (int) ; 
 TYPE_4__ inst ; 
 int /*<<< orphan*/  unified_syntax ; 

__attribute__((used)) static int
move_or_literal_pool (int i, bfd_boolean thumb_p, bfd_boolean mode_3)
{
  unsigned long tbit;

  if (thumb_p)
    tbit = (inst.instruction > 0xffff) ? THUMB2_LOAD_BIT : THUMB_LOAD_BIT;
  else
    tbit = LOAD_BIT;

  if ((inst.instruction & tbit) == 0)
    {
      inst.error = _("invalid pseudo operation");
      return 1;
    }
  if (inst.reloc.exp.X_op != O_constant && inst.reloc.exp.X_op != O_symbol)
    {
      inst.error = _("constant expression expected");
      return 1;
    }
  if (inst.reloc.exp.X_op == O_constant)
    {
      if (thumb_p)
	{
	  if (!unified_syntax && (inst.reloc.exp.X_add_number & ~0xFF) == 0)
	    {
	      /* This can be done with a mov(1) instruction.  */
	      inst.instruction	= T_OPCODE_MOV_I8 | (inst.operands[i].reg << 8);
	      inst.instruction |= inst.reloc.exp.X_add_number;
	      return 1;
	    }
	}
      else
	{
	  int value = encode_arm_immediate (inst.reloc.exp.X_add_number);
	  if (value != FAIL)
	    {
	      /* This can be done with a mov instruction.  */
	      inst.instruction &= LITERAL_MASK;
	      inst.instruction |= INST_IMMEDIATE | (OPCODE_MOV << DATA_OP_SHIFT);
	      inst.instruction |= value & 0xfff;
	      return 1;
	    }

	  value = encode_arm_immediate (~inst.reloc.exp.X_add_number);
	  if (value != FAIL)
	    {
	      /* This can be done with a mvn instruction.  */
	      inst.instruction &= LITERAL_MASK;
	      inst.instruction |= INST_IMMEDIATE | (OPCODE_MVN << DATA_OP_SHIFT);
	      inst.instruction |= value & 0xfff;
	      return 1;
	    }
	}
    }

  if (add_to_lit_pool () == FAIL)
    {
      inst.error = _("literal pool insertion failed");
      return 1;
    }
  inst.operands[1].reg = REG_PC;
  inst.operands[1].isreg = 1;
  inst.operands[1].preind = 1;
  inst.reloc.pc_rel = 1;
  inst.reloc.type = (thumb_p
		     ? BFD_RELOC_ARM_THUMB_OFFSET
		     : (mode_3
			? BFD_RELOC_ARM_HWLITERAL
			: BFD_RELOC_ARM_LITERAL));
  return 0;
}