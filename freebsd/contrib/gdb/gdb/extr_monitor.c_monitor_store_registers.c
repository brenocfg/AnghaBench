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
 int NUM_REGS ; 
 int /*<<< orphan*/  monitor_store_register (int) ; 

__attribute__((used)) static void
monitor_store_registers (int regno)
{
  if (regno >= 0)
    {
      monitor_store_register (regno);
      return;
    }

  for (regno = 0; regno < NUM_REGS; regno++)
    monitor_store_register (regno);
}