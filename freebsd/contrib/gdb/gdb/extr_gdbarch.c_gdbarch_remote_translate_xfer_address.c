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
struct gdbarch {int /*<<< orphan*/  (* remote_translate_xfer_address ) (struct gdbarch*,struct regcache*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct gdbarch*,struct regcache*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

void
gdbarch_remote_translate_xfer_address (struct gdbarch *gdbarch, struct regcache *regcache, CORE_ADDR gdb_addr, int gdb_len, CORE_ADDR *rem_addr, int *rem_len)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->remote_translate_xfer_address != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_remote_translate_xfer_address called\n");
  gdbarch->remote_translate_xfer_address (gdbarch, regcache, gdb_addr, gdb_len, rem_addr, rem_len);
}