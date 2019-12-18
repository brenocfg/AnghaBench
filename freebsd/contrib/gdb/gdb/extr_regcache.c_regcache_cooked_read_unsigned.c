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
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int,char*) ; 

void
regcache_cooked_read_unsigned (struct regcache *regcache, int regnum,
			       ULONGEST *val)
{
  char *buf;
  gdb_assert (regcache != NULL);
  gdb_assert (regnum >= 0 && regnum < regcache->descr->nr_cooked_registers);
  buf = alloca (regcache->descr->sizeof_register[regnum]);
  regcache_cooked_read (regcache, regnum, buf);
  (*val) = extract_unsigned_integer (buf,
				     regcache->descr->sizeof_register[regnum]);
}