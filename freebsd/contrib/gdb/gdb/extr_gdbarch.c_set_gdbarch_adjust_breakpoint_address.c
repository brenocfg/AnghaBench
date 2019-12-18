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
struct gdbarch {int /*<<< orphan*/  adjust_breakpoint_address; } ;
typedef  int /*<<< orphan*/  gdbarch_adjust_breakpoint_address_ftype ;

/* Variables and functions */

void
set_gdbarch_adjust_breakpoint_address (struct gdbarch *gdbarch,
                                       gdbarch_adjust_breakpoint_address_ftype adjust_breakpoint_address)
{
  gdbarch->adjust_breakpoint_address = adjust_breakpoint_address;
}