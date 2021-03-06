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
struct gdbarch {int /*<<< orphan*/  deprecated_call_dummy_breakpoint_offset; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

void
set_gdbarch_deprecated_call_dummy_breakpoint_offset (struct gdbarch *gdbarch,
                                                     CORE_ADDR deprecated_call_dummy_breakpoint_offset)
{
  gdbarch->deprecated_call_dummy_breakpoint_offset = deprecated_call_dummy_breakpoint_offset;
}