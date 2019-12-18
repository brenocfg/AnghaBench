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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int CC0 ; 
 int CLOBBER ; 
 int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (size_t) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int MEM ; 
 int PC ; 
 int REG ; 
 int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  referenced_regs ; 
 scalar_t__* reg_equiv_address ; 
 scalar_t__* reg_equiv_mem ; 
 int* reg_renumber ; 

__attribute__((used)) static void
mark_referenced_regs (rtx x)
{
  enum rtx_code code = GET_CODE (x);
  const char *fmt;
  int i, j;

  if (code == SET)
    mark_referenced_regs (SET_SRC (x));
  if (code == SET || code == CLOBBER)
    {
      x = SET_DEST (x);
      code = GET_CODE (x);
      if ((code == REG && REGNO (x) < FIRST_PSEUDO_REGISTER)
	  || code == PC || code == CC0
	  || (code == SUBREG && REG_P (SUBREG_REG (x))
	      && REGNO (SUBREG_REG (x)) < FIRST_PSEUDO_REGISTER
	      /* If we're setting only part of a multi-word register,
		 we shall mark it as referenced, because the words
		 that are not being set should be restored.  */
	      && ((GET_MODE_SIZE (GET_MODE (x))
		   >= GET_MODE_SIZE (GET_MODE (SUBREG_REG (x))))
		  || (GET_MODE_SIZE (GET_MODE (SUBREG_REG (x)))
		      <= UNITS_PER_WORD))))
	return;
    }
  if (code == MEM || code == SUBREG)
    {
      x = XEXP (x, 0);
      code = GET_CODE (x);
    }

  if (code == REG)
    {
      int regno = REGNO (x);
      int hardregno = (regno < FIRST_PSEUDO_REGISTER ? regno
		       : reg_renumber[regno]);

      if (hardregno >= 0)
	{
	  int nregs = hard_regno_nregs[hardregno][GET_MODE (x)];
	  while (nregs-- > 0)
	    SET_HARD_REG_BIT (referenced_regs, hardregno + nregs);
	}
      /* If this is a pseudo that did not get a hard register, scan its
	 memory location, since it might involve the use of another
	 register, which might be saved.  */
      else if (reg_equiv_mem[regno] != 0)
	mark_referenced_regs (XEXP (reg_equiv_mem[regno], 0));
      else if (reg_equiv_address[regno] != 0)
	mark_referenced_regs (reg_equiv_address[regno]);
      return;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	mark_referenced_regs (XEXP (x, i));
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  mark_referenced_regs (XVECEXP (x, i, j));
    }
}