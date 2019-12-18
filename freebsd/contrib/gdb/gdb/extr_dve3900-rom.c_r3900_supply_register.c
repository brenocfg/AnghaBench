#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int regno; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  monitor_supply_register (int,char*) ; 
 TYPE_1__* reg_table ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
r3900_supply_register (char *regname, int regnamelen, char *val, int vallen)
{
  int regno = -1;
  int i;
  char valbuf[10];
  char *p;

  /* Perform some sanity checks on the register name and value.  */
  if (regnamelen < 2 || regnamelen > 7 || vallen != 9)
    return;

  /* Look up the register name.  */
  for (i = 0; reg_table[i].name != NULL; i++)
    {
      int rlen = strlen (reg_table[i].name);
      if (rlen == regnamelen && strncmp (regname, reg_table[i].name, rlen) == 0)
	{
	  regno = reg_table[i].regno;
	  break;
	}
    }
  if (regno == -1)
    return;

  /* Copy the hex value to a buffer and eliminate the embedded space. */
  for (i = 0, p = valbuf; i < vallen; i++)
    if (val[i] != ' ')
      *p++ = val[i];
  *p = '\0';

  monitor_supply_register (regno, valbuf);
}