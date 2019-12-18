#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fp_control_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANNOT_STORE_REGISTER (int) ; 
 int FP0_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int mips_regsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 

void
mipsfbsd_fill_fpreg (char *fpregs, int regno)
{
  int i;

  for (i = FP0_REGNUM; i <= mips_regnum (current_gdbarch)->fp_control_status;
       i++)
    if ((regno == i || regno == -1) && ! CANNOT_STORE_REGISTER (i))
      regcache_collect (i, 
	  fpregs + ((i - FP0_REGNUM) * mips_regsize (current_gdbarch)));
}