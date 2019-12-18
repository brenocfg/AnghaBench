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
struct mips_cpu_info {scalar_t__ name; int isa; } ;

/* Variables and functions */
 struct mips_cpu_info* mips_cpu_info_table ; 

__attribute__((used)) static const struct mips_cpu_info *
mips_cpu_info_from_isa (int isa)
{
  const struct mips_cpu_info *p;

  for (p = mips_cpu_info_table; p->name != 0; p++)
    if (p->isa == isa)
      return p;

  return 0;
}