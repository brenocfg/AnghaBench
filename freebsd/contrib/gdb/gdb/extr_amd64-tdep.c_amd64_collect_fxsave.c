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
 int /*<<< orphan*/  i387_collect_fxsave (struct regcache const*,int,void*) ; 
 int /*<<< orphan*/  regcache_raw_collect (struct regcache const*,int,char*) ; 

void
amd64_collect_fxsave (const struct regcache *regcache, int regnum,
		      void *fxsave)
{
  char *regs = fxsave;

  i387_collect_fxsave (regcache, regnum, fxsave);

  if (regnum == -1 || regnum == I387_FISEG_REGNUM)
    regcache_raw_collect (regcache, I387_FISEG_REGNUM, regs + 12);
  if (regnum == -1 || regnum == I387_FOSEG_REGNUM)
    regcache_raw_collect (regcache, I387_FOSEG_REGNUM, regs + 20);
}