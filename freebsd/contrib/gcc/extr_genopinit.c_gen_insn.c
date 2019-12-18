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
typedef  int MAX_MACHINE_MODE ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char* GET_MODE_NAME (int) ; 
 scalar_t__ GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  GET_RTX_CLASS (int) ; 
 char* GET_RTX_NAME (int) ; 
 int /*<<< orphan*/  MODE_COMPLEX_FLOAT ; 
 int /*<<< orphan*/  MODE_DECIMAL_FLOAT ; 
 int /*<<< orphan*/  MODE_FLOAT ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  MODE_PARTIAL_INT ; 
 int /*<<< orphan*/  MODE_VECTOR_FLOAT ; 
 int /*<<< orphan*/  MODE_VECTOR_INT ; 
 int NUM_RTX_CODE ; 
 int /*<<< orphan*/  RTX_COMM_COMPARE ; 
 int /*<<< orphan*/  RTX_COMPARE ; 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int) ; 
 char const TOLOWER (char const) ; 
 char const TOUPPER (char const) ; 
 scalar_t__* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * mode_class ; 
 char** optabs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
gen_insn (rtx insn)
{
  const char *name = XSTR (insn, 0);
  int m1 = 0, m2 = 0, op = 0;
  size_t pindex;
  int i;
  const char *np, *pp, *p, *q;

  /* Don't mention instructions whose names are the null string.
     They are in the machine description just to be recognized.  */
  if (*name == 0)
    return;

  /* See if NAME matches one of the patterns we have for the optabs we know
     about.  */

  for (pindex = 0; pindex < ARRAY_SIZE (optabs); pindex++)
    {
      int force_float = 0, force_int = 0, force_partial_int = 0;
      int force_consec = 0;
      int matches = 1;

      for (pp = optabs[pindex]; pp[0] != '$' || pp[1] != '('; pp++)
	;

      for (pp += 2, np = name; matches && ! (pp[0] == '$' && pp[1] == ')');
	   pp++)
	{
	  if (*pp != '$')
	    {
	      if (*pp != *np++)
		break;
	    }
	  else
	    switch (*++pp)
	      {
	      case 'N':
		force_consec = 1;
		break;
	      case 'I':
		force_int = 1;
		break;
	      case 'P':
                force_partial_int = 1;
                break;
	      case 'F':
		force_float = 1;
		break;
	      case 'V':
                break;
	      case 'c':
		for (op = 0; op < NUM_RTX_CODE; op++)
		  {
		    for (p = GET_RTX_NAME(op), q = np; *p; p++, q++)
		      if (*p != *q)
			break;

		    /* We have to be concerned about matching "gt" and
		       missing "gtu", e.g., so verify we have reached the
		       end of thing we are to match.  */
		    if (*p == 0 && *q == 0
			&& (GET_RTX_CLASS (op) == RTX_COMPARE
			    || GET_RTX_CLASS (op) == RTX_COMM_COMPARE))
		      break;
		  }

		if (op == NUM_RTX_CODE)
		  matches = 0;
		else
		  np += strlen (GET_RTX_NAME(op));
		break;
	      case 'a':
	      case 'b':
		/* This loop will stop at the first prefix match, so
                   look through the modes in reverse order, in case
                   there are extra CC modes and CC is a prefix of the
                   CC modes (as it should be).  */
		for (i = (MAX_MACHINE_MODE) - 1; i >= 0; i--)
		  {
		    for (p = GET_MODE_NAME(i), q = np; *p; p++, q++)
		      if (TOLOWER (*p) != *q)
			break;

		    if (*p == 0
			&& (! force_int || mode_class[i] == MODE_INT 
			    || mode_class[i] == MODE_VECTOR_INT)
		        && (! force_partial_int
                            || mode_class[i] == MODE_INT
                            || mode_class[i] == MODE_PARTIAL_INT
			    || mode_class[i] == MODE_VECTOR_INT)
			&& (! force_float
			    || mode_class[i] == MODE_FLOAT 
			    || mode_class[i] == MODE_DECIMAL_FLOAT
			    || mode_class[i] == MODE_COMPLEX_FLOAT
			    || mode_class[i] == MODE_VECTOR_FLOAT))
		      break;
		  }

		if (i < 0)
		  matches = 0;
		else if (*pp == 'a')
		  m1 = i, np += strlen (GET_MODE_NAME(i));
		else
		  m2 = i, np += strlen (GET_MODE_NAME(i));

		force_int = force_partial_int = force_float = 0;
		break;

	      default:
		gcc_unreachable ();
	      }
	}

      if (matches && pp[0] == '$' && pp[1] == ')'
	  && *np == 0
	  && (! force_consec || (int) GET_MODE_WIDER_MODE(m1) == m2))
	break;
    }

  if (pindex == ARRAY_SIZE (optabs))
    return;

  /* We found a match.  If this pattern is only conditionally present,
     write out the "if" and two extra blanks.  */

  if (*XSTR (insn, 2) != 0)
    printf ("  if (HAVE_%s)\n  ", name);

  printf ("  ");

  /* Now write out the initialization, making all required substitutions.  */
  for (pp = optabs[pindex]; *pp; pp++)
    {
      if (*pp != '$')
	putchar (*pp);
      else
	switch (*++pp)
	  {
	  case '(':  case ')':
	  case 'I':  case 'F':  case 'N':
	    break;
	  case 'V':
	    if (SCALAR_FLOAT_MODE_P (m1))
              printf ("v");
            break;
	  case 'a':
	    for (np = GET_MODE_NAME(m1); *np; np++)
	      putchar (TOLOWER (*np));
	    break;
	  case 'b':
	    for (np = GET_MODE_NAME(m2); *np; np++)
	      putchar (TOLOWER (*np));
	    break;
	  case 'A':
	    printf ("%smode", GET_MODE_NAME(m1));
	    break;
	  case 'B':
	    printf ("%smode", GET_MODE_NAME(m2));
	    break;
	  case 'c':
	    printf ("%s", GET_RTX_NAME(op));
	    break;
	  case 'C':
	    for (np = GET_RTX_NAME(op); *np; np++)
	      putchar (TOUPPER (*np));
	    break;
	  }
    }

  printf (";\n");
}