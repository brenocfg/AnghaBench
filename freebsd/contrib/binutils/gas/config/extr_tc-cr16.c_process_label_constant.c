#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int X_op; int /*<<< orphan*/  X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; } ;
struct TYPE_6__ {TYPE_5__ exp; void* rtype; TYPE_2__* arg; } ;
typedef  TYPE_1__ ins ;
struct TYPE_7__ {int X_op; int size; int /*<<< orphan*/  type; int /*<<< orphan*/  constant; } ;
typedef  TYPE_2__ argument ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARITH_BYTE_INS ; 
 int /*<<< orphan*/  ARITH_INS ; 
 void* BFD_RELOC_CR16_ABS20 ; 
 void* BFD_RELOC_CR16_ABS24 ; 
 void* BFD_RELOC_CR16_DISP16 ; 
 void* BFD_RELOC_CR16_DISP24 ; 
 void* BFD_RELOC_CR16_DISP4 ; 
 void* BFD_RELOC_CR16_DISP8 ; 
 void* BFD_RELOC_CR16_IMM16 ; 
 void* BFD_RELOC_CR16_IMM20 ; 
 void* BFD_RELOC_CR16_IMM32 ; 
 void* BFD_RELOC_CR16_IMM32a ; 
 void* BFD_RELOC_CR16_IMM4 ; 
 void* BFD_RELOC_CR16_REGREL0 ; 
 void* BFD_RELOC_CR16_REGREL14 ; 
 void* BFD_RELOC_CR16_REGREL16 ; 
 void* BFD_RELOC_CR16_REGREL20 ; 
 void* BFD_RELOC_CR16_REGREL20a ; 
 void* BFD_RELOC_CR16_REGREL4 ; 
 void* BFD_RELOC_CR16_REGREL4a ; 
 void* BFD_RELOC_NONE ; 
 int /*<<< orphan*/  BRANCH_INS ; 
 int /*<<< orphan*/  BRANCH_NEQ_INS ; 
 int /*<<< orphan*/  CSTBIT_INS ; 
 int /*<<< orphan*/  IS_INSN_MNEMONIC (char*) ; 
 int /*<<< orphan*/  IS_INSN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_STOR_INS ; 
#define  O_absent 139 
#define  O_add 138 
#define  O_big 137 
#define  O_constant 136 
#define  O_subtract 135 
#define  O_symbol 134 
 int /*<<< orphan*/  STOR_IMM_INS ; 
 int /*<<< orphan*/  _ (char*) ; 
#define  arg_c 133 
#define  arg_cr 132 
#define  arg_crp 131 
#define  arg_ic 130 
#define  arg_idxr 129 
#define  arg_idxrp 128 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int cur_arg_num ; 
 int /*<<< orphan*/  expression (TYPE_5__*) ; 
 char* input_line_pointer ; 
 TYPE_4__* instruction ; 
 int relocatable ; 
 int /*<<< orphan*/  strneq (char*,char*,int) ; 

__attribute__((used)) static void
process_label_constant (char *str, ins * cr16_ins)
{
  char *saved_input_line_pointer;
  int symbol_with_at = 0;
  int symbol_with_s = 0;
  int symbol_with_m = 0;
  int symbol_with_l = 0;
  argument *cur_arg = cr16_ins->arg + cur_arg_num;  /* Current argument.  */

  saved_input_line_pointer = input_line_pointer;
  input_line_pointer = str;

  expression (&cr16_ins->exp);

  switch (cr16_ins->exp.X_op)
    {
    case O_big:
    case O_absent:
      /* Missing or bad expr becomes absolute 0.  */
      as_bad (_("missing or invalid displacement expression `%s' taken as 0"),
	      str);
      cr16_ins->exp.X_op = O_constant;
      cr16_ins->exp.X_add_number = 0;
      cr16_ins->exp.X_add_symbol = NULL;
      cr16_ins->exp.X_op_symbol = NULL;
      /* Fall through.  */

    case O_constant:
      cur_arg->X_op = O_constant;
      cur_arg->constant = cr16_ins->exp.X_add_number;
      break;

    case O_symbol:
    case O_subtract:
    case O_add:
      cur_arg->X_op = O_symbol;
      cr16_ins->rtype = BFD_RELOC_NONE;
      relocatable = 1;

      if (strneq (input_line_pointer, "@c", 2))
	symbol_with_at = 1;

      if (strneq (input_line_pointer, "@l", 2)
	  || strneq (input_line_pointer, ":l", 2))
	symbol_with_l = 1;

      if (strneq (input_line_pointer, "@m", 2)
	  || strneq (input_line_pointer, ":m", 2))
	symbol_with_m = 1;

      if (strneq (input_line_pointer, "@s", 2)
	  || strneq (input_line_pointer, ":s", 2))
	symbol_with_s = 1;

      switch (cur_arg->type)
        {
	case arg_cr:
	  if (IS_INSN_TYPE (LD_STOR_INS) || IS_INSN_TYPE (CSTBIT_INS))
	    {
	      if (cur_arg->size == 20)
		cr16_ins->rtype = BFD_RELOC_CR16_REGREL20;
	      else
		cr16_ins->rtype = BFD_RELOC_CR16_REGREL20a;
	    }
	  break;

	case arg_crp:
	  if (IS_INSN_TYPE (LD_STOR_INS) || IS_INSN_TYPE (CSTBIT_INS))
	    switch (instruction->size)
	      {
	      case 1:
		switch (cur_arg->size)
		  {
		  case 0:
		    cr16_ins->rtype = BFD_RELOC_CR16_REGREL0;
		    break;
		  case 4:
		    if (IS_INSN_MNEMONIC ("loadb") || IS_INSN_MNEMONIC ("storb"))
		      cr16_ins->rtype = BFD_RELOC_CR16_REGREL4;
		    else
		      cr16_ins->rtype = BFD_RELOC_CR16_REGREL4a;
		    break;
		  default: break;
		  }
		break;
	      case 2:
		cr16_ins->rtype = BFD_RELOC_CR16_REGREL16;
		break;
	      case 3:
		if (cur_arg->size == 20)
		  cr16_ins->rtype = BFD_RELOC_CR16_REGREL20;
		else
		  cr16_ins->rtype = BFD_RELOC_CR16_REGREL20a;
		break;
	      default:
		break;
	      }
	  break;

	case arg_idxr:
	  if (IS_INSN_TYPE (LD_STOR_INS) || IS_INSN_TYPE (CSTBIT_INS))
	    cr16_ins->rtype = BFD_RELOC_CR16_REGREL20;
	  break;

	case arg_idxrp:
	  if (IS_INSN_TYPE (LD_STOR_INS) || IS_INSN_TYPE (CSTBIT_INS))
	    switch (instruction->size)
	      {
	      case 1: cr16_ins->rtype = BFD_RELOC_CR16_REGREL0; break;
	      case 2: cr16_ins->rtype = BFD_RELOC_CR16_REGREL14; break;
	      case 3: cr16_ins->rtype = BFD_RELOC_CR16_REGREL20; break;
	      default: break;
	      }
	  break;

	case arg_c:
	  if (IS_INSN_MNEMONIC ("bal"))
	    cr16_ins->rtype = BFD_RELOC_CR16_DISP24;
	  else if (IS_INSN_TYPE (BRANCH_INS))
	    {
	      if (symbol_with_s)
		cr16_ins->rtype = BFD_RELOC_CR16_DISP8;
	      else if (symbol_with_m)
		cr16_ins->rtype = BFD_RELOC_CR16_DISP16;
	      else
		cr16_ins->rtype = BFD_RELOC_CR16_DISP24;
	    }
	  else if (IS_INSN_TYPE (STOR_IMM_INS) || IS_INSN_TYPE (LD_STOR_INS)
		   || IS_INSN_TYPE (CSTBIT_INS))
	    {
	      if (symbol_with_s)
		as_bad (_("operand %d: illegal use expression: `%s`"), cur_arg_num + 1, str);
	      if (symbol_with_m)
		cr16_ins->rtype = BFD_RELOC_CR16_ABS20;
	      else /* Default to (symbol_with_l) */
		cr16_ins->rtype = BFD_RELOC_CR16_ABS24;
	    }
	  else if (IS_INSN_TYPE (BRANCH_NEQ_INS))
	    cr16_ins->rtype = BFD_RELOC_CR16_DISP4;
          break;

        case arg_ic:
          if (IS_INSN_TYPE (ARITH_INS))
            {
              if (symbol_with_s)
                cr16_ins->rtype = BFD_RELOC_CR16_IMM4;
              else if (symbol_with_m)
                cr16_ins->rtype = BFD_RELOC_CR16_IMM20;
              else if (symbol_with_at)
                cr16_ins->rtype = BFD_RELOC_CR16_IMM32a;
              else /* Default to (symbol_with_l) */
                cr16_ins->rtype = BFD_RELOC_CR16_IMM32;
            }
          else if (IS_INSN_TYPE (ARITH_BYTE_INS))
	    {
	      cr16_ins->rtype = BFD_RELOC_CR16_IMM16;
	    }
          break;
        default:
          break;
	}
      break;

    default:
      cur_arg->X_op = cr16_ins->exp.X_op;
      break;
    }

  input_line_pointer = saved_input_line_pointer;
  return;
}