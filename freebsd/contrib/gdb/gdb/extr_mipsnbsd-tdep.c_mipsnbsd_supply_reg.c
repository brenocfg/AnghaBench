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
 scalar_t__ CANNOT_FETCH_REGISTER (int) ; 
 int PC_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int mips_regsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

void
mipsnbsd_supply_reg (char *regs, int regno)
{
  int i;

  for (i = 0; i <= PC_REGNUM; i++)
    {
      if (regno == i || regno == -1)
	{
	  if (CANNOT_FETCH_REGISTER (i))
	    supply_register (i, NULL);
	  else
            supply_register (i, regs + (i * mips_regsize (current_gdbarch)));
        }
    }
}