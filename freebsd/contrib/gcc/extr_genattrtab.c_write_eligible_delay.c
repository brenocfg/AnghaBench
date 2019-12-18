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
struct delay_desc {int num; int /*<<< orphan*/  def; struct delay_desc* next; } ;
struct attr_value {struct attr_value* next; } ;
struct attr_desc {struct attr_value* first_value; } ;

/* Variables and functions */
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 char const* delay_1_0_str ; 
 char const* delay_type_str ; 
 struct delay_desc* delays ; 
 struct attr_desc* find_attr (char const**,int /*<<< orphan*/ ) ; 
 struct attr_value* find_most_used (struct attr_desc*) ; 
 int /*<<< orphan*/  gcc_assert (struct attr_desc*) ; 
 int num_delays ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  true_rtx ; 
 int /*<<< orphan*/  write_attr_case (struct attr_desc*,struct attr_value*,int,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_eligible_delay (const char *kind)
{
  struct delay_desc *delay;
  int max_slots;
  char str[50];
  const char *pstr;
  struct attr_desc *attr;
  struct attr_value *av, *common_av;
  int i;

  /* Compute the maximum number of delay slots required.  We use the delay
     ordinal times this number plus one, plus the slot number as an index into
     the appropriate predicate to test.  */

  for (delay = delays, max_slots = 0; delay; delay = delay->next)
    if (XVECLEN (delay->def, 1) / 3 > max_slots)
      max_slots = XVECLEN (delay->def, 1) / 3;

  /* Write function prelude.  */

  printf ("int\n");
  printf ("eligible_for_%s (rtx delay_insn ATTRIBUTE_UNUSED, int slot, rtx candidate_insn, int flags ATTRIBUTE_UNUSED)\n",
	  kind);
  printf ("{\n");
  printf ("  rtx insn;\n");
  printf ("\n");
  printf ("  gcc_assert (slot < %d);\n", max_slots);
  printf ("\n");
  /* Allow dbr_schedule to pass labels, etc.  This can happen if try_split
     converts a compound instruction into a loop.  */
  printf ("  if (!INSN_P (candidate_insn))\n");
  printf ("    return 0;\n");
  printf ("\n");

  /* If more than one delay type, find out which type the delay insn is.  */

  if (num_delays > 1)
    {
      attr = find_attr (&delay_type_str, 0);
      gcc_assert (attr);
      common_av = find_most_used (attr);

      printf ("  insn = delay_insn;\n");
      printf ("  switch (recog_memoized (insn))\n");
      printf ("    {\n");

      sprintf (str, " * %d;\n      break;", max_slots);
      for (av = attr->first_value; av; av = av->next)
	if (av != common_av)
	  write_attr_case (attr, av, 1, "slot +=", str, 4, true_rtx);

      write_attr_case (attr, common_av, 0, "slot +=", str, 4, true_rtx);
      printf ("    }\n\n");

      /* Ensure matched.  Otherwise, shouldn't have been called.  */
      printf ("  gcc_assert (slot >= %d);\n\n", max_slots);
    }

  /* If just one type of delay slot, write simple switch.  */
  if (num_delays == 1 && max_slots == 1)
    {
      printf ("  insn = candidate_insn;\n");
      printf ("  switch (recog_memoized (insn))\n");
      printf ("    {\n");

      attr = find_attr (&delay_1_0_str, 0);
      gcc_assert (attr);
      common_av = find_most_used (attr);

      for (av = attr->first_value; av; av = av->next)
	if (av != common_av)
	  write_attr_case (attr, av, 1, "return", ";", 4, true_rtx);

      write_attr_case (attr, common_av, 0, "return", ";", 4, true_rtx);
      printf ("    }\n");
    }

  else
    {
      /* Write a nested CASE.  The first indicates which condition we need to
	 test, and the inner CASE tests the condition.  */
      printf ("  insn = candidate_insn;\n");
      printf ("  switch (slot)\n");
      printf ("    {\n");

      for (delay = delays; delay; delay = delay->next)
	for (i = 0; i < XVECLEN (delay->def, 1); i += 3)
	  {
	    printf ("    case %d:\n",
		    (i / 3) + (num_delays == 1 ? 0 : delay->num * max_slots));
	    printf ("      switch (recog_memoized (insn))\n");
	    printf ("\t{\n");

	    sprintf (str, "*%s_%d_%d", kind, delay->num, i / 3);
	    pstr = str;
	    attr = find_attr (&pstr, 0);
	    gcc_assert (attr);
	    common_av = find_most_used (attr);

	    for (av = attr->first_value; av; av = av->next)
	      if (av != common_av)
		write_attr_case (attr, av, 1, "return", ";", 8, true_rtx);

	    write_attr_case (attr, common_av, 0, "return", ";", 8, true_rtx);
	    printf ("      }\n");
	  }

      printf ("    default:\n");
      printf ("      gcc_unreachable ();\n");
      printf ("    }\n");
    }

  printf ("}\n\n");
}