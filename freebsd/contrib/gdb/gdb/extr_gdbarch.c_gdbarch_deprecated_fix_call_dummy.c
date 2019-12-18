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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* deprecated_fix_call_dummy ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct value**,struct type*,int) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct value**,struct type*,int) ; 

void
gdbarch_deprecated_fix_call_dummy (struct gdbarch *gdbarch, char *dummy, CORE_ADDR pc, CORE_ADDR fun, int nargs, struct value **args, struct type *type, int gcc_p)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_fix_call_dummy != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_fix_call_dummy called\n");
  gdbarch->deprecated_fix_call_dummy (dummy, pc, fun, nargs, args, type, gcc_p);
}