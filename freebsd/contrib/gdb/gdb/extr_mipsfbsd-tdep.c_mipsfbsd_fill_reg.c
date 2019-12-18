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

/* Variables and functions */
 int /*<<< orphan*/  CANNOT_STORE_REGISTER (int) ; 
 int PC_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int mips_regsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 

void
mipsfbsd_fill_reg (char *regs, int regno)
{
  int i;

  for (i = 0; i <= PC_REGNUM; i++)
    if ((regno == i || regno == -1) && ! CANNOT_STORE_REGISTER (i))
      regcache_collect (i, regs + (i * mips_regsize (current_gdbarch)));
}