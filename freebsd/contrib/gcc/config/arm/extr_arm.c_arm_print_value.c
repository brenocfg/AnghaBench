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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CONST 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_STRING 133 
#define  CONST_VECTOR 132 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_HEX ; 
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 131 
#define  PC 130 
#define  PLUS 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XWINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arm_print_value (FILE *f, rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST_INT:
      fprintf (f, HOST_WIDE_INT_PRINT_HEX, INTVAL (x));
      return;

    case CONST_DOUBLE:
      fprintf (f, "<0x%lx,0x%lx>", (long)XWINT (x, 2), (long)XWINT (x, 3));
      return;

    case CONST_VECTOR:
      {
	int i;

	fprintf (f, "<");
	for (i = 0; i < CONST_VECTOR_NUNITS (x); i++)
	  {
	    fprintf (f, HOST_WIDE_INT_PRINT_HEX, INTVAL (CONST_VECTOR_ELT (x, i)));
	    if (i < (CONST_VECTOR_NUNITS (x) - 1))
	      fputc (',', f);
	  }
	fprintf (f, ">");
      }
      return;

    case CONST_STRING:
      fprintf (f, "\"%s\"", XSTR (x, 0));
      return;

    case SYMBOL_REF:
      fprintf (f, "`%s'", XSTR (x, 0));
      return;

    case LABEL_REF:
      fprintf (f, "L%d", INSN_UID (XEXP (x, 0)));
      return;

    case CONST:
      arm_print_value (f, XEXP (x, 0));
      return;

    case PLUS:
      arm_print_value (f, XEXP (x, 0));
      fprintf (f, "+");
      arm_print_value (f, XEXP (x, 1));
      return;

    case PC:
      fprintf (f, "pc");
      return;

    default:
      fprintf (f, "????");
      return;
    }
}