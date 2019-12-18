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
struct gdbarch {int /*<<< orphan*/  in_function_epilogue_p; } ;
typedef  int /*<<< orphan*/  gdbarch_in_function_epilogue_p_ftype ;

/* Variables and functions */

void
set_gdbarch_in_function_epilogue_p (struct gdbarch *gdbarch,
                                    gdbarch_in_function_epilogue_p_ftype in_function_epilogue_p)
{
  gdbarch->in_function_epilogue_p = in_function_epilogue_p;
}