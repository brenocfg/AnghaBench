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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  int RTX_CODE ;

/* Variables and functions */
#define  ADDRESS 140 
#define  CC0 139 
#define  CLOBBER 138 
#define  CONST_DOUBLE 137 
#define  CONST_INT 136 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 char* GET_MODE_NAME (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 char* HOST_WIDE_INT_PRINT_DEC_C ; 
 int INTVAL (scalar_t__) ; 
#define  MATCH_DUP 135 
#define  MATCH_OPERAND 134 
#define  MATCH_OPERATOR 133 
#define  MATCH_OP_DUP 132 
#define  MATCH_PARALLEL 131 
#define  MATCH_PAR_DUP 130 
#define  MATCH_SCRATCH 129 
 int MAX_SAVED_CONST_INT ; 
#define  PC 128 
 int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 int STORE_FLAG_VALUE ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XINT (scalar_t__,int) ; 
 char* XSTR (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtx_scratch (scalar_t__,int) ; 
 int /*<<< orphan*/  print_code (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
gen_exp (rtx x, enum rtx_code subroutine_type, char *used)
{
  RTX_CODE code;
  int i;
  int len;
  const char *fmt;

  if (x == 0)
    {
      printf ("NULL_RTX");
      return;
    }

  code = GET_CODE (x);

  switch (code)
    {
    case MATCH_OPERAND:
    case MATCH_DUP:
      if (used)
	{
	  if (used[XINT (x, 0)])
	    {
	      printf ("copy_rtx (operand%d)", XINT (x, 0));
	      return;
	    }
	  used[XINT (x, 0)] = 1;
	}
      printf ("operand%d", XINT (x, 0));
      return;

    case MATCH_OP_DUP:
      printf ("gen_rtx_fmt_");
      for (i = 0; i < XVECLEN (x, 1); i++)
	printf ("e");
      printf (" (GET_CODE (operand%d), ", XINT (x, 0));
      if (GET_MODE (x) == VOIDmode)
	printf ("GET_MODE (operand%d)", XINT (x, 0));
      else
	printf ("%smode", GET_MODE_NAME (GET_MODE (x)));
      for (i = 0; i < XVECLEN (x, 1); i++)
	{
	  printf (",\n\t\t");
	  gen_exp (XVECEXP (x, 1, i), subroutine_type, used);
	}
      printf (")");
      return;

    case MATCH_OPERATOR:
      printf ("gen_rtx_fmt_");
      for (i = 0; i < XVECLEN (x, 2); i++)
	printf ("e");
      printf (" (GET_CODE (operand%d)", XINT (x, 0));
      printf (", %smode", GET_MODE_NAME (GET_MODE (x)));
      for (i = 0; i < XVECLEN (x, 2); i++)
	{
	  printf (",\n\t\t");
	  gen_exp (XVECEXP (x, 2, i), subroutine_type, used);
	}
      printf (")");
      return;

    case MATCH_PARALLEL:
    case MATCH_PAR_DUP:
      printf ("operand%d", XINT (x, 0));
      return;

    case MATCH_SCRATCH:
      gen_rtx_scratch (x, subroutine_type);
      return;

    case ADDRESS:
      fatal ("ADDRESS expression code used in named instruction pattern");

    case PC:
      printf ("pc_rtx");
      return;
    case CLOBBER:
      if (REG_P (XEXP (x, 0)))
	{
	  printf ("gen_hard_reg_clobber (%smode, %i)", GET_MODE_NAME (GET_MODE (XEXP (x, 0))),
			  			     REGNO (XEXP (x, 0)));
	  return;
	}
      break;

    case CC0:
      printf ("cc0_rtx");
      return;

    case CONST_INT:
      if (INTVAL (x) == 0)
	printf ("const0_rtx");
      else if (INTVAL (x) == 1)
	printf ("const1_rtx");
      else if (INTVAL (x) == -1)
	printf ("constm1_rtx");
      else if (-MAX_SAVED_CONST_INT <= INTVAL (x)
	  && INTVAL (x) <= MAX_SAVED_CONST_INT)
	printf ("const_int_rtx[MAX_SAVED_CONST_INT + (%d)]",
		(int) INTVAL (x));
      else if (INTVAL (x) == STORE_FLAG_VALUE)
	printf ("const_true_rtx");
      else
	{
	  printf ("GEN_INT (");
	  printf (HOST_WIDE_INT_PRINT_DEC_C, INTVAL (x));
	  printf (")");
	}
      return;

    case CONST_DOUBLE:
      /* These shouldn't be written in MD files.  Instead, the appropriate
	 routines in varasm.c should be called.  */
      gcc_unreachable ();

    default:
      break;
    }

  printf ("gen_rtx_");
  print_code (code);
  printf (" (%smode", GET_MODE_NAME (GET_MODE (x)));

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      if (fmt[i] == '0')
	break;
      printf (",\n\t");
      switch (fmt[i])
	{
	case 'e': case 'u':
	  gen_exp (XEXP (x, i), subroutine_type, used);
	  break;

	case 'i':
	  printf ("%u", XINT (x, i));
	  break;

	case 's':
	  printf ("\"%s\"", XSTR (x, i));
	  break;

	case 'E':
	  {
	    int j;
	    printf ("gen_rtvec (%d", XVECLEN (x, i));
	    for (j = 0; j < XVECLEN (x, i); j++)
	      {
		printf (",\n\t\t");
		gen_exp (XVECEXP (x, i, j), subroutine_type, used);
	      }
	    printf (")");
	    break;
	  }

	default:
	  gcc_unreachable ();
	}
    }
  printf (")");
}