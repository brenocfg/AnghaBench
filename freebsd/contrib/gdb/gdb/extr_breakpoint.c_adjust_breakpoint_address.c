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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  breakpoint_adjustment_warning (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ gdbarch_adjust_breakpoint_address (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gdbarch_adjust_breakpoint_address_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
adjust_breakpoint_address (CORE_ADDR bpaddr)
{
  if (!gdbarch_adjust_breakpoint_address_p (current_gdbarch))
    {
      /* Very few targets need any kind of breakpoint adjustment.  */
      return bpaddr;
    }
  else
    {
      CORE_ADDR adjusted_bpaddr;

      /* Some targets have architectural constraints on the placement
         of breakpoint instructions.  Obtain the adjusted address.  */
      adjusted_bpaddr = gdbarch_adjust_breakpoint_address (current_gdbarch,
                                                           bpaddr);

      /* An adjusted breakpoint address can significantly alter
         a user's expectations.  Print a warning if an adjustment
	 is required.  */
      if (adjusted_bpaddr != bpaddr)
	breakpoint_adjustment_warning (bpaddr, adjusted_bpaddr, 0, 0);

      return adjusted_bpaddr;
    }
}