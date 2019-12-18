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
 scalar_t__ IS_VSPACE (char const) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int max_id_len ; 
 int maybe_eval_c_test (char*) ; 
 int /*<<< orphan*/  obstack ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
gen_insn (rtx insn)
{
  const char *name = XSTR (insn, 0);
  const char *p;
  int len;
  int truth = maybe_eval_c_test (XSTR (insn, 2));

  /* Don't mention instructions whose names are the null string
     or begin with '*'.  They are in the machine description just
     to be recognized.  */
  if (name[0] == 0 || name[0] == '*')
    return;

  len = strlen (name);

  if (len > max_id_len)
    max_id_len = len;

  if (truth == 0)
    /* Emit nothing.  */;
  else if (truth == 1)
    printf ("#define HAVE_%s 1\n", name);
  else
    {
      /* Write the macro definition, putting \'s at the end of each line,
	 if more than one.  */
      printf ("#define HAVE_%s (", name);
      for (p = XSTR (insn, 2); *p; p++)
	{
	  if (IS_VSPACE (*p))
	    fputs (" \\\n", stdout);
	  else
	    putchar (*p);
	}
      fputs (")\n", stdout);
    }

  obstack_grow (&obstack, &insn, sizeof (rtx));
}