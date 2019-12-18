#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  st_space; } ;
struct TYPE_4__ {int /*<<< orphan*/  u_fpstate; } ;
struct user {TYPE_1__ i387; TYPE_2__ u_fps; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int FP0_REGNUM ; 
 int KSTKSZ ; 
 int SS ; 
 scalar_t__ i386_fp_regnum_p (int) ; 
 int* regmap ; 

CORE_ADDR
register_u_addr (CORE_ADDR blockend, int regnum)
{
  struct user u;
  CORE_ADDR fpstate;

  if (i386_fp_regnum_p (regnum))
    {
#ifdef KSTKSZ			/* SCO, and others?  */
      blockend += 4 * (SS + 1) - KSTKSZ;
      fpstate = blockend + ((char *) &u.u_fps.u_fpstate - (char *) &u);
      return (fpstate + 0x1c + 10 * (regnum - FP0_REGNUM));
#else
      fpstate = blockend + ((char *) &u.i387.st_space - (char *) &u);
      return (fpstate + 10 * (regnum - FP0_REGNUM));
#endif
    }

  return (blockend + 4 * regmap[regnum]);
}