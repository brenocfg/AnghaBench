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
typedef  char uint64_t ;
struct regcache {int dummy; } ;

/* Variables and functions */
 size_t IA64_BSPSTORE_REGNUM ; 
 int IA64_BSP_REGNUM ; 
 int NUM_REGS ; 
 int* reg_offset ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,char*) ; 

__attribute__((used)) static void
ia64_fbsd_regcache_supply (struct regcache *regcache, int regno,
			   const void *regs)
{
  int ofs;

  if (regno < 0 || regno >= NUM_REGS)
    return;

  ofs = reg_offset[regno];
  if (regno == IA64_BSP_REGNUM)
    {
      /* BSP is synthesized. It's not actually present in struct reg,
	 but can be derived from bspstore and ndirty. The offset of
	 IA64_BSP_REGNUM in the reg_offset array above is that of the
	 ndirty field in struct reg. */
      uint64_t bsp;
      bsp = *((uint64_t*)((char *)regs + ofs));		/* ndirty */
      bsp += *((uint64_t*)((char *)regs + reg_offset[IA64_BSPSTORE_REGNUM]));
      regcache_raw_supply (regcache, regno, &bsp);
    }
  else
    {
      if (ofs < 0)
	regcache_raw_supply (regcache, regno, NULL);
      else
	regcache_raw_supply (regcache, regno, (char *)regs + ofs);
    }
}