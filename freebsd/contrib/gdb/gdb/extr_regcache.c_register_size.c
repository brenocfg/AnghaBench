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
struct regcache_descr {int* sizeof_register; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct regcache_descr* regcache_descr (struct gdbarch*) ; 

int
register_size (struct gdbarch *gdbarch, int regnum)
{
  struct regcache_descr *descr = regcache_descr (gdbarch);
  int size;
  gdb_assert (regnum >= 0 && regnum < (NUM_REGS + NUM_PSEUDO_REGS));
  size = descr->sizeof_register[regnum];
  /* NB: The deprecated DEPRECATED_REGISTER_RAW_SIZE, if not provided, defaults
     to the size of the register's type.  */
  gdb_assert (size == DEPRECATED_REGISTER_RAW_SIZE (regnum)); /* OK */
  /* NB: Don't check the register's virtual size.  It, in say the case
     of the MIPS, may not match the raw size!  */
  return size;
}