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
typedef  int rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int) ; 
 scalar_t__ MEM ; 
 scalar_t__ REG ; 
 int SET_DEST (int) ; 
 scalar_t__ SUBREG ; 
 int SUBREG_REG (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int ia64_single_set (int) ; 
 int reg_mentioned_p (int,int) ; 

int
ia64_st_address_bypass_p (rtx producer, rtx consumer)
{
  rtx dest, reg, mem;

  gcc_assert (producer && consumer);
  dest = ia64_single_set (producer);
  gcc_assert (dest);
  reg = SET_DEST (dest);
  gcc_assert (reg);
  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);
  gcc_assert (GET_CODE (reg) == REG);
  
  dest = ia64_single_set (consumer);
  gcc_assert (dest);
  mem = SET_DEST (dest);
  gcc_assert (mem && GET_CODE (mem) == MEM);
  return reg_mentioned_p (reg, mem);
}