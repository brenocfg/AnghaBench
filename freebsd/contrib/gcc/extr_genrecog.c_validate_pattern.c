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
struct pred_data {int /*<<< orphan*/  allows_non_const; int /*<<< orphan*/  special; int /*<<< orphan*/  allows_non_lvalue; } ;
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int RTX_CODE ;

/* Variables and functions */
 int const CALL ; 
 int const CC0 ; 
#define  CLOBBER 138 
 int const CONST_INT ; 
 int const DEFINE_EXPAND ; 
 int const DEFINE_INSN ; 
 int const DEFINE_PEEPHOLE2 ; 
 int const DEFINE_SPLIT ; 
 int const GET_CODE (int /*<<< orphan*/ *) ; 
 int GET_MODE (int /*<<< orphan*/ *) ; 
 char const* GET_MODE_NAME (int) ; 
 char* GET_RTX_FORMAT (int) ; 
 size_t GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 137 
#define  MATCH_DUP 136 
#define  MATCH_OPERAND 135 
#define  MATCH_OPERATOR 134 
#define  MATCH_OP_DUP 133 
#define  MATCH_PAR_DUP 132 
#define  MATCH_SCRATCH 131 
 int /*<<< orphan*/ * NULL_RTX ; 
 int const PC ; 
#define  SET 130 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
#define  STRICT_LOW_PART 129 
 int VOIDmode ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,size_t) ; 
 char const* XINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XSTR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,size_t,int) ; 
 int XVECLEN (int /*<<< orphan*/ *,size_t) ; 
#define  ZERO_EXTRACT 128 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  find_matching_operand (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * find_operand (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 struct pred_data* lookup_predicate (char const*) ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  pattern_lineno ; 
 char const** rtx_name ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static void
validate_pattern (rtx pattern, rtx insn, rtx set, int set_code)
{
  const char *fmt;
  RTX_CODE code;
  size_t i, len;
  int j;

  code = GET_CODE (pattern);
  switch (code)
    {
    case MATCH_SCRATCH:
      return;
    case MATCH_DUP:
    case MATCH_OP_DUP:
    case MATCH_PAR_DUP:
      if (find_operand (insn, XINT (pattern, 0), pattern) == pattern)
	{
	  message_with_line (pattern_lineno,
			     "operand %i duplicated before defined",
			     XINT (pattern, 0));
          error_count++;
	}
      break;
    case MATCH_OPERAND:
    case MATCH_OPERATOR:
      {
	const char *pred_name = XSTR (pattern, 1);
	const struct pred_data *pred;
	const char *c_test;

	if (GET_CODE (insn) == DEFINE_INSN)
	  c_test = XSTR (insn, 2);
	else
	  c_test = XSTR (insn, 1);

	if (pred_name[0] != 0)
	  {
	    pred = lookup_predicate (pred_name);
	    if (!pred)
	      message_with_line (pattern_lineno,
				 "warning: unknown predicate '%s'",
				 pred_name);
	  }
	else
	  pred = 0;

	if (code == MATCH_OPERAND)
	  {
	    const char constraints0 = XSTR (pattern, 2)[0];

	    /* In DEFINE_EXPAND, DEFINE_SPLIT, and DEFINE_PEEPHOLE2, we
	       don't use the MATCH_OPERAND constraint, only the predicate.
	       This is confusing to folks doing new ports, so help them
	       not make the mistake.  */
	    if (GET_CODE (insn) == DEFINE_EXPAND
		|| GET_CODE (insn) == DEFINE_SPLIT
		|| GET_CODE (insn) == DEFINE_PEEPHOLE2)
	      {
		if (constraints0)
		  message_with_line (pattern_lineno,
				     "warning: constraints not supported in %s",
				     rtx_name[GET_CODE (insn)]);
	      }

	    /* A MATCH_OPERAND that is a SET should have an output reload.  */
	    else if (set && constraints0)
	      {
		if (set_code == '+')
		  {
		    if (constraints0 == '+')
		      ;
		    /* If we've only got an output reload for this operand,
		       we'd better have a matching input operand.  */
		    else if (constraints0 == '='
			     && find_matching_operand (insn, XINT (pattern, 0)))
		      ;
		    else
		      {
			message_with_line (pattern_lineno,
					   "operand %d missing in-out reload",
					   XINT (pattern, 0));
			error_count++;
		      }
		  }
		else if (constraints0 != '=' && constraints0 != '+')
		  {
		    message_with_line (pattern_lineno,
				       "operand %d missing output reload",
				       XINT (pattern, 0));
		    error_count++;
		  }
	      }
	  }

	/* Allowing non-lvalues in destinations -- particularly CONST_INT --
	   while not likely to occur at runtime, results in less efficient
	   code from insn-recog.c.  */
	if (set && pred && pred->allows_non_lvalue)
	  message_with_line (pattern_lineno,
			     "warning: destination operand %d "
			     "allows non-lvalue",
			     XINT (pattern, 0));

	/* A modeless MATCH_OPERAND can be handy when we can check for
	   multiple modes in the c_test.  In most other cases, it is a
	   mistake.  Only DEFINE_INSN is eligible, since SPLIT and
	   PEEP2 can FAIL within the output pattern.  Exclude special
	   predicates, which check the mode themselves.  Also exclude
	   predicates that allow only constants.  Exclude the SET_DEST
	   of a call instruction, as that is a common idiom.  */

	if (GET_MODE (pattern) == VOIDmode
	    && code == MATCH_OPERAND
	    && GET_CODE (insn) == DEFINE_INSN
	    && pred
	    && !pred->special
	    && pred->allows_non_const
	    && strstr (c_test, "operands") == NULL
	    && ! (set
		  && GET_CODE (set) == SET
		  && GET_CODE (SET_SRC (set)) == CALL))
	  message_with_line (pattern_lineno,
			     "warning: operand %d missing mode?",
			     XINT (pattern, 0));
	return;
      }

    case SET:
      {
	enum machine_mode dmode, smode;
	rtx dest, src;

	dest = SET_DEST (pattern);
	src = SET_SRC (pattern);

	/* STRICT_LOW_PART is a wrapper.  Its argument is the real
	   destination, and it's mode should match the source.  */
	if (GET_CODE (dest) == STRICT_LOW_PART)
	  dest = XEXP (dest, 0);

	/* Find the referent for a DUP.  */

	if (GET_CODE (dest) == MATCH_DUP
	    || GET_CODE (dest) == MATCH_OP_DUP
	    || GET_CODE (dest) == MATCH_PAR_DUP)
	  dest = find_operand (insn, XINT (dest, 0), NULL);

	if (GET_CODE (src) == MATCH_DUP
	    || GET_CODE (src) == MATCH_OP_DUP
	    || GET_CODE (src) == MATCH_PAR_DUP)
	  src = find_operand (insn, XINT (src, 0), NULL);

	dmode = GET_MODE (dest);
	smode = GET_MODE (src);

	/* The mode of an ADDRESS_OPERAND is the mode of the memory
	   reference, not the mode of the address.  */
	if (GET_CODE (src) == MATCH_OPERAND
	    && ! strcmp (XSTR (src, 1), "address_operand"))
	  ;

        /* The operands of a SET must have the same mode unless one
	   is VOIDmode.  */
        else if (dmode != VOIDmode && smode != VOIDmode && dmode != smode)
	  {
	    message_with_line (pattern_lineno,
			       "mode mismatch in set: %smode vs %smode",
			       GET_MODE_NAME (dmode), GET_MODE_NAME (smode));
	    error_count++;
	  }

	/* If only one of the operands is VOIDmode, and PC or CC0 is
	   not involved, it's probably a mistake.  */
	else if (dmode != smode
		 && GET_CODE (dest) != PC
		 && GET_CODE (dest) != CC0
		 && GET_CODE (src) != PC
		 && GET_CODE (src) != CC0
		 && GET_CODE (src) != CONST_INT)
	  {
	    const char *which;
	    which = (dmode == VOIDmode ? "destination" : "source");
	    message_with_line (pattern_lineno,
			       "warning: %s missing a mode?", which);
	  }

	if (dest != SET_DEST (pattern))
	  validate_pattern (dest, insn, pattern, '=');
	validate_pattern (SET_DEST (pattern), insn, pattern, '=');
        validate_pattern (SET_SRC (pattern), insn, NULL_RTX, 0);
        return;
      }

    case CLOBBER:
      validate_pattern (SET_DEST (pattern), insn, pattern, '=');
      return;

    case ZERO_EXTRACT:
      validate_pattern (XEXP (pattern, 0), insn, set, set ? '+' : 0);
      validate_pattern (XEXP (pattern, 1), insn, NULL_RTX, 0);
      validate_pattern (XEXP (pattern, 2), insn, NULL_RTX, 0);
      return;

    case STRICT_LOW_PART:
      validate_pattern (XEXP (pattern, 0), insn, set, set ? '+' : 0);
      return;

    case LABEL_REF:
      if (GET_MODE (XEXP (pattern, 0)) != VOIDmode)
	{
	  message_with_line (pattern_lineno,
			     "operand to label_ref %smode not VOIDmode",
			     GET_MODE_NAME (GET_MODE (XEXP (pattern, 0))));
	  error_count++;
	}
      break;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      switch (fmt[i])
	{
	case 'e': case 'u':
	  validate_pattern (XEXP (pattern, i), insn, NULL_RTX, 0);
	  break;

	case 'E':
	  for (j = 0; j < XVECLEN (pattern, i); j++)
	    validate_pattern (XVECEXP (pattern, i, j), insn, NULL_RTX, 0);
	  break;

	case 'i': case 'w': case '0': case 's':
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}