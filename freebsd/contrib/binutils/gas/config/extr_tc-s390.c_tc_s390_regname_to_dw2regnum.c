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
 int /*<<< orphan*/  REG_NAME_CNT ; 
 int /*<<< orphan*/  pre_defined_registers ; 
 int reg_name_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
tc_s390_regname_to_dw2regnum (char *regname)
{
  int regnum = -1;

  if (regname[0] != 'c' && regname[0] != 'a')
    {
      regnum = reg_name_search (pre_defined_registers, REG_NAME_CNT, regname);
      if (regname[0] == 'f' && regnum != -1)
        regnum += 16;
    }
  else if (strcmp (regname, "ap") == 0)
    regnum = 32;
  else if (strcmp (regname, "cc") == 0)
    regnum = 33;
  return regnum;
}