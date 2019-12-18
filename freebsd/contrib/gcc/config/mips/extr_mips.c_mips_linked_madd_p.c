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
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ MINUS ; 
 scalar_t__ MULT ; 
 scalar_t__ PLUS ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ reg_set_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

bool
mips_linked_madd_p (rtx prev, rtx insn)
{
  rtx x;

  x = single_set (insn);
  if (x == 0)
    return false;

  x = SET_SRC (x);

  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 0)) == MULT
      && reg_set_p (XEXP (x, 1), prev))
    return true;

  if (GET_CODE (x) == MINUS
      && GET_CODE (XEXP (x, 1)) == MULT
      && reg_set_p (XEXP (x, 0), prev))
    return true;

  return false;
}