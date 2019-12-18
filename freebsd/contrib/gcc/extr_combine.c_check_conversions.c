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
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_PROMOTED_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  record_promoted_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_truncated_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_conversions (rtx insn, rtx x)
{
  if (GET_CODE (x) == SUBREG || REG_P (x))
    {
      if (GET_CODE (x) == SUBREG
	  && SUBREG_PROMOTED_VAR_P (x)
	  && REG_P (SUBREG_REG (x)))
	record_promoted_value (insn, x);

      record_truncated_value (x);
    }
  else
    {
      const char *format = GET_RTX_FORMAT (GET_CODE (x));
      int i, j;

      for (i = 0; i < GET_RTX_LENGTH (GET_CODE (x)); i++)
	switch (format[i])
	  {
	  case 'e':
	    check_conversions (insn, XEXP (x, i));
	    break;
	  case 'V':
	  case 'E':
	    if (XVEC (x, i) != 0)
	      for (j = 0; j < XVECLEN (x, i); j++)
		check_conversions (insn, XVECEXP (x, i, j));
	    break;
	  }
    }
}