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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
is_mem_ref (rtx pat)
{
  const char * fmt;
  int i, j;
  bool ret = false;

  if (GET_CODE (pat) == MEM)
    return true;

  /* Recursively process the pattern.  */
  fmt = GET_RTX_FORMAT (GET_CODE (pat));

  for (i = GET_RTX_LENGTH (GET_CODE (pat)) - 1; i >= 0 && !ret; i--)
    {
      if (fmt[i] == 'e')
	ret |= is_mem_ref (XEXP (pat, i));
      else if (fmt[i] == 'E')
	for (j = XVECLEN (pat, i) - 1; j >= 0; j--)
	  ret |= is_mem_ref (XVECEXP (pat, i, j));
    }

  return ret;
}