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
typedef  scalar_t__ rtx ;

/* Variables and functions */
#define  AND 134 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_NAME (int) ; 
#define  IF_THEN_ELSE 133 
#define  IOR 132 
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 int /*<<< orphan*/  ISLOWER (char const) ; 
#define  MATCH_CODE 131 
#define  MATCH_OPERAND 130 
#define  MATCH_TEST 129 
#define  NOT 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 char* XSTR (scalar_t__,int) ; 
 int have_error ; 
 int /*<<< orphan*/  message_with_line (int,char*,char const*,...) ; 

__attribute__((used)) static bool
validate_exp (rtx exp, const char *name, int lineno)
{
  if (exp == 0)
    {
      message_with_line (lineno, "%s: must give a predicate expression", name);
      return true;
    }

  switch (GET_CODE (exp))
    {
      /* Ternary, binary, unary expressions: recurse into subexpressions.  */
    case IF_THEN_ELSE:
      if (validate_exp (XEXP (exp, 2), name, lineno))
	return true;
      /* else fall through */
    case AND:
    case IOR:
      if (validate_exp (XEXP (exp, 1), name, lineno))
	return true;
      /* else fall through */
    case NOT:
      return validate_exp (XEXP (exp, 0), name, lineno);

      /* MATCH_CODE might have a syntax error in its path expression.  */
    case MATCH_CODE:
      {
	const char *p;
	for (p = XSTR (exp, 1); *p; p++)
	  {
	    if (!ISDIGIT (*p) && !ISLOWER (*p))
	      {
		message_with_line (lineno, "%s: invalid character in path "
				   "string '%s'", name, XSTR (exp, 1));
		have_error = 1;
		return true;
	      }
	  }
      }
      /* fall through */

      /* These need no special checking.  */
    case MATCH_OPERAND:
    case MATCH_TEST:
      return false;

    default:
      message_with_line (lineno,
			 "%s: cannot use '%s' in a predicate expression",
			 name, GET_RTX_NAME (GET_CODE (exp)));
      have_error = 1;
      return true;
    }
}