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
struct gdbarch_tdep {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  int ULONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  I387_FSTAT_REGNUM ; 
 int /*<<< orphan*/  I387_FTAG_REGNUM ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  regcache_raw_read_unsigned (struct regcache*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regcache_raw_write_unsigned (struct regcache*,int /*<<< orphan*/ ,int) ; 

void
i387_return_value (struct gdbarch *gdbarch, struct regcache *regcache)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  ULONGEST fstat;

  /* Define I387_ST0_REGNUM such that we use the proper
     definitions for the architecture.  */
#define I387_ST0_REGNUM tdep->st0_regnum

  /* Set the top of the floating-point register stack to 7.  The
     actual value doesn't really matter, but 7 is what a normal
     function return would end up with if the program started out with
     a freshly initialized FPU.  */
  regcache_raw_read_unsigned (regcache, I387_FSTAT_REGNUM, &fstat);
  fstat |= (7 << 11);
  regcache_raw_write_unsigned (regcache, I387_FSTAT_REGNUM, fstat);

  /* Mark %st(1) through %st(7) as empty.  Since we set the top of the
     floating-point register stack to 7, the appropriate value for the
     tag word is 0x3fff.  */
  regcache_raw_write_unsigned (regcache, I387_FTAG_REGNUM, 0x3fff);

#undef I387_ST0_REGNUM
}