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
 int /*<<< orphan*/  monitor_supply_register (int,char*) ; 

__attribute__((used)) static void
ppcbug_supply_register (char *regname, int regnamelen, char *val, int vallen)
{
  int regno = 0;

  if (regnamelen < 2 || regnamelen > 4)
    return;

  switch (regname[0])
    {
    case 'R':
      if (regname[1] < '0' || regname[1] > '9')
	return;
      if (regnamelen == 2)
	regno = regname[1] - '0';
      else if (regnamelen == 3 && regname[2] >= '0' && regname[2] <= '9')
	regno = (regname[1] - '0') * 10 + (regname[2] - '0');
      else
	return;
      break;
    case 'F':
      if (regname[1] != 'R' || regname[2] < '0' || regname[2] > '9')
	return;
      if (regnamelen == 3)
	regno = 32 + regname[2] - '0';
      else if (regnamelen == 4 && regname[3] >= '0' && regname[3] <= '9')
	regno = 32 + (regname[2] - '0') * 10 + (regname[3] - '0');
      else
	return;
      break;
    case 'I':
      if (regnamelen != 2 || regname[1] != 'P')
	return;
      regno = 64;
      break;
    case 'M':
      if (regnamelen != 3 || regname[1] != 'S' || regname[2] != 'R')
	return;
      regno = 65;
      break;
    case 'C':
      if (regnamelen != 2 || regname[1] != 'R')
	return;
      regno = 66;
      break;
    case 'S':
      if (regnamelen != 4 || regname[1] != 'P' || regname[2] != 'R')
	return;
      else if (regname[3] == '8')
	regno = 67;
      else if (regname[3] == '9')
	regno = 68;
      else if (regname[3] == '1')
	regno = 69;
      else if (regname[3] == '0')
	regno = 70;
      else
	return;
      break;
    default:
      return;
    }

  monitor_supply_register (regno, val);
}