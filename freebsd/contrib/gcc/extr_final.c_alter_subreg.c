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

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 scalar_t__ adjust_address (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_rtx_REG_offset (scalar_t__,int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ simplify_subreg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 unsigned int subreg_regno (scalar_t__) ; 

rtx
alter_subreg (rtx *xp)
{
  rtx x = *xp;
  rtx y = SUBREG_REG (x);

  /* simplify_subreg does not remove subreg from volatile references.
     We are required to.  */
  if (MEM_P (y))
    {
      int offset = SUBREG_BYTE (x);

      /* For paradoxical subregs on big-endian machines, SUBREG_BYTE
	 contains 0 instead of the proper offset.  See simplify_subreg.  */
      if (offset == 0
	  && GET_MODE_SIZE (GET_MODE (y)) < GET_MODE_SIZE (GET_MODE (x)))
        {
          int difference = GET_MODE_SIZE (GET_MODE (y))
			   - GET_MODE_SIZE (GET_MODE (x));
          if (WORDS_BIG_ENDIAN)
            offset += (difference / UNITS_PER_WORD) * UNITS_PER_WORD;
          if (BYTES_BIG_ENDIAN)
            offset += difference % UNITS_PER_WORD;
        }

      *xp = adjust_address (y, GET_MODE (x), offset);
    }
  else
    {
      rtx new = simplify_subreg (GET_MODE (x), y, GET_MODE (y),
				 SUBREG_BYTE (x));

      if (new != 0)
	*xp = new;
      else if (REG_P (y))
	{
	  /* Simplify_subreg can't handle some REG cases, but we have to.  */
	  unsigned int regno = subreg_regno (x);
	  *xp = gen_rtx_REG_offset (y, GET_MODE (x), regno, SUBREG_BYTE (x));
	}
    }

  return *xp;
}