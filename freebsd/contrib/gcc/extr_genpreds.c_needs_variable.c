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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 133 
#define  IOR 132 
 int /*<<< orphan*/  ISALNUM (char const) ; 
#define  MATCH_CODE 131 
#define  MATCH_OPERAND 130 
#define  MATCH_TEST 129 
#define  NOT 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static bool
needs_variable (rtx exp, const char *var)
{
  switch (GET_CODE (exp))
    {
      /* Ternary, binary, unary expressions need a variable if
	 any of their subexpressions do.  */
    case IF_THEN_ELSE:
      if (needs_variable (XEXP (exp, 2), var))
	return true;
      /* else fall through */
    case AND:
    case IOR:
      if (needs_variable (XEXP (exp, 1), var))
	return true;
      /* else fall through */
    case NOT:
      return needs_variable (XEXP (exp, 0), var);

      /* MATCH_CODE uses "op", but nothing else.  */
    case MATCH_CODE:
      return !strcmp (var, "op");

      /* MATCH_OPERAND uses "op" and may use "mode".  */
    case MATCH_OPERAND:
      if (!strcmp (var, "op"))
	return true;
      if (!strcmp (var, "mode") && GET_MODE (exp) == VOIDmode)
	return true;
      return false;

      /* MATCH_TEST uses var if XSTR (exp, 0) =~ /\b${var}\b/o; */
    case MATCH_TEST:
      {
	const char *p = XSTR (exp, 0);
	const char *q = strstr (p, var);
	if (!q)
	  return false;
	if (q != p && (ISALNUM (q[-1]) || q[-1] == '_'))
	  return false;
	q += strlen (var);
	if (ISALNUM (q[0] || q[0] == '_'))
	  return false;
      }
      return true;

    default:
      gcc_unreachable ();
    }
}