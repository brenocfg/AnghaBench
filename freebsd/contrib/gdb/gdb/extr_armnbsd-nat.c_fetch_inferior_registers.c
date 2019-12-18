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
 int ARM_F0_REGNUM ; 
 int ARM_FPS_REGNUM ; 
 int /*<<< orphan*/  fetch_fp_register (int) ; 
 int /*<<< orphan*/  fetch_fp_regs () ; 
 int /*<<< orphan*/  fetch_register (int) ; 
 int /*<<< orphan*/  fetch_regs () ; 

void
fetch_inferior_registers (int regno)
{
  if (regno >= 0)
    {
      if (regno < ARM_F0_REGNUM || regno > ARM_FPS_REGNUM)
	fetch_register (regno);
      else
	fetch_fp_register (regno);
    }
  else
    {
      fetch_regs ();
      fetch_fp_regs ();
    }
}