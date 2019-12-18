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
struct clobber_pat {int has_hard_reg; struct clobber_ent* insns; struct clobber_pat* next; } ;
struct clobber_ent {int code_number; struct clobber_ent* next; } ;

/* Variables and functions */
 struct clobber_pat* clobber_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
output_added_clobbers_hard_reg_p (void)
{
  struct clobber_pat *clobber;
  struct clobber_ent *ent;
  int clobber_p, used;

  printf ("\n\nint\nadded_clobbers_hard_reg_p (int insn_code_number)\n");
  printf ("{\n");
  printf ("  switch (insn_code_number)\n");
  printf ("    {\n");

  for (clobber_p = 0; clobber_p <= 1; clobber_p++)
    {
      used = 0;
      for (clobber = clobber_list; clobber; clobber = clobber->next)
	if (clobber->has_hard_reg == clobber_p)
	  for (ent = clobber->insns; ent; ent = ent->next)
	    {
	      printf ("    case %d:\n", ent->code_number);
	      used++;
	    }

      if (used)
	printf ("      return %d;\n\n", clobber_p);
    }

  printf ("    default:\n");
  printf ("      gcc_unreachable ();\n");
  printf ("    }\n");
  printf ("}\n");
}