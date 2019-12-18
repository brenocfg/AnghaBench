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
struct regcache {int dummy; } ;
struct gdbarch {int (* return_value ) (struct gdbarch*,struct type*,struct regcache*,void*,void const*) ;} ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (struct gdbarch*,struct type*,struct regcache*,void*,void const*) ; 

enum return_value_convention
gdbarch_return_value (struct gdbarch *gdbarch, struct type *valtype, struct regcache *regcache, void *readbuf, const void *writebuf)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->return_value != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_return_value called\n");
  return gdbarch->return_value (gdbarch, valtype, regcache, readbuf, writebuf);
}