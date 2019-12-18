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
 int FP0_REGNUM ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  fetch_register (int) ; 
 int /*<<< orphan*/  i387_supply_fsave (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npx ; 

__attribute__((used)) static void
go32_fetch_registers (int regno)
{
  if (regno >= 0)
    fetch_register (regno);
  else
    {
      for (regno = 0; regno < FP0_REGNUM; regno++)
	fetch_register (regno);
      i387_supply_fsave (current_regcache, -1, &npx);
    }
}