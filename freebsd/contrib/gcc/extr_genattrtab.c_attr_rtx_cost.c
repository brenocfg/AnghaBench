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
#define  EQ_ATTR 130 
#define  EQ_ATTR_ALT 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int /*<<< orphan*/  GET_RTX_LENGTH (int) ; 
#define  MATCH_OPERAND 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alternative_name ; 
 int /*<<< orphan*/  strcmp_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
attr_rtx_cost (rtx x)
{
  int cost = 0;
  enum rtx_code code;
  if (!x)
    return 0;
  code = GET_CODE (x);
  switch (code)
    {
    case MATCH_OPERAND:
      if (XSTR (x, 1)[0])
	return 10;
      else
	return 0;

    case EQ_ATTR_ALT:
      return 0;

    case EQ_ATTR:
      /* Alternatives don't result into function call.  */
      if (!strcmp_check (XSTR (x, 0), alternative_name))
	return 0;
      else
	return 5;
    default:
      {
	int i, j;
	const char *fmt = GET_RTX_FORMAT (code);
	for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
	  {
	    switch (fmt[i])
	      {
	      case 'V':
	      case 'E':
		for (j = 0; j < XVECLEN (x, i); j++)
		  cost += attr_rtx_cost (XVECEXP (x, i, j));
		break;
	      case 'e':
		cost += attr_rtx_cost (XEXP (x, i));
		break;
	      }
	  }
      }
      break;
    }
  return cost;
}