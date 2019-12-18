#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AND 148 
 int CCFPEmode ; 
 int CCFPmode ; 
 scalar_t__ CCXmode ; 
 scalar_t__ CCmode ; 
 int /*<<< orphan*/  CONST0_RTX (scalar_t__) ; 
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DOUBLE ; 
 int CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SIZE (int /*<<< orphan*/ ) ; 
 char* EMBMEDANY_BASE_REG ; 
#define  EQ 147 
#define  GE 146 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (scalar_t__) ; 
#define  GEU 145 
#define  GT 144 
#define  GTU 143 
 scalar_t__ HIGH ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int /*<<< orphan*/  INTEGER_CST ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 142 
#define  LE 141 
#define  LEU 140 
 scalar_t__ LO_SUM ; 
#define  LT 139 
#define  LTGT 138 
#define  LTU 137 
 scalar_t__ MEM ; 
 scalar_t__ MODE_INT ; 
#define  NE 136 
#define  ORDERED 135 
 int PROCESSOR_V9 ; 
 int /*<<< orphan*/  QImode ; 
 scalar_t__ REG ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 size_t SPARC_ICC_REG ; 
 int /*<<< orphan*/  TARGET_ARCH64 ; 
 scalar_t__ TARGET_CM_MEDMID ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
#define  UNEQ 134 
#define  UNGE 133 
#define  UNGT 132 
#define  UNLE 131 
#define  UNLT 130 
#define  UNORDERED 129 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  XOR 128 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  current_function_returns_struct ; 
 int /*<<< orphan*/  final_sequence ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_some_local_dynamic_name () ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optimize ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 char** reg_names ; 
 scalar_t__ reverse_condition (scalar_t__) ; 
 int reverse_condition_maybe_unordered (scalar_t__) ; 
 scalar_t__ sparc_cpu ; 
 int sparc_indent_opcode ; 
 int /*<<< orphan*/  sparc_std_struct_return ; 
 int trunc_int_for_mode (int,int /*<<< orphan*/ ) ; 

void
print_operand (FILE *file, rtx x, int code)
{
  switch (code)
    {
    case '#':
      /* Output an insn in a delay slot.  */
      if (final_sequence)
        sparc_indent_opcode = 1;
      else
	fputs ("\n\t nop", file);
      return;
    case '*':
      /* Output an annul flag if there's nothing for the delay slot and we
	 are optimizing.  This is always used with '(' below.
         Sun OS 4.1.1 dbx can't handle an annulled unconditional branch;
	 this is a dbx bug.  So, we only do this when optimizing.
         On UltraSPARC, a branch in a delay slot causes a pipeline flush.
	 Always emit a nop in case the next instruction is a branch.  */
      if (! final_sequence && (optimize && (int)sparc_cpu < PROCESSOR_V9))
	fputs (",a", file);
      return;
    case '(':
      /* Output a 'nop' if there's nothing for the delay slot and we are
	 not optimizing.  This is always used with '*' above.  */
      if (! final_sequence && ! (optimize && (int)sparc_cpu < PROCESSOR_V9))
	fputs ("\n\t nop", file);
      else if (final_sequence)
        sparc_indent_opcode = 1;
      return;
    case ')':
      /* Output the right displacement from the saved PC on function return.
	 The caller may have placed an "unimp" insn immediately after the call
	 so we have to account for it.  This insn is used in the 32-bit ABI
	 when calling a function that returns a non zero-sized structure. The
	 64-bit ABI doesn't have it.  Be careful to have this test be the same
	 as that used on the call. The exception here is that when 
	 sparc_std_struct_return is enabled, the psABI is followed exactly
	 and the adjustment is made by the code in sparc_struct_value_rtx. 
	 The call emitted is the same when sparc_std_struct_return is 
	 present. */
     if (! TARGET_ARCH64
	 && current_function_returns_struct
	 && ! sparc_std_struct_return
	 && (TREE_CODE (DECL_SIZE (DECL_RESULT (current_function_decl)))
	     == INTEGER_CST)
	 && ! integer_zerop (DECL_SIZE (DECL_RESULT (current_function_decl))))
	fputs ("12", file);
      else
        fputc ('8', file);
      return;
    case '_':
      /* Output the Embedded Medium/Anywhere code model base register.  */
      fputs (EMBMEDANY_BASE_REG, file);
      return;
    case '&':
      /* Print some local dynamic TLS name.  */
      assemble_name (file, get_some_local_dynamic_name ());
      return;

    case 'Y':
      /* Adjust the operand to take into account a RESTORE operation.  */
      if (GET_CODE (x) == CONST_INT)
	break;
      else if (GET_CODE (x) != REG)
	output_operand_lossage ("invalid %%Y operand");
      else if (REGNO (x) < 8)
	fputs (reg_names[REGNO (x)], file);
      else if (REGNO (x) >= 24 && REGNO (x) < 32)
	fputs (reg_names[REGNO (x)-16], file);
      else
	output_operand_lossage ("invalid %%Y operand");
      return;
    case 'L':
      /* Print out the low order register name of a register pair.  */
      if (WORDS_BIG_ENDIAN)
	fputs (reg_names[REGNO (x)+1], file);
      else
	fputs (reg_names[REGNO (x)], file);
      return;
    case 'H':
      /* Print out the high order register name of a register pair.  */
      if (WORDS_BIG_ENDIAN)
	fputs (reg_names[REGNO (x)], file);
      else
	fputs (reg_names[REGNO (x)+1], file);
      return;
    case 'R':
      /* Print out the second register name of a register pair or quad.
	 I.e., R (%o0) => %o1.  */
      fputs (reg_names[REGNO (x)+1], file);
      return;
    case 'S':
      /* Print out the third register name of a register quad.
	 I.e., S (%o0) => %o2.  */
      fputs (reg_names[REGNO (x)+2], file);
      return;
    case 'T':
      /* Print out the fourth register name of a register quad.
	 I.e., T (%o0) => %o3.  */
      fputs (reg_names[REGNO (x)+3], file);
      return;
    case 'x':
      /* Print a condition code register.  */
      if (REGNO (x) == SPARC_ICC_REG)
	{
	  /* We don't handle CC[X]_NOOVmode because they're not supposed
	     to occur here.  */
	  if (GET_MODE (x) == CCmode)
	    fputs ("%icc", file);
	  else if (GET_MODE (x) == CCXmode)
	    fputs ("%xcc", file);
	  else
	    gcc_unreachable ();
	}
      else
	/* %fccN register */
	fputs (reg_names[REGNO (x)], file);
      return;
    case 'm':
      /* Print the operand's address only.  */
      output_address (XEXP (x, 0));
      return;
    case 'r':
      /* In this case we need a register.  Use %g0 if the
	 operand is const0_rtx.  */
      if (x == const0_rtx
	  || (GET_MODE (x) != VOIDmode && x == CONST0_RTX (GET_MODE (x))))
	{
	  fputs ("%g0", file);
	  return;
	}
      else
	break;

    case 'A':
      switch (GET_CODE (x))
	{
	case IOR: fputs ("or", file); break;
	case AND: fputs ("and", file); break;
	case XOR: fputs ("xor", file); break;
	default: output_operand_lossage ("invalid %%A operand");
	}
      return;

    case 'B':
      switch (GET_CODE (x))
	{
	case IOR: fputs ("orn", file); break;
	case AND: fputs ("andn", file); break;
	case XOR: fputs ("xnor", file); break;
	default: output_operand_lossage ("invalid %%B operand");
	}
      return;

      /* These are used by the conditional move instructions.  */
    case 'c' :
    case 'C':
      {
	enum rtx_code rc = GET_CODE (x);
	
	if (code == 'c')
	  {
	    enum machine_mode mode = GET_MODE (XEXP (x, 0));
	    if (mode == CCFPmode || mode == CCFPEmode)
	      rc = reverse_condition_maybe_unordered (GET_CODE (x));
	    else
	      rc = reverse_condition (GET_CODE (x));
	  }
	switch (rc)
	  {
	  case NE: fputs ("ne", file); break;
	  case EQ: fputs ("e", file); break;
	  case GE: fputs ("ge", file); break;
	  case GT: fputs ("g", file); break;
	  case LE: fputs ("le", file); break;
	  case LT: fputs ("l", file); break;
	  case GEU: fputs ("geu", file); break;
	  case GTU: fputs ("gu", file); break;
	  case LEU: fputs ("leu", file); break;
	  case LTU: fputs ("lu", file); break;
	  case LTGT: fputs ("lg", file); break;
	  case UNORDERED: fputs ("u", file); break;
	  case ORDERED: fputs ("o", file); break;
	  case UNLT: fputs ("ul", file); break;
	  case UNLE: fputs ("ule", file); break;
	  case UNGT: fputs ("ug", file); break;
	  case UNGE: fputs ("uge", file); break;
	  case UNEQ: fputs ("ue", file); break;
	  default: output_operand_lossage (code == 'c'
					   ? "invalid %%c operand"
					   : "invalid %%C operand");
	  }
	return;
      }

      /* These are used by the movr instruction pattern.  */
    case 'd':
    case 'D':
      {
	enum rtx_code rc = (code == 'd'
			    ? reverse_condition (GET_CODE (x))
			    : GET_CODE (x));
	switch (rc)
	  {
	  case NE: fputs ("ne", file); break;
	  case EQ: fputs ("e", file); break;
	  case GE: fputs ("gez", file); break;
	  case LT: fputs ("lz", file); break;
	  case LE: fputs ("lez", file); break;
	  case GT: fputs ("gz", file); break;
	  default: output_operand_lossage (code == 'd'
					   ? "invalid %%d operand"
					   : "invalid %%D operand");
	  }
	return;
      }

    case 'b':
      {
	/* Print a sign-extended character.  */
	int i = trunc_int_for_mode (INTVAL (x), QImode);
	fprintf (file, "%d", i);
	return;
      }

    case 'f':
      /* Operand must be a MEM; write its address.  */
      if (GET_CODE (x) != MEM)
	output_operand_lossage ("invalid %%f operand");
      output_address (XEXP (x, 0));
      return;

    case 's':
      {
	/* Print a sign-extended 32-bit value.  */
	HOST_WIDE_INT i;
	if (GET_CODE(x) == CONST_INT)
	  i = INTVAL (x);
	else if (GET_CODE(x) == CONST_DOUBLE)
	  i = CONST_DOUBLE_LOW (x);
	else
	  {
	    output_operand_lossage ("invalid %%s operand");
	    return;
	  }
	i = trunc_int_for_mode (i, SImode);
	fprintf (file, HOST_WIDE_INT_PRINT_DEC, i);
	return;
      }

    case 0:
      /* Do nothing special.  */
      break;

    default:
      /* Undocumented flag.  */
      output_operand_lossage ("invalid operand output code");
    }

  if (GET_CODE (x) == REG)
    fputs (reg_names[REGNO (x)], file);
  else if (GET_CODE (x) == MEM)
    {
      fputc ('[', file);
	/* Poor Sun assembler doesn't understand absolute addressing.  */
      if (CONSTANT_P (XEXP (x, 0)))
	fputs ("%g0+", file);
      output_address (XEXP (x, 0));
      fputc (']', file);
    }
  else if (GET_CODE (x) == HIGH)
    {
      fputs ("%hi(", file);
      output_addr_const (file, XEXP (x, 0));
      fputc (')', file);
    }
  else if (GET_CODE (x) == LO_SUM)
    {
      print_operand (file, XEXP (x, 0), 0);
      if (TARGET_CM_MEDMID)
	fputs ("+%l44(", file);
      else
	fputs ("+%lo(", file);
      output_addr_const (file, XEXP (x, 1));
      fputc (')', file);
    }
  else if (GET_CODE (x) == CONST_DOUBLE
	   && (GET_MODE (x) == VOIDmode
	       || GET_MODE_CLASS (GET_MODE (x)) == MODE_INT))
    {
      if (CONST_DOUBLE_HIGH (x) == 0)
	fprintf (file, "%u", (unsigned int) CONST_DOUBLE_LOW (x));
      else if (CONST_DOUBLE_HIGH (x) == -1
	       && CONST_DOUBLE_LOW (x) < 0)
	fprintf (file, "%d", (int) CONST_DOUBLE_LOW (x));
      else
	output_operand_lossage ("long long constant not a valid immediate operand");
    }
  else if (GET_CODE (x) == CONST_DOUBLE)
    output_operand_lossage ("floating point constant not a valid immediate operand");
  else { output_addr_const (file, x); }
}