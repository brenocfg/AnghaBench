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
struct gdbarch {int (* deprecated_frameless_function_invocation ) (struct frame_info*) ;} ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (struct frame_info*) ; 

int
gdbarch_deprecated_frameless_function_invocation (struct gdbarch *gdbarch, struct frame_info *fi)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_frameless_function_invocation != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_frameless_function_invocation called\n");
  return gdbarch->deprecated_frameless_function_invocation (fi);
}