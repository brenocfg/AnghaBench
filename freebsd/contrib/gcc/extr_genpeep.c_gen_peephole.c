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
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int insn_code_number ; 
 int /*<<< orphan*/  match_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int n_operands ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
gen_peephole (rtx peep)
{
  int ninsns = XVECLEN (peep, 0);
  int i;

  n_operands = 0;

  printf ("  insn = ins1;\n");

  for (i = 0; i < ninsns; i++)
    {
      if (i > 0)
	{
	  printf ("  do { insn = NEXT_INSN (insn);\n");
	  printf ("       if (insn == 0) goto L%d; }\n",
		  insn_code_number);
	  printf ("  while (NOTE_P (insn)\n");
	  printf ("\t || (NONJUMP_INSN_P (insn)\n");
	  printf ("\t     && (GET_CODE (PATTERN (insn)) == USE\n");
	  printf ("\t\t || GET_CODE (PATTERN (insn)) == CLOBBER)));\n");

	  printf ("  if (LABEL_P (insn)\n\
      || BARRIER_P (insn))\n    goto L%d;\n",
		  insn_code_number);
	}

      printf ("  pat = PATTERN (insn);\n");

      /* Walk the insn's pattern, remembering at all times the path
	 down to the walking point.  */

      match_rtx (XVECEXP (peep, 0, i), NULL, insn_code_number);
    }

  /* We get this far if the pattern matches.
     Now test the extra condition.  */

  if (XSTR (peep, 1) && XSTR (peep, 1)[0])
    printf ("  if (! (%s)) goto L%d;\n",
	    XSTR (peep, 1), insn_code_number);

  /* If that matches, construct new pattern and put it in the first insn.
     This new pattern will never be matched.
     It exists only so that insn-extract can get the operands back.
     So use a simple regular form: a PARALLEL containing a vector
     of all the operands.  */

  printf ("  PATTERN (ins1) = gen_rtx_PARALLEL (VOIDmode, gen_rtvec_v (%d, operands));\n", n_operands);

  /* Record this define_peephole's insn code in the insn,
     as if it had been recognized to match this.  */
  printf ("  INSN_CODE (ins1) = %d;\n",
	  insn_code_number);

  /* Delete the remaining insns.  */
  if (ninsns > 1)
    printf ("  delete_for_peephole (NEXT_INSN (ins1), insn);\n");

  /* See reload1.c for insertion of NOTE which guarantees that this
     cannot be zero.  */
  printf ("  return NEXT_INSN (insn);\n");

  printf (" L%d:\n\n", insn_code_number);
}