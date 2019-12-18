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
#define  AND 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  IOR 130 
#define  MATCH_CODE 129 
#define  NOT 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_switch_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_match_code_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_predicate_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_predicate_stmts (rtx exp)
{
  switch (GET_CODE (exp))
    {
    case MATCH_CODE:
      if (generate_switch_p (exp))
	{
	  write_match_code_switch (exp);
	  puts ("      return true;\n"
		"    default:\n"
		"      break;\n"
		"    }\n"
		"  return false;");
	  return;
	}
      break;

    case AND:
      if (generate_switch_p (XEXP (exp, 0)))
	{
	  write_match_code_switch (XEXP (exp, 0));
	  puts ("      break;\n"
		"    default:\n"
		"      return false;\n"
		"    }");
	  exp = XEXP (exp, 1);
	}
      break;

    case IOR:
      if (generate_switch_p (XEXP (exp, 0)))
	{
	  write_match_code_switch (XEXP (exp, 0));
	  puts ("      return true;\n"
		"    default:\n"
		"      break;\n"
		"    }");
	  exp = XEXP (exp, 1);
	}
      break;

    case NOT:
      if (generate_switch_p (XEXP (exp, 0)))
	{
	  write_match_code_switch (XEXP (exp, 0));
	  puts ("      return false;\n"
		"    default:\n"
		"      break;\n"
		"    }\n"
		"  return true;");
	  return;
	}
      break;

    default:
      break;
    }

  fputs("  return ",stdout);
  write_predicate_expr (exp);
  fputs(";\n", stdout);
}