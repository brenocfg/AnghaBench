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
struct TYPE_4__ {void* type; } ;
struct TYPE_6__ {int instruction; int size_req; TYPE_2__* operands; TYPE_1__ reloc; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int reg; int shifted; int shift_kind; scalar_t__ isreg; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_HIREG ; 
 int /*<<< orphan*/  BAD_THUMB32 ; 
 void* BFD_RELOC_ARM_THUMB_SHIFT ; 
 void* BFD_RELOC_UNUSED ; 
 int FALSE ; 
#define  SHIFT_ASR 139 
#define  SHIFT_LSL 138 
#define  SHIFT_LSR 137 
#define  SHIFT_ROR 136 
 void* THUMB_OP32 (int) ; 
 int THUMB_SETS_FLAGS (int) ; 
#define  T_MNEM_asr 135 
#define  T_MNEM_asrs 134 
#define  T_MNEM_lsl 133 
#define  T_MNEM_lsls 132 
#define  T_MNEM_lsr 131 
#define  T_MNEM_lsrs 130 
 int T_MNEM_mov ; 
 int T_MNEM_movs ; 
#define  T_MNEM_ror 129 
#define  T_MNEM_rors 128 
 void* T_OPCODE_ASR_I ; 
 void* T_OPCODE_ASR_R ; 
 void* T_OPCODE_LSL_I ; 
 void* T_OPCODE_LSL_R ; 
 void* T_OPCODE_LSR_I ; 
 void* T_OPCODE_LSR_R ; 
 void* T_OPCODE_ROR_R ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 scalar_t__ current_it_mask ; 
 int /*<<< orphan*/  encode_thumb32_shifted_operand (int) ; 
 TYPE_3__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_shift (void)
{
  if (!inst.operands[1].present)
    inst.operands[1].reg = inst.operands[0].reg;

  if (unified_syntax)
    {
      bfd_boolean narrow;
      int shift_kind;

      switch (inst.instruction)
	{
	case T_MNEM_asr:
	case T_MNEM_asrs: shift_kind = SHIFT_ASR; break;
	case T_MNEM_lsl:
	case T_MNEM_lsls: shift_kind = SHIFT_LSL; break;
	case T_MNEM_lsr:
	case T_MNEM_lsrs: shift_kind = SHIFT_LSR; break;
	case T_MNEM_ror:
	case T_MNEM_rors: shift_kind = SHIFT_ROR; break;
	default: abort ();
	}

      if (THUMB_SETS_FLAGS (inst.instruction))
	narrow = (current_it_mask == 0);
      else
	narrow = (current_it_mask != 0);
      if (inst.operands[0].reg > 7 || inst.operands[1].reg > 7)
	narrow = FALSE;
      if (!inst.operands[2].isreg && shift_kind == SHIFT_ROR)
	narrow = FALSE;
      if (inst.operands[2].isreg
	  && (inst.operands[1].reg != inst.operands[0].reg
	      || inst.operands[2].reg > 7))
	narrow = FALSE;
      if (inst.size_req == 4)
	narrow = FALSE;

      if (!narrow)
	{
	  if (inst.operands[2].isreg)
	    {
	      inst.instruction = THUMB_OP32 (inst.instruction);
	      inst.instruction |= inst.operands[0].reg << 8;
	      inst.instruction |= inst.operands[1].reg << 16;
	      inst.instruction |= inst.operands[2].reg;
	    }
	  else
	    {
	      inst.operands[1].shifted = 1;
	      inst.operands[1].shift_kind = shift_kind;
	      inst.instruction = THUMB_OP32 (THUMB_SETS_FLAGS (inst.instruction)
					     ? T_MNEM_movs : T_MNEM_mov);
	      inst.instruction |= inst.operands[0].reg << 8;
	      encode_thumb32_shifted_operand (1);
	      /* Prevent the incorrect generation of an ARM_IMMEDIATE fixup.  */
	      inst.reloc.type = BFD_RELOC_UNUSED;
	    }
	}
      else
	{
	  if (inst.operands[2].isreg)
	    {
	      switch (shift_kind)
		{
		case SHIFT_ASR: inst.instruction = T_OPCODE_ASR_R; break;
		case SHIFT_LSL: inst.instruction = T_OPCODE_LSL_R; break;
		case SHIFT_LSR: inst.instruction = T_OPCODE_LSR_R; break;
		case SHIFT_ROR: inst.instruction = T_OPCODE_ROR_R; break;
		default: abort ();
		}
	  
	      inst.instruction |= inst.operands[0].reg;
	      inst.instruction |= inst.operands[2].reg << 3;
	    }
	  else
	    {
	      switch (shift_kind)
		{
		case SHIFT_ASR: inst.instruction = T_OPCODE_ASR_I; break;
		case SHIFT_LSL: inst.instruction = T_OPCODE_LSL_I; break;
		case SHIFT_LSR: inst.instruction = T_OPCODE_LSR_I; break;
		default: abort ();
		}
	      inst.reloc.type = BFD_RELOC_ARM_THUMB_SHIFT;
	      inst.instruction |= inst.operands[0].reg;
	      inst.instruction |= inst.operands[1].reg << 3;
	    }
	}
    }
  else
    {
      constraint (inst.operands[0].reg > 7
		  || inst.operands[1].reg > 7, BAD_HIREG);
      constraint (THUMB_SETS_FLAGS (inst.instruction), BAD_THUMB32);

      if (inst.operands[2].isreg)  /* Rd, {Rs,} Rn */
	{
	  constraint (inst.operands[2].reg > 7, BAD_HIREG);
	  constraint (inst.operands[0].reg != inst.operands[1].reg,
		      _("source1 and dest must be same register"));

	  switch (inst.instruction)
	    {
	    case T_MNEM_asr: inst.instruction = T_OPCODE_ASR_R; break;
	    case T_MNEM_lsl: inst.instruction = T_OPCODE_LSL_R; break;
	    case T_MNEM_lsr: inst.instruction = T_OPCODE_LSR_R; break;
	    case T_MNEM_ror: inst.instruction = T_OPCODE_ROR_R; break;
	    default: abort ();
	    }
	  
	  inst.instruction |= inst.operands[0].reg;
	  inst.instruction |= inst.operands[2].reg << 3;
	}
      else
	{
	  switch (inst.instruction)
	    {
	    case T_MNEM_asr: inst.instruction = T_OPCODE_ASR_I; break;
	    case T_MNEM_lsl: inst.instruction = T_OPCODE_LSL_I; break;
	    case T_MNEM_lsr: inst.instruction = T_OPCODE_LSR_I; break;
	    case T_MNEM_ror: inst.error = _("ror #imm not supported"); return;
	    default: abort ();
	    }
	  inst.reloc.type = BFD_RELOC_ARM_THUMB_SHIFT;
	  inst.instruction |= inst.operands[0].reg;
	  inst.instruction |= inst.operands[1].reg << 3;
	}
    }
}