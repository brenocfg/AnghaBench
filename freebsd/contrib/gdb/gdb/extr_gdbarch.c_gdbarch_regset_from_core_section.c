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
struct regset {int dummy; } ;
struct gdbarch {struct regset const* (* regset_from_core_section ) (struct gdbarch*,char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 struct regset const* stub1 (struct gdbarch*,char const*,size_t) ; 

const struct regset *
gdbarch_regset_from_core_section (struct gdbarch *gdbarch, const char *sect_name, size_t sect_size)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->regset_from_core_section != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_regset_from_core_section called\n");
  return gdbarch->regset_from_core_section (gdbarch, sect_name, sect_size);
}