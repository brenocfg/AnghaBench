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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  MATCH_OPERAND 131 
#define  MATCH_OPERATOR 130 
#define  MATCH_PARALLEL 129 
#define  MATCH_SCRATCH 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int n_alternatives (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
collect_insn_data (rtx pattern, int *palt, int *pmax)
{
  const char *fmt;
  enum rtx_code code;
  int i, j, len;

  code = GET_CODE (pattern);
  switch (code)
    {
    case MATCH_OPERAND:
      i = n_alternatives (XSTR (pattern, 2));
      *palt = (i > *palt ? i : *palt);
      /* Fall through.  */

    case MATCH_OPERATOR:
    case MATCH_SCRATCH:
    case MATCH_PARALLEL:
      i = XINT (pattern, 0);
      if (i > *pmax)
	*pmax = i;
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
	  collect_insn_data (XEXP (pattern, i), palt, pmax);
	  break;

	case 'V':
	  if (XVEC (pattern, i) == NULL)
	    break;
	  /* Fall through.  */
	case 'E':
	  for (j = XVECLEN (pattern, i) - 1; j >= 0; --j)
	    collect_insn_data (XVECEXP (pattern, i, j), palt, pmax);
	  break;

	case 'i': case 'w': case '0': case 's': case 'S': case 'T':
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}