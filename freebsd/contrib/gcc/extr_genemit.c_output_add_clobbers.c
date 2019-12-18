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
struct clobber_pat {int first_clobber; int /*<<< orphan*/  pattern; struct clobber_ent* insns; struct clobber_pat* next; } ;
struct clobber_ent {int code_number; struct clobber_ent* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 struct clobber_pat* clobber_list ; 
 int /*<<< orphan*/  gen_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
output_add_clobbers (void)
{
  struct clobber_pat *clobber;
  struct clobber_ent *ent;
  int i;

  printf ("\n\nvoid\nadd_clobbers (rtx pattern ATTRIBUTE_UNUSED, int insn_code_number)\n");
  printf ("{\n");
  printf ("  switch (insn_code_number)\n");
  printf ("    {\n");

  for (clobber = clobber_list; clobber; clobber = clobber->next)
    {
      for (ent = clobber->insns; ent; ent = ent->next)
	printf ("    case %d:\n", ent->code_number);

      for (i = clobber->first_clobber; i < XVECLEN (clobber->pattern, 1); i++)
	{
	  printf ("      XVECEXP (pattern, 0, %d) = ", i);
	  gen_exp (XVECEXP (clobber->pattern, 1, i),
		   GET_CODE (clobber->pattern), NULL);
	  printf (";\n");
	}

      printf ("      break;\n\n");
    }

  printf ("    default:\n");
  printf ("      gcc_unreachable ();\n");
  printf ("    }\n");
  printf ("}\n");
}