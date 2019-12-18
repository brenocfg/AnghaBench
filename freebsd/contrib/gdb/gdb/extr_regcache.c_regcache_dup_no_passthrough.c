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
struct TYPE_2__ {int /*<<< orphan*/  gdbarch; } ;

/* Variables and functions */
 int /*<<< orphan*/ * current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cpy_no_passthrough (struct regcache*,struct regcache*) ; 
 struct regcache* regcache_xmalloc (int /*<<< orphan*/ ) ; 

struct regcache *
regcache_dup_no_passthrough (struct regcache *src)
{
  struct regcache *newbuf;
  gdb_assert (current_regcache != NULL);
  newbuf = regcache_xmalloc (src->descr->gdbarch);
  regcache_cpy_no_passthrough (newbuf, src);
  return newbuf;
}