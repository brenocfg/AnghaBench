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
struct gdbarch {int /*<<< orphan*/  deprecated_frameless_function_invocation; } ;
typedef  int /*<<< orphan*/  gdbarch_deprecated_frameless_function_invocation_ftype ;

/* Variables and functions */

void
set_gdbarch_deprecated_frameless_function_invocation (struct gdbarch *gdbarch,
                                                      gdbarch_deprecated_frameless_function_invocation_ftype deprecated_frameless_function_invocation)
{
  gdbarch->deprecated_frameless_function_invocation = deprecated_frameless_function_invocation;
}