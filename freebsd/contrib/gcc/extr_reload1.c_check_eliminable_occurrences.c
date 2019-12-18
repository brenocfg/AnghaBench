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
struct elim_table {scalar_t__ from_rtx; scalar_t__ can_eliminate; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 size_t NUM_ELIMINABLE_REGS ; 
 int REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 struct elim_table* reg_eliminate ; 

__attribute__((used)) static void
check_eliminable_occurrences (rtx x)
{
  const char *fmt;
  int i;
  enum rtx_code code;

  if (x == 0)
    return;

  code = GET_CODE (x);

  if (code == REG && REGNO (x) < FIRST_PSEUDO_REGISTER)
    {
      struct elim_table *ep;

      for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
	if (ep->from_rtx == x)
	  ep->can_eliminate = 0;
      return;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = 0; i < GET_RTX_LENGTH (code); i++, fmt++)
    {
      if (*fmt == 'e')
	check_eliminable_occurrences (XEXP (x, i));
      else if (*fmt == 'E')
	{
	  int j;
	  for (j = 0; j < XVECLEN (x, i); j++)
	    check_eliminable_occurrences (XVECEXP (x, i, j));
	}
    }
}