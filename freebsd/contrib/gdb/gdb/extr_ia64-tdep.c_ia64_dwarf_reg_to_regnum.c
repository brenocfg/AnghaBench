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
 int IA64_GR127_REGNUM ; 
 int IA64_GR32_REGNUM ; 
 int V32_REGNUM ; 

__attribute__((used)) static int
ia64_dwarf_reg_to_regnum (int reg)
{
  if (reg >= IA64_GR32_REGNUM && reg <= IA64_GR127_REGNUM)
    return V32_REGNUM + (reg - IA64_GR32_REGNUM);
  return reg;
}