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
struct regcache_descr {int nr_cooked_registers; } ;
struct regcache {struct regcache_descr* descr; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_read ; 
 int /*<<< orphan*/  regcache_cooked_write ; 
 int /*<<< orphan*/  regcache_xfer_part (struct regcache*,int,int,int,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
regcache_cooked_write_part (struct regcache *regcache, int regnum,
			    int offset, int len, const void *buf)
{
  struct regcache_descr *descr = regcache->descr;
  gdb_assert (regnum >= 0 && regnum < descr->nr_cooked_registers);
  regcache_xfer_part (regcache, regnum, offset, len, NULL, buf,
		      regcache_cooked_read, regcache_cooked_write);
}