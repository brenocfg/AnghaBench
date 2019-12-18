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
struct regcache {TYPE_1__* descr; int /*<<< orphan*/  register_valid_p; int /*<<< orphan*/  registers; } ;
struct TYPE_2__ {scalar_t__ gdbarch; int /*<<< orphan*/  sizeof_raw_register_valid_p; int /*<<< orphan*/  sizeof_raw_registers; } ;

/* Variables and functions */
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
regcache_cpy_no_passthrough (struct regcache *dst, struct regcache *src)
{
  int i;
  gdb_assert (src != NULL && dst != NULL);
  gdb_assert (src->descr->gdbarch == dst->descr->gdbarch);
  /* NOTE: cagney/2002-05-17: Don't let the caller do a no-passthrough
     move of data into the current_regcache().  Doing this would be
     silly - it would mean that valid_p would be completely invalid.  */
  gdb_assert (dst != current_regcache);
  memcpy (dst->registers, src->registers, dst->descr->sizeof_raw_registers);
  memcpy (dst->register_valid_p, src->register_valid_p,
	  dst->descr->sizeof_raw_register_valid_p);
}