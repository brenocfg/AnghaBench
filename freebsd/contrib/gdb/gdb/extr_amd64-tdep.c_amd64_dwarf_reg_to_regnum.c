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
 int* amd64_dwarf_regmap ; 
 int amd64_dwarf_regmap_len ; 
 int /*<<< orphan*/  warning (char*,int) ; 

__attribute__((used)) static int
amd64_dwarf_reg_to_regnum (int reg)
{
  int regnum = -1;

  if (reg >= 0 || reg < amd64_dwarf_regmap_len)
    regnum = amd64_dwarf_regmap[reg];

  if (regnum == -1)
    warning ("Unmapped DWARF Register #%d encountered\n", reg);

  return regnum;
}