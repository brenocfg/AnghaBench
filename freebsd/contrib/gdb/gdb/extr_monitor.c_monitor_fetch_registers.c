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
struct TYPE_3__ {scalar_t__ cmd; } ;
struct TYPE_4__ {TYPE_1__ getreg; } ;

/* Variables and functions */
 int NUM_REGS ; 
 TYPE_2__* current_monitor ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int /*<<< orphan*/  monitor_dump_regs () ; 
 int /*<<< orphan*/  monitor_fetch_register (int) ; 

__attribute__((used)) static void
monitor_fetch_registers (int regno)
{
  monitor_debug ("MON fetchregs\n");
  if (current_monitor->getreg.cmd)
    {
      if (regno >= 0)
	{
	  monitor_fetch_register (regno);
	  return;
	}

      for (regno = 0; regno < NUM_REGS; regno++)
	monitor_fetch_register (regno);
    }
  else
    {
      monitor_dump_regs ();
    }
}