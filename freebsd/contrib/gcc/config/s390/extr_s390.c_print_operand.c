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
struct s390_address {int /*<<< orphan*/  base; int /*<<< orphan*/  disp; int /*<<< orphan*/  indx; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CODE_LABEL 135 
#define  CONST 134 
#define  CONST_DOUBLE 133 
 int CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 132 
 int /*<<< orphan*/  FALSE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HImode ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 131 
#define  MEM 130 
#define  REG 129 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_BASE_P (size_t) ; 
 int /*<<< orphan*/  SImode ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  TRUE ; 
 int UNSPEC ; 
 int /*<<< orphan*/  UNSPEC_TLSGD ; 
 int /*<<< orphan*/  UNSPEC_TLSLDM ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_some_local_dynamic_name () ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_shift_count_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** reg_names ; 
 char* s390_branch_condition_mnemonic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s390_decompose_address (int /*<<< orphan*/ ,struct s390_address*) ; 
 int s390_extract_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
print_operand (FILE *file, rtx x, int code)
{
  switch (code)
    {
    case 'C':
      fprintf (file, s390_branch_condition_mnemonic (x, FALSE));
      return;

    case 'D':
      fprintf (file, s390_branch_condition_mnemonic (x, TRUE));
      return;

    case 'J':
      if (GET_CODE (x) == SYMBOL_REF)
	{
	  fprintf (file, "%s", ":tls_load:");
	  output_addr_const (file, x);
	}
      else if (GET_CODE (x) == UNSPEC && XINT (x, 1) == UNSPEC_TLSGD)
	{
	  fprintf (file, "%s", ":tls_gdcall:");
	  output_addr_const (file, XVECEXP (x, 0, 0));
	}
      else if (GET_CODE (x) == UNSPEC && XINT (x, 1) == UNSPEC_TLSLDM)
	{
	  fprintf (file, "%s", ":tls_ldcall:");
	  assemble_name (file, get_some_local_dynamic_name ());
	}
      else
	gcc_unreachable ();
      return;

    case 'G':
      fprintf (file, "%u", GET_MODE_SIZE (GET_MODE (x)));
      return;

    case 'O':
      {
        struct s390_address ad;
	int ret;

        gcc_assert (GET_CODE (x) == MEM);
	ret = s390_decompose_address (XEXP (x, 0), &ad);
	gcc_assert (ret);
	gcc_assert (!ad.base || REGNO_OK_FOR_BASE_P (REGNO (ad.base)));
	gcc_assert (!ad.indx);

        if (ad.disp)
          output_addr_const (file, ad.disp);
        else
          fprintf (file, "0");
      }
      return;

    case 'R':
      {
        struct s390_address ad;
	int ret;

        gcc_assert (GET_CODE (x) == MEM);
	ret = s390_decompose_address (XEXP (x, 0), &ad);
	gcc_assert (ret);
	gcc_assert (!ad.base || REGNO_OK_FOR_BASE_P (REGNO (ad.base)));
	gcc_assert (!ad.indx);

        if (ad.base)
          fprintf (file, "%s", reg_names[REGNO (ad.base)]);
        else
          fprintf (file, "0");
      }
      return;

    case 'S':
      {
	struct s390_address ad;
	int ret;

        gcc_assert (GET_CODE (x) == MEM);
	ret = s390_decompose_address (XEXP (x, 0), &ad);
	gcc_assert (ret);
	gcc_assert (!ad.base || REGNO_OK_FOR_BASE_P (REGNO (ad.base)));
	gcc_assert (!ad.indx);

	if (ad.disp)
	  output_addr_const (file, ad.disp);
	else
	  fprintf (file, "0");

	if (ad.base)
	  fprintf (file, "(%s)", reg_names[REGNO (ad.base)]);
      }
      return;

    case 'N':
      if (GET_CODE (x) == REG)
	x = gen_rtx_REG (GET_MODE (x), REGNO (x) + 1);
      else if (GET_CODE (x) == MEM)
	x = change_address (x, VOIDmode, plus_constant (XEXP (x, 0), 4));
      else
        gcc_unreachable ();
      break;

    case 'M':
      if (GET_CODE (x) == REG)
	x = gen_rtx_REG (GET_MODE (x), REGNO (x) + 1);
      else if (GET_CODE (x) == MEM)
	x = change_address (x, VOIDmode, plus_constant (XEXP (x, 0), 8));
      else
        gcc_unreachable ();
      break;

    case 'Y':
      print_shift_count_operand (file, x);
      return;
    }

  switch (GET_CODE (x))
    {
    case REG:
      fprintf (file, "%s", reg_names[REGNO (x)]);
      break;

    case MEM:
      output_address (XEXP (x, 0));
      break;

    case CONST:
    case CODE_LABEL:
    case LABEL_REF:
    case SYMBOL_REF:
      output_addr_const (file, x);
      break;

    case CONST_INT:
      if (code == 'b')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x) & 0xff);
      else if (code == 'x')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x) & 0xffff);
      else if (code == 'h')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, ((INTVAL (x) & 0xffff) ^ 0x8000) - 0x8000);
      else if (code == 'i')
	fprintf (file, HOST_WIDE_INT_PRINT_DEC,
		 s390_extract_part (x, HImode, 0));
      else if (code == 'j')
	fprintf (file, HOST_WIDE_INT_PRINT_DEC,
		 s390_extract_part (x, HImode, -1));
      else if (code == 'k')
 	fprintf (file, HOST_WIDE_INT_PRINT_DEC,
 		 s390_extract_part (x, SImode, 0));
      else if (code == 'm')
 	fprintf (file, HOST_WIDE_INT_PRINT_DEC,
 		 s390_extract_part (x, SImode, -1));
      else if (code == 'o')
	fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x) & 0xffffffff);
      else
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
      break;

    case CONST_DOUBLE:
      gcc_assert (GET_MODE (x) == VOIDmode);
      if (code == 'b')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, CONST_DOUBLE_LOW (x) & 0xff);
      else if (code == 'x')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, CONST_DOUBLE_LOW (x) & 0xffff);
      else if (code == 'h')
        fprintf (file, HOST_WIDE_INT_PRINT_DEC, ((CONST_DOUBLE_LOW (x) & 0xffff) ^ 0x8000) - 0x8000);
      else
        gcc_unreachable ();
      break;

    default:
      fatal_insn ("UNKNOWN in print_operand !?", x);
      break;
    }
}