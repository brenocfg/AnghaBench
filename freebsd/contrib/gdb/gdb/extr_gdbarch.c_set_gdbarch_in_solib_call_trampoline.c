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
struct gdbarch {int /*<<< orphan*/  in_solib_call_trampoline; } ;
typedef  int /*<<< orphan*/  gdbarch_in_solib_call_trampoline_ftype ;

/* Variables and functions */

void
set_gdbarch_in_solib_call_trampoline (struct gdbarch *gdbarch,
                                      gdbarch_in_solib_call_trampoline_ftype in_solib_call_trampoline)
{
  gdbarch->in_solib_call_trampoline = in_solib_call_trampoline;
}