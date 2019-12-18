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
struct regset {struct gdbarch_tdep* descr; } ;
struct regcache {int dummy; } ;
struct gdbarch_tdep {size_t sizeof_fpregset; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd64_supply_fxsave (struct regcache*,int,void const*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static void
amd64_supply_fpregset (const struct regset *regset, struct regcache *regcache,
		       int regnum, const void *fpregs, size_t len)
{
  const struct gdbarch_tdep *tdep = regset->descr;

  gdb_assert (len == tdep->sizeof_fpregset);
  amd64_supply_fxsave (regcache, regnum, fpregs);
}