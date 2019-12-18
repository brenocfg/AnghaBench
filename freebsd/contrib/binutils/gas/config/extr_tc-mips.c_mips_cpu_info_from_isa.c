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
struct mips_cpu_info {int flags; int isa; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int MIPS_CPU_IS_ISA ; 
 struct mips_cpu_info const* mips_cpu_info_table ; 

__attribute__((used)) static const struct mips_cpu_info *
mips_cpu_info_from_isa (int isa)
{
  int i;

  for (i = 0; mips_cpu_info_table[i].name != NULL; i++)
    if ((mips_cpu_info_table[i].flags & MIPS_CPU_IS_ISA)
	&& isa == mips_cpu_info_table[i].isa)
      return (&mips_cpu_info_table[i]);

  return NULL;
}