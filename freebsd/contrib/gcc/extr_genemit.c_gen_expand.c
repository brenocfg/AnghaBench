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

/* Variables and functions */
 scalar_t__ CALL ; 
 int /*<<< orphan*/  DEFINE_EXPAND ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MATCH_DUP ; 
 scalar_t__ MATCH_OPERAND ; 
 scalar_t__ MATCH_OPERATOR ; 
 scalar_t__ MATCH_OP_DUP ; 
 scalar_t__ MATCH_PARALLEL ; 
 scalar_t__ MATCH_PAR_DUP ; 
 int MAX (int,int) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PC ; 
 scalar_t__ RETURN ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  gen_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max_dup_opno ; 
 int max_operand_vec (int /*<<< orphan*/ ,int) ; 
 int max_scratch_opno ; 
 int /*<<< orphan*/  print_rtx_ptr_loc (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
gen_expand (rtx expand)
{
  int operands;
  int i;

  if (strlen (XSTR (expand, 0)) == 0)
    fatal ("define_expand lacks a name");
  if (XVEC (expand, 1) == 0)
    fatal ("define_expand for %s lacks a pattern", XSTR (expand, 0));

  /* Find out how many operands this function has.  */
  operands = max_operand_vec (expand, 1);

  /* Output the function name and argument declarations.  */
  printf ("rtx\ngen_%s (", XSTR (expand, 0));
  if (operands)
    for (i = 0; i < operands; i++)
      if (i)
	printf (",\n\trtx operand%d", i);
      else
	printf ("rtx operand%d", i);
  else
    printf ("void");
  printf (")\n");
  printf ("{\n");

  /* If we don't have any C code to write, only one insn is being written,
     and no MATCH_DUPs are present, we can just return the desired insn
     like we do for a DEFINE_INSN.  This saves memory.  */
  if ((XSTR (expand, 3) == 0 || *XSTR (expand, 3) == '\0')
      && operands > max_dup_opno
      && XVECLEN (expand, 1) == 1)
    {
      printf ("  return ");
      gen_exp (XVECEXP (expand, 1, 0), DEFINE_EXPAND, NULL);
      printf (";\n}\n\n");
      return;
    }

  /* For each operand referred to only with MATCH_DUPs,
     make a local variable.  */
  for (i = operands; i <= max_dup_opno; i++)
    printf ("  rtx operand%d;\n", i);
  for (; i <= max_scratch_opno; i++)
    printf ("  rtx operand%d ATTRIBUTE_UNUSED;\n", i);
  printf ("  rtx _val = 0;\n");
  printf ("  start_sequence ();\n");

  /* The fourth operand of DEFINE_EXPAND is some code to be executed
     before the actual construction.
     This code expects to refer to `operands'
     just as the output-code in a DEFINE_INSN does,
     but here `operands' is an automatic array.
     So copy the operand values there before executing it.  */
  if (XSTR (expand, 3) && *XSTR (expand, 3))
    {
      printf ("  {\n");
      if (operands > 0 || max_dup_opno >= 0 || max_scratch_opno >= 0)
	printf ("    rtx operands[%d];\n",
	    MAX (operands, MAX (max_scratch_opno, max_dup_opno) + 1));
      /* Output code to copy the arguments into `operands'.  */
      for (i = 0; i < operands; i++)
	printf ("    operands[%d] = operand%d;\n", i, i);

      /* Output the special code to be executed before the sequence
	 is generated.  */
      print_rtx_ptr_loc (XSTR (expand, 3));
      printf ("%s\n", XSTR (expand, 3));

      /* Output code to copy the arguments back out of `operands'
	 (unless we aren't going to use them at all).  */
      if (XVEC (expand, 1) != 0)
	{
	  for (i = 0; i < operands; i++)
	    printf ("    operand%d = operands[%d];\n", i, i);
	  for (; i <= max_dup_opno; i++)
	    printf ("    operand%d = operands[%d];\n", i, i);
	  for (; i <= max_scratch_opno; i++)
	    printf ("    operand%d = operands[%d];\n", i, i);
	}
      printf ("  }\n");
    }

  /* Output code to construct the rtl for the instruction bodies.
     Use emit_insn to add them to the sequence being accumulated.
     But don't do this if the user's code has set `no_more' nonzero.  */

  for (i = 0; i < XVECLEN (expand, 1); i++)
    {
      rtx next = XVECEXP (expand, 1, i);
      if ((GET_CODE (next) == SET && GET_CODE (SET_DEST (next)) == PC)
	  || (GET_CODE (next) == PARALLEL
	      && ((GET_CODE (XVECEXP (next, 0, 0)) == SET
		   && GET_CODE (SET_DEST (XVECEXP (next, 0, 0))) == PC)
		  || GET_CODE (XVECEXP (next, 0, 0)) == RETURN))
	  || GET_CODE (next) == RETURN)
	printf ("  emit_jump_insn (");
      else if ((GET_CODE (next) == SET && GET_CODE (SET_SRC (next)) == CALL)
	       || GET_CODE (next) == CALL
	       || (GET_CODE (next) == PARALLEL
		   && GET_CODE (XVECEXP (next, 0, 0)) == SET
		   && GET_CODE (SET_SRC (XVECEXP (next, 0, 0))) == CALL)
	       || (GET_CODE (next) == PARALLEL
		   && GET_CODE (XVECEXP (next, 0, 0)) == CALL))
	printf ("  emit_call_insn (");
      else if (LABEL_P (next))
	printf ("  emit_label (");
      else if (GET_CODE (next) == MATCH_OPERAND
	       || GET_CODE (next) == MATCH_DUP
	       || GET_CODE (next) == MATCH_OPERATOR
	       || GET_CODE (next) == MATCH_OP_DUP
	       || GET_CODE (next) == MATCH_PARALLEL
	       || GET_CODE (next) == MATCH_PAR_DUP
	       || GET_CODE (next) == PARALLEL)
	printf ("  emit (");
      else
	printf ("  emit_insn (");
      gen_exp (next, DEFINE_EXPAND, NULL);
      printf (");\n");
      if (GET_CODE (next) == SET && GET_CODE (SET_DEST (next)) == PC
	  && GET_CODE (SET_SRC (next)) == LABEL_REF)
	printf ("  emit_barrier ();");
    }

  /* Call `get_insns' to extract the list of all the
     insns emitted within this gen_... function.  */

  printf ("  _val = get_insns ();\n");
  printf ("  end_sequence ();\n");
  printf ("  return _val;\n}\n\n");
}