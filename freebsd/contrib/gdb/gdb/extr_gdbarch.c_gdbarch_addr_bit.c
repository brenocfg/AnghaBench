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
struct gdbarch {scalar_t__ addr_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 

int
gdbarch_addr_bit (struct gdbarch *gdbarch)
{
  gdb_assert (gdbarch != NULL);
  /* Check variable changed from pre-default.  */
  gdb_assert (gdbarch->addr_bit != 0);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_addr_bit called\n");
  return gdbarch->addr_bit;
}