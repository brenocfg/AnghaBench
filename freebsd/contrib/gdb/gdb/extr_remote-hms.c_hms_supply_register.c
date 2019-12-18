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
 int CCR_REGNUM ; 
 int PC_REGNUM ; 
 char* monitor_supply_register (int,char*) ; 

__attribute__((used)) static void
hms_supply_register (char *regname, int regnamelen, char *val, int vallen)
{
  int regno;

  if (regnamelen != 2)
    return;
  if (regname[0] != 'P')
    return;
  /* We scan off all the registers in one go */

  val = monitor_supply_register (PC_REGNUM, val);
  /* Skip the ccr string */
  while (*val != '=' && *val)
    val++;

  val = monitor_supply_register (CCR_REGNUM, val + 1);

  /* Skip up to rest of regs */
  while (*val != '=' && *val)
    val++;

  for (regno = 0; regno < 7; regno++)
    {
      val = monitor_supply_register (regno, val + 1);
    }
}