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
 int /*<<< orphan*/  BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ ZERO_EXTRACT ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ pc_rtx ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  side_effects_p (scalar_t__) ; 

int
set_noop_p (rtx set)
{
  rtx src = SET_SRC (set);
  rtx dst = SET_DEST (set);

  if (dst == pc_rtx && src == pc_rtx)
    return 1;

  if (MEM_P (dst) && MEM_P (src))
    return rtx_equal_p (dst, src) && !side_effects_p (dst);

  if (GET_CODE (dst) == ZERO_EXTRACT)
    return rtx_equal_p (XEXP (dst, 0), src)
	   && ! BYTES_BIG_ENDIAN && XEXP (dst, 2) == const0_rtx
	   && !side_effects_p (src);

  if (GET_CODE (dst) == STRICT_LOW_PART)
    dst = XEXP (dst, 0);

  if (GET_CODE (src) == SUBREG && GET_CODE (dst) == SUBREG)
    {
      if (SUBREG_BYTE (src) != SUBREG_BYTE (dst))
	return 0;
      src = SUBREG_REG (src);
      dst = SUBREG_REG (dst);
    }

  return (REG_P (src) && REG_P (dst)
	  && REGNO (src) == REGNO (dst));
}