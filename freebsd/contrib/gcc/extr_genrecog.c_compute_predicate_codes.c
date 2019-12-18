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
struct pred_data {int /*<<< orphan*/ * codes; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  AND 134 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_NAME (int) ; 
 char I ; 
#define  IF_THEN_ELSE 133 
#define  IOR 132 
#define  MATCH_CODE 131 
#define  MATCH_OPERAND 130 
#define  MATCH_TEST 129 
 char N ; 
#define  NOT 128 
 int NUM_RTX_CODE ; 
 char TRISTATE_AND (char,char) ; 
 char TRISTATE_NOT (char) ; 
 char TRISTATE_OR (char,char) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 char Y ; 
 int* did_you_mean_codes ; 
 int /*<<< orphan*/  error_count ; 
 struct pred_data* lookup_predicate (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pattern_lineno ; 
 char* scan_comma_elt (char const**) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static void
compute_predicate_codes (rtx exp, char codes[NUM_RTX_CODE])
{
  char op0_codes[NUM_RTX_CODE];
  char op1_codes[NUM_RTX_CODE];
  char op2_codes[NUM_RTX_CODE];
  int i;

  switch (GET_CODE (exp))
    {
    case AND:
      compute_predicate_codes (XEXP (exp, 0), op0_codes);
      compute_predicate_codes (XEXP (exp, 1), op1_codes);
      for (i = 0; i < NUM_RTX_CODE; i++)
	codes[i] = TRISTATE_AND (op0_codes[i], op1_codes[i]);
      break;

    case IOR:
      compute_predicate_codes (XEXP (exp, 0), op0_codes);
      compute_predicate_codes (XEXP (exp, 1), op1_codes);
      for (i = 0; i < NUM_RTX_CODE; i++)
	codes[i] = TRISTATE_OR (op0_codes[i], op1_codes[i]);
      break;
    case NOT:
      compute_predicate_codes (XEXP (exp, 0), op0_codes);
      for (i = 0; i < NUM_RTX_CODE; i++)
	codes[i] = TRISTATE_NOT (op0_codes[i]);
      break;

    case IF_THEN_ELSE:
      /* a ? b : c  accepts the same codes as (a & b) | (!a & c).  */ 
      compute_predicate_codes (XEXP (exp, 0), op0_codes);
      compute_predicate_codes (XEXP (exp, 1), op1_codes);
      compute_predicate_codes (XEXP (exp, 2), op2_codes);
      for (i = 0; i < NUM_RTX_CODE; i++)
	codes[i] = TRISTATE_OR (TRISTATE_AND (op0_codes[i], op1_codes[i]),
				TRISTATE_AND (TRISTATE_NOT (op0_codes[i]),
					      op2_codes[i]));
      break;

    case MATCH_CODE:
      /* MATCH_CODE allows a specified list of codes.  However, if it
	 does not apply to the top level of the expression, it does not
	 constrain the set of codes for the top level.  */
      if (XSTR (exp, 1)[0] != '\0')
	{
	  memset (codes, Y, NUM_RTX_CODE);
	  break;
	}

      memset (codes, N, NUM_RTX_CODE);
      {
	const char *next_code = XSTR (exp, 0);
	const char *code;

	if (*next_code == '\0')
	  {
	    message_with_line (pattern_lineno, "empty match_code expression");
	    error_count++;
	    break;
	  }

	while ((code = scan_comma_elt (&next_code)) != 0)
	  {
	    size_t n = next_code - code;
	    int found_it = 0;
	    
	    for (i = 0; i < NUM_RTX_CODE; i++)
	      if (!strncmp (code, GET_RTX_NAME (i), n)
		  && GET_RTX_NAME (i)[n] == '\0')
		{
		  codes[i] = Y;
		  found_it = 1;
		  break;
		}
	    if (!found_it)
	      {
		message_with_line (pattern_lineno, "match_code \"%.*s\" matches nothing",
				   (int) n, code);
		error_count ++;
		for (i = 0; i < NUM_RTX_CODE; i++)
		  if (!strncasecmp (code, GET_RTX_NAME (i), n)
		      && GET_RTX_NAME (i)[n] == '\0'
		      && !did_you_mean_codes[i])
		    {
		      did_you_mean_codes[i] = 1;
		      message_with_line (pattern_lineno, "(did you mean \"%s\"?)", GET_RTX_NAME (i));
		    }
	      }

	  }
      }
      break;

    case MATCH_OPERAND:
      /* MATCH_OPERAND disallows the set of codes that the named predicate
	 disallows, and is indeterminate for the codes that it does allow.  */
      {
	struct pred_data *p = lookup_predicate (XSTR (exp, 1));
	if (!p)
	  {
	    message_with_line (pattern_lineno,
			       "reference to unknown predicate '%s'",
			       XSTR (exp, 1));
	    error_count++;
	    break;
	  }
	for (i = 0; i < NUM_RTX_CODE; i++)
	  codes[i] = p->codes[i] ? I : N;
      }
      break;


    case MATCH_TEST:
      /* (match_test WHATEVER) is completely indeterminate.  */
      memset (codes, I, NUM_RTX_CODE);
      break;

    default:
      message_with_line (pattern_lineno,
	 "'%s' cannot be used in a define_predicate expression",
	 GET_RTX_NAME (GET_CODE (exp)));
      error_count++;
      memset (codes, I, NUM_RTX_CODE);
      break;
    }
}