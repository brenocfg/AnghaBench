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
typedef  scalar_t__ RTX_CODE ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ MATCH_OPERAND ; 
 scalar_t__ MATCH_OPERATOR ; 
 scalar_t__ MATCH_PARALLEL ; 
 scalar_t__ MATCH_SCRATCH ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XINT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVEC (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static rtx
find_operand (rtx pattern, int n, rtx stop)
{
  const char *fmt;
  RTX_CODE code;
  int i, j, len;
  rtx r;

  if (pattern == stop)
    return stop;

  code = GET_CODE (pattern);
  if ((code == MATCH_SCRATCH
       || code == MATCH_OPERAND
       || code == MATCH_OPERATOR
       || code == MATCH_PARALLEL)
      && XINT (pattern, 0) == n)
    return pattern;

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      switch (fmt[i])
	{
	case 'e': case 'u':
	  if ((r = find_operand (XEXP (pattern, i), n, stop)) != NULL_RTX)
	    return r;
	  break;

	case 'V':
	  if (! XVEC (pattern, i))
	    break;
	  /* Fall through.  */

	case 'E':
	  for (j = 0; j < XVECLEN (pattern, i); j++)
	    if ((r = find_operand (XVECEXP (pattern, i, j), n, stop))
		!= NULL_RTX)
	      return r;
	  break;

	case 'i': case 'w': case '0': case 's':
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  return NULL;
}