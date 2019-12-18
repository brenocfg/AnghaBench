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
struct gdbarch {int /*<<< orphan*/  (* pseudo_register_write ) (struct gdbarch*,struct regcache*,int,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct gdbarch*,struct regcache*,int,void const*) ; 

void
gdbarch_pseudo_register_write (struct gdbarch *gdbarch, struct regcache *regcache, int cookednum, const void *buf)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->pseudo_register_write != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_pseudo_register_write called\n");
  gdbarch->pseudo_register_write (gdbarch, regcache, cookednum, buf);
}