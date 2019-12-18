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
struct attr_value {int /*<<< orphan*/  first_insn; int /*<<< orphan*/  value; struct attr_value* next; } ;
struct attr_desc {struct attr_value* first_value; } ;

/* Variables and functions */
 struct attr_desc* find_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ length_used ; 
 int /*<<< orphan*/  num_delay_slots_str ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  walk_attr_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_insn_cases (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
write_const_num_delay_slots (void)
{
  struct attr_desc *attr = find_attr (&num_delay_slots_str, 0);
  struct attr_value *av;

  if (attr)
    {
      printf ("int\nconst_num_delay_slots (rtx insn)\n");
      printf ("{\n");
      printf ("  switch (recog_memoized (insn))\n");
      printf ("    {\n");

      for (av = attr->first_value; av; av = av->next)
	{
	  length_used = 0;
	  walk_attr_value (av->value);
	  if (length_used)
	    write_insn_cases (av->first_insn, 4);
	}

      printf ("    default:\n");
      printf ("      return 1;\n");
      printf ("    }\n}\n\n");
    }
}