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
 int* FSAVE_ADDR (char*,int) ; 
 scalar_t__ I386_ST0_REGNUM ; 
 int I387_FCTRL_REGNUM ; 
 int I387_FIOFF_REGNUM ; 
 int I387_FOOFF_REGNUM ; 
 int I387_FOP_REGNUM ; 
 int I387_ST0_REGNUM ; 
 int I387_XMM0_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 
 int /*<<< orphan*/  regcache_raw_collect (struct regcache*,int,...) ; 

void
i387_fill_fsave (void *fsave, int regnum)
{
  struct regcache *regcache = current_regcache;
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  char *regs = fsave;
  int i;

  gdb_assert (tdep->st0_regnum >= I386_ST0_REGNUM);

  /* Define I387_ST0_REGNUM such that we use the proper definitions
     for REGCACHE's architecture.  */
#define I387_ST0_REGNUM tdep->st0_regnum

  for (i = I387_ST0_REGNUM; i < I387_XMM0_REGNUM; i++)
    if (regnum == -1 || regnum == i)
      {
	/* Most of the FPU control registers occupy only 16 bits in
           the fsave area.  Give those a special treatment.  */
	if (i >= I387_FCTRL_REGNUM
	    && i != I387_FIOFF_REGNUM && i != I387_FOOFF_REGNUM)
	  {
	    unsigned char buf[4];

	    regcache_raw_collect (regcache, i, buf);

	    if (i == I387_FOP_REGNUM)
	      {
		/* The opcode occupies only 11 bits.  Make sure we
                   don't touch the other bits.  */
		buf[1] &= ((1 << 3) - 1);
		buf[1] |= ((FSAVE_ADDR (regs, i))[1] & ~((1 << 3) - 1));
	      }
	    memcpy (FSAVE_ADDR (regs, i), buf, 2);
	  }
	else
	  regcache_raw_collect (regcache, i, FSAVE_ADDR (regs, i));
      }
#undef I387_ST0_REGNUM
}