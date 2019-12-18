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
struct gdbarch {int (* sdb_reg_to_regnum ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (int) ; 

int
gdbarch_sdb_reg_to_regnum (struct gdbarch *gdbarch, int sdb_regnr)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->sdb_reg_to_regnum != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_sdb_reg_to_regnum called\n");
  return gdbarch->sdb_reg_to_regnum (sdb_regnr);
}