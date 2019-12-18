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
struct type {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* deprecated_register_convert_to_virtual ) (int,struct type*,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (int,struct type*,char*,char*) ; 

void
gdbarch_deprecated_register_convert_to_virtual (struct gdbarch *gdbarch, int regnum, struct type *type, char *from, char *to)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_register_convert_to_virtual != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_register_convert_to_virtual called\n");
  gdbarch->deprecated_register_convert_to_virtual (regnum, type, from, to);
}