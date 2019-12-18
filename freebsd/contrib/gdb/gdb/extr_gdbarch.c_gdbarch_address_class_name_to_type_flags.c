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
struct gdbarch {int (* address_class_name_to_type_flags ) (struct gdbarch*,char const*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (struct gdbarch*,char const*,int*) ; 

int
gdbarch_address_class_name_to_type_flags (struct gdbarch *gdbarch, const char *name, int *type_flags_ptr)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->address_class_name_to_type_flags != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_address_class_name_to_type_flags called\n");
  return gdbarch->address_class_name_to_type_flags (gdbarch, name, type_flags_ptr);
}