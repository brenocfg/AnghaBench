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
typedef  int /*<<< orphan*/ * rtx ;
typedef  scalar_t__ RTX_CODE ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ MATCH_OPERAND ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int* XSTR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XVEC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static rtx
find_matching_operand (rtx pattern, int n)
{
  const char *fmt;
  RTX_CODE code;
  int i, j, len;
  rtx r;

  code = GET_CODE (pattern);
  if (code == MATCH_OPERAND
      && (XSTR (pattern, 2)[0] == '0' + n
	  || (XSTR (pattern, 2)[0] == '%'
	      && XSTR (pattern, 2)[1] == '0' + n)))
    return pattern;

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      switch (fmt[i])
	{
	case 'e': case 'u':
	  if ((r = find_matching_operand (XEXP (pattern, i), n)))
	    return r;
	  break;

	case 'V':
	  if (! XVEC (pattern, i))
	    break;
	  /* Fall through.  */

	case 'E':
	  for (j = 0; j < XVECLEN (pattern, i); j++)
	    if ((r = find_matching_operand (XVECEXP (pattern, i, j), n)))
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