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
 int /*<<< orphan*/  M68K_A0_REGNUM ; 
 int /*<<< orphan*/  M68K_D0_REGNUM ; 
 int PC_REGNUM ; 
 int PS_REGNUM ; 
 int /*<<< orphan*/  monitor_supply_register (int,char*) ; 

__attribute__((used)) static void
cpu32bug_supply_register (char *regname, int regnamelen, char *val, int vallen)
{
  int regno;

  if (regnamelen != 2)
    return;

  switch (regname[0])
    {
    case 'S':
      if (regname[1] != 'R')
	return;
      regno = PS_REGNUM;
      break;
    case 'P':
      if (regname[1] != 'C')
	return;
      regno = PC_REGNUM;
      break;
    case 'D':
      if (regname[1] < '0' || regname[1] > '7')
	return;
      regno = regname[1] - '0' + M68K_D0_REGNUM;
      break;
    case 'A':
      if (regname[1] < '0' || regname[1] > '7')
	return;
      regno = regname[1] - '0' + M68K_A0_REGNUM;
      break;
    default:
      return;
    }

  monitor_supply_register (regno, val);
}