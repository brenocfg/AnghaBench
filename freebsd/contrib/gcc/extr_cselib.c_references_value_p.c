#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_2__ {scalar_t__ locs; } ;

/* Variables and functions */
 TYPE_1__* CSELIB_VAL_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 scalar_t__ VALUE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 

int
references_value_p (rtx x, int only_useless)
{
  enum rtx_code code = GET_CODE (x);
  const char *fmt = GET_RTX_FORMAT (code);
  int i, j;

  if (GET_CODE (x) == VALUE
      && (! only_useless || CSELIB_VAL_PTR (x)->locs == 0))
    return 1;

  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e' && references_value_p (XEXP (x, i), only_useless))
	return 1;
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (references_value_p (XVECEXP (x, i, j), only_useless))
	    return 1;
    }

  return 0;
}