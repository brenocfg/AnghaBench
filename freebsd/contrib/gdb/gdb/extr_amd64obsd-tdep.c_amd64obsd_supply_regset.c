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
struct gdbarch_tdep {size_t sizeof_gregset; } ;

/* Variables and functions */
 size_t I387_SIZEOF_FXSAVE ; 
 int /*<<< orphan*/  amd64_supply_fxsave (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  i386_supply_gregset (struct regset const*,struct regcache*,int,void const*,size_t) ; 

__attribute__((used)) static void
amd64obsd_supply_regset (const struct regset *regset,
			 struct regcache *regcache, int regnum,
			 const void *regs, size_t len)
{
  const struct gdbarch_tdep *tdep = regset->descr;

  gdb_assert (len >= tdep->sizeof_gregset + I387_SIZEOF_FXSAVE);

  i386_supply_gregset (regset, regcache, regnum, regs, tdep->sizeof_gregset);
  amd64_supply_fxsave (regcache, regnum, (char *)regs + tdep->sizeof_gregset);
}