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
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_2__ {int nr_cooked_registers; int /*<<< orphan*/ * sizeof_register; } ;

/* Variables and functions */
 void* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int,void*) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
regcache_cooked_write_unsigned (struct regcache *regcache, int regnum,
				ULONGEST val)
{
  void *buf;
  gdb_assert (regcache != NULL);
  gdb_assert (regnum >=0 && regnum < regcache->descr->nr_cooked_registers);
  buf = alloca (regcache->descr->sizeof_register[regnum]);
  store_unsigned_integer (buf, regcache->descr->sizeof_register[regnum], val);
  regcache_cooked_write (regcache, regnum, buf);
}