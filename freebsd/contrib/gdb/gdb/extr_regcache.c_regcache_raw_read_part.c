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
struct regcache_descr {int nr_raw_registers; } ;
struct regcache {struct regcache_descr* descr; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_raw_read ; 
 int /*<<< orphan*/  regcache_raw_write ; 
 int /*<<< orphan*/  regcache_xfer_part (struct regcache*,int,int,int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
regcache_raw_read_part (struct regcache *regcache, int regnum,
			int offset, int len, void *buf)
{
  struct regcache_descr *descr = regcache->descr;
  gdb_assert (regnum >= 0 && regnum < descr->nr_raw_registers);
  regcache_xfer_part (regcache, regnum, offset, len, buf, NULL,
		      regcache_raw_read, regcache_raw_write);
}