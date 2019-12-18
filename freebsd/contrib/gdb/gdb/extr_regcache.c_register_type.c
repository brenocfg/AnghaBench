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
struct regcache_descr {int nr_cooked_registers; struct type** register_type; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct regcache_descr* regcache_descr (struct gdbarch*) ; 

struct type *
register_type (struct gdbarch *gdbarch, int regnum)
{
  struct regcache_descr *descr = regcache_descr (gdbarch);
  gdb_assert (regnum >= 0 && regnum < descr->nr_cooked_registers);
  return descr->register_type[regnum];
}