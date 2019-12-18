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
struct mips_cpu_info {int cpu; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct mips_cpu_info const* mips_cpu_info_table ; 

__attribute__((used)) static const struct mips_cpu_info *
mips_cpu_info_from_arch (int arch)
{
  int i;

  for (i = 0; mips_cpu_info_table[i].name != NULL; i++)
    if (arch == mips_cpu_info_table[i].cpu)
      return (&mips_cpu_info_table[i]);

  return NULL;
}