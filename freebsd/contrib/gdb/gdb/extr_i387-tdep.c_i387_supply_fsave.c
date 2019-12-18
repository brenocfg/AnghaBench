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
struct gdbarch_tdep {scalar_t__ st0_regnum; } ;

/* Variables and functions */
 unsigned char* FSAVE_ADDR (char const*,int) ; 
 scalar_t__ I386_ST0_REGNUM ; 
 int I387_FCTRL_REGNUM ; 
 int I387_FIOFF_REGNUM ; 
 int I387_FOOFF_REGNUM ; 
 int I387_FOP_REGNUM ; 
 int I387_ST0_REGNUM ; 
 int I387_XMM0_REGNUM ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_regcache_arch (struct regcache*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  regcache_raw_supply (struct regcache*,int,unsigned char*) ; 

void
i387_supply_fsave (struct regcache *regcache, int regnum, const void *fsave)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (get_regcache_arch (regcache));
  const char *regs = fsave;
  int i;

  gdb_assert (tdep->st0_regnum >= I386_ST0_REGNUM);

  /* Define I387_ST0_REGNUM such that we use the proper definitions
     for REGCACHE's architecture.  */
#define I387_ST0_REGNUM tdep->st0_regnum

  for (i = I387_ST0_REGNUM; i < I387_XMM0_REGNUM; i++)
    if (regnum == -1 || regnum == i)
      {
	if (fsave == NULL)
	  {
	    regcache_raw_supply (regcache, i, NULL);
	    continue;
	  }

	/* Most of the FPU control registers occupy only 16 bits in the
	   fsave area.  Give those a special treatment.  */
	if (i >= I387_FCTRL_REGNUM
	    && i != I387_FIOFF_REGNUM && i != I387_FOOFF_REGNUM)
	  {
	    unsigned char val[4];

	    memcpy (val, FSAVE_ADDR (regs, i), 2);
	    val[2] = val[3] = 0;
	    if (i == I387_FOP_REGNUM)
	      val[1] &= ((1 << 3) - 1);
	    regcache_raw_supply (regcache, i, val);
	  }
	else
	  regcache_raw_supply (regcache, i, FSAVE_ADDR (regs, i));
      }
#undef I387_ST0_REGNUM
}