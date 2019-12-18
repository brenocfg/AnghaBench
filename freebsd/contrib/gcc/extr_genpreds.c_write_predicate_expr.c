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
#define  AND 134 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 133 
#define  IOR 132 
#define  MATCH_CODE 131 
#define  MATCH_OPERAND 130 
#define  MATCH_TEST 129 
#define  NOT 128 
 size_t VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char** mode_name ; 
 int /*<<< orphan*/  print_c_condition (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_match_code (char*,char*) ; 

__attribute__((used)) static void
write_predicate_expr (rtx exp)
{
  switch (GET_CODE (exp))
    {
    case AND:
      putchar ('(');
      write_predicate_expr (XEXP (exp, 0));
      fputs (") && (", stdout);
      write_predicate_expr (XEXP (exp, 1));
      putchar (')');
      break;
  
    case IOR:
      putchar ('(');
      write_predicate_expr (XEXP (exp, 0));
      fputs (") || (", stdout);
      write_predicate_expr (XEXP (exp, 1));
      putchar (')');
      break;

    case NOT:
      fputs ("!(", stdout);
      write_predicate_expr (XEXP (exp, 0));
      putchar (')');
      break;

    case IF_THEN_ELSE:
      putchar ('(');
      write_predicate_expr (XEXP (exp, 0));
      fputs (") ? (", stdout);
      write_predicate_expr (XEXP (exp, 1));
      fputs (") : (", stdout);
      write_predicate_expr (XEXP (exp, 2));
      putchar (')');
      break;

    case MATCH_OPERAND:
      if (GET_MODE (exp) == VOIDmode)
        printf ("%s (op, mode)", XSTR (exp, 1));
      else
        printf ("%s (op, %smode)", XSTR (exp, 1), mode_name[GET_MODE (exp)]);
      break;

    case MATCH_CODE:
      write_match_code (XSTR (exp, 1), XSTR (exp, 0));
      break;

    case MATCH_TEST:
      print_c_condition (XSTR (exp, 0));
      break;

    default:
      gcc_unreachable ();
    }
}