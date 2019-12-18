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
struct mips_cpu_info {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  mips_tune ; 

__attribute__((used)) static void
mips_set_tune (const struct mips_cpu_info *info)
{
  if (info != 0)
    mips_tune = info->cpu;
}