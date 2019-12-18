#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regcache {TYPE_1__* descr; } ;
struct TYPE_2__ {int nr_cooked_registers; int nr_raw_registers; int /*<<< orphan*/  gdbarch; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdbarch_pseudo_register_write (int /*<<< orphan*/ ,struct regcache*,int,void const*) ; 
 int /*<<< orphan*/  regcache_raw_write (struct regcache*,int,void const*) ; 

void
regcache_cooked_write (struct regcache *regcache, int regnum, const void *buf)
{
  gdb_assert (regnum >= 0);
  gdb_assert (regnum < regcache->descr->nr_cooked_registers);
  if (regnum < regcache->descr->nr_raw_registers)
    regcache_raw_write (regcache, regnum, buf);
  else
    gdbarch_pseudo_register_write (regcache->descr->gdbarch, regcache,
				   regnum, buf);
}