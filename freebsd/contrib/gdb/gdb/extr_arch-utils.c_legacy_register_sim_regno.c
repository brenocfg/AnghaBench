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
 int LEGACY_SIM_REGNO_IGNORE ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

int
legacy_register_sim_regno (int regnum)
{
  /* Only makes sense to supply raw registers.  */
  gdb_assert (regnum >= 0 && regnum < NUM_REGS);
  /* NOTE: cagney/2002-05-13: The old code did it this way and it is
     suspected that some GDB/SIM combinations may rely on this
     behavour.  The default should be one2one_register_sim_regno
     (below).  */
  if (REGISTER_NAME (regnum) != NULL
      && REGISTER_NAME (regnum)[0] != '\0')
    return regnum;
  else
    return LEGACY_SIM_REGNO_IGNORE;
}