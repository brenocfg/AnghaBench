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
struct regcache {scalar_t__ readonly_p; TYPE_1__* descr; } ;
struct TYPE_2__ {scalar_t__ gdbarch; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cooked_read ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cpy_no_passthrough (struct regcache*,struct regcache*) ; 
 int /*<<< orphan*/  regcache_restore (struct regcache*,int /*<<< orphan*/ ,struct regcache*) ; 
 int /*<<< orphan*/  regcache_save (struct regcache*,int /*<<< orphan*/ ,struct regcache*) ; 

void
regcache_cpy (struct regcache *dst, struct regcache *src)
{
  int i;
  char *buf;
  gdb_assert (src != NULL && dst != NULL);
  gdb_assert (src->descr->gdbarch == dst->descr->gdbarch);
  gdb_assert (src != dst);
  gdb_assert (src->readonly_p || dst->readonly_p);
  if (!src->readonly_p)
    regcache_save (dst, do_cooked_read, src);
  else if (!dst->readonly_p)
    regcache_restore (dst, do_cooked_read, src);
  else
    regcache_cpy_no_passthrough (dst, src);
}