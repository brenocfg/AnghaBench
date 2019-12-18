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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  close_paren; int /*<<< orphan*/  open_paren; } ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_LABEL_REF (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ASM_OUTPUT_SYMBOL_REF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  CODE_LABEL 139 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
#define  CONST 138 
#define  CONST_DOUBLE 137 
 int /*<<< orphan*/  CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 136 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 char* HOST_WIDE_INT_PRINT_DOUBLE_HEX ; 
 char* HOST_WIDE_INT_PRINT_HEX ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 135 
#define  MINUS 134 
 int /*<<< orphan*/  OUTPUT_ADDR_CONST_EXTRA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PC 133 
#define  PLUS 132 
#define  SIGN_EXTEND 131 
#define  SUBREG 130 
#define  SYMBOL_REF 129 
 int /*<<< orphan*/  SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fail ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_decl_referenced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplify_subtraction (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

void
output_addr_const (FILE *file, rtx x)
{
  char buf[256];

 restart:
  switch (GET_CODE (x))
    {
    case PC:
      putc ('.', file);
      break;

    case SYMBOL_REF:
      if (SYMBOL_REF_DECL (x))
	mark_decl_referenced (SYMBOL_REF_DECL (x));
#ifdef ASM_OUTPUT_SYMBOL_REF
      ASM_OUTPUT_SYMBOL_REF (file, x);
#else
      assemble_name (file, XSTR (x, 0));
#endif
      break;

    case LABEL_REF:
      x = XEXP (x, 0);
      /* Fall through.  */
    case CODE_LABEL:
      ASM_GENERATE_INTERNAL_LABEL (buf, "L", CODE_LABEL_NUMBER (x));
#ifdef ASM_OUTPUT_LABEL_REF
      ASM_OUTPUT_LABEL_REF (file, buf);
#else
      assemble_name (file, buf);
#endif
      break;

    case CONST_INT:
      fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
      break;

    case CONST:
      /* This used to output parentheses around the expression,
	 but that does not work on the 386 (either ATT or BSD assembler).  */
      output_addr_const (file, XEXP (x, 0));
      break;

    case CONST_DOUBLE:
      if (GET_MODE (x) == VOIDmode)
	{
	  /* We can use %d if the number is one word and positive.  */
	  if (CONST_DOUBLE_HIGH (x))
	    fprintf (file, HOST_WIDE_INT_PRINT_DOUBLE_HEX,
		     CONST_DOUBLE_HIGH (x), CONST_DOUBLE_LOW (x));
	  else if (CONST_DOUBLE_LOW (x) < 0)
	    fprintf (file, HOST_WIDE_INT_PRINT_HEX, CONST_DOUBLE_LOW (x));
	  else
	    fprintf (file, HOST_WIDE_INT_PRINT_DEC, CONST_DOUBLE_LOW (x));
	}
      else
	/* We can't handle floating point constants;
	   PRINT_OPERAND must handle them.  */
	output_operand_lossage ("floating constant misused");
      break;

    case PLUS:
      /* Some assemblers need integer constants to appear last (eg masm).  */
      if (GET_CODE (XEXP (x, 0)) == CONST_INT)
	{
	  output_addr_const (file, XEXP (x, 1));
	  if (INTVAL (XEXP (x, 0)) >= 0)
	    fprintf (file, "+");
	  output_addr_const (file, XEXP (x, 0));
	}
      else
	{
	  output_addr_const (file, XEXP (x, 0));
	  if (GET_CODE (XEXP (x, 1)) != CONST_INT
	      || INTVAL (XEXP (x, 1)) >= 0)
	    fprintf (file, "+");
	  output_addr_const (file, XEXP (x, 1));
	}
      break;

    case MINUS:
      /* Avoid outputting things like x-x or x+5-x,
	 since some assemblers can't handle that.  */
      x = simplify_subtraction (x);
      if (GET_CODE (x) != MINUS)
	goto restart;

      output_addr_const (file, XEXP (x, 0));
      fprintf (file, "-");
      if ((GET_CODE (XEXP (x, 1)) == CONST_INT && INTVAL (XEXP (x, 1)) >= 0)
	  || GET_CODE (XEXP (x, 1)) == PC
	  || GET_CODE (XEXP (x, 1)) == SYMBOL_REF)
	output_addr_const (file, XEXP (x, 1));
      else
	{
	  fputs (targetm.asm_out.open_paren, file);
	  output_addr_const (file, XEXP (x, 1));
	  fputs (targetm.asm_out.close_paren, file);
	}
      break;

    case ZERO_EXTEND:
    case SIGN_EXTEND:
    case SUBREG:
      output_addr_const (file, XEXP (x, 0));
      break;

    default:
#ifdef OUTPUT_ADDR_CONST_EXTRA
      OUTPUT_ADDR_CONST_EXTRA (file, x, fail);
      break;

    fail:
#endif
      output_operand_lossage ("invalid expression as operand");
    }
}