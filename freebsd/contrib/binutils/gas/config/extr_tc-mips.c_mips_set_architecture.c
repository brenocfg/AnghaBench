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
struct mips_cpu_info {int /*<<< orphan*/  isa; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  isa; int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_mips_arch ; 
 TYPE_1__ mips_opts ; 

__attribute__((used)) static void
mips_set_architecture (const struct mips_cpu_info *info)
{
  if (info != 0)
    {
      file_mips_arch = info->cpu;
      mips_opts.arch = info->cpu;
      mips_opts.isa = info->isa;
    }
}