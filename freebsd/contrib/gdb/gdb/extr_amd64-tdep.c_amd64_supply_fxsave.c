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
struct regcache {int dummy; } ;

/* Variables and functions */
 int I387_FISEG_REGNUM ; 
 int I387_FOSEG_REGNUM ; 
 int /*<<< orphan*/  i387_supply_fxsave (struct regcache*,int,void const*) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char const*) ; 

void
amd64_supply_fxsave (struct regcache *regcache, int regnum,
		      const void *fxsave)
{
  i387_supply_fxsave (regcache, regnum, fxsave);

  if (fxsave)
    {
      const char *regs = fxsave;

      if (regnum == -1 || regnum == I387_FISEG_REGNUM)
	regcache_raw_supply (regcache, I387_FISEG_REGNUM, regs + 12);
      if (regnum == -1 || regnum == I387_FOSEG_REGNUM)
	regcache_raw_supply (regcache, I387_FOSEG_REGNUM, regs + 20);
    }
}