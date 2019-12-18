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
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_known_value (scalar_t__) ; 
 int rtx_addr_can_trap_p (scalar_t__) ; 

__attribute__((used)) static int
deps_may_trap_p (rtx mem)
{
  rtx addr = XEXP (mem, 0);

  if (REG_P (addr) && REGNO (addr) >= FIRST_PSEUDO_REGISTER)
    {
      rtx t = get_reg_known_value (REGNO (addr));
      if (t)
	addr = t;
    }
  return rtx_addr_can_trap_p (addr);
}