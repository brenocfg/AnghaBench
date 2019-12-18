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
struct regcache {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* deprecated_extract_struct_value_address ) (struct regcache*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct regcache*) ; 

CORE_ADDR
gdbarch_deprecated_extract_struct_value_address (struct gdbarch *gdbarch, struct regcache *regcache)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_extract_struct_value_address != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_extract_struct_value_address called\n");
  return gdbarch->deprecated_extract_struct_value_address (regcache);
}