#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct attr_value {int num_insns; int /*<<< orphan*/  value; TYPE_2__* first_insn; scalar_t__ has_asm_insn; } ;
struct attr_desc {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* def; } ;
struct TYPE_3__ {int insn_code; int /*<<< orphan*/  insn_index; } ;

/* Variables and functions */
 scalar_t__ address_used ; 
 scalar_t__ must_constrain ; 
 scalar_t__ must_extract ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  walk_attr_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_attr_set (struct attr_desc*,int,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_indent (int) ; 
 int /*<<< orphan*/  write_insn_cases (TYPE_2__*,int) ; 

__attribute__((used)) static void
write_attr_case (struct attr_desc *attr, struct attr_value *av,
		 int write_case_lines, const char *prefix, const char *suffix,
		 int indent, rtx known_true)
{
  if (av->num_insns == 0)
    return;

  if (av->has_asm_insn)
    {
      write_indent (indent);
      printf ("case -1:\n");
      write_indent (indent + 2);
      printf ("if (GET_CODE (PATTERN (insn)) != ASM_INPUT\n");
      write_indent (indent + 2);
      printf ("    && asm_noperands (PATTERN (insn)) < 0)\n");
      write_indent (indent + 2);
      printf ("  fatal_insn_not_found (insn);\n");
    }

  if (write_case_lines)
    write_insn_cases (av->first_insn, indent);
  else
    {
      write_indent (indent);
      printf ("default:\n");
    }

  /* See what we have to do to output this value.  */
  must_extract = must_constrain = address_used = 0;
  walk_attr_value (av->value);

  if (must_constrain)
    {
      write_indent (indent + 2);
      printf ("extract_constrain_insn_cached (insn);\n");
    }
  else if (must_extract)
    {
      write_indent (indent + 2);
      printf ("extract_insn_cached (insn);\n");
    }

  if (av->num_insns == 1)
    write_attr_set (attr, indent + 2, av->value, prefix, suffix,
		    known_true, av->first_insn->def->insn_code,
		    av->first_insn->def->insn_index);
  else
    write_attr_set (attr, indent + 2, av->value, prefix, suffix,
		    known_true, -2, 0);

  if (strncmp (prefix, "return", 6))
    {
      write_indent (indent + 2);
      printf ("break;\n");
    }
  printf ("\n");
}