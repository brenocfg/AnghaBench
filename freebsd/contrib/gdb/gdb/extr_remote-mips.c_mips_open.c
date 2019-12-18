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
struct TYPE_2__ {scalar_t__ arch; int mach; } ;

/* Variables and functions */
 int /*<<< orphan*/  MON_IDT ; 
 TYPE_1__* TARGET_ARCHITECTURE ; 
 scalar_t__ bfd_arch_mips ; 
#define  bfd_mach_mips4100 132 
#define  bfd_mach_mips4300 131 
#define  bfd_mach_mips4600 130 
#define  bfd_mach_mips4650 129 
#define  bfd_mach_mips5000 128 
 int /*<<< orphan*/  common_open (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mips_ops ; 

__attribute__((used)) static void
mips_open (char *name, int from_tty)
{
  const char *monitor_prompt = NULL;
  if (TARGET_ARCHITECTURE != NULL
      && TARGET_ARCHITECTURE->arch == bfd_arch_mips)
    {
    switch (TARGET_ARCHITECTURE->mach)
      {
      case bfd_mach_mips4100:
      case bfd_mach_mips4300:
      case bfd_mach_mips4600:
      case bfd_mach_mips4650:
      case bfd_mach_mips5000:
	monitor_prompt = "<RISQ> ";
	break;
      }
    }
  if (monitor_prompt == NULL)
    monitor_prompt = "<IDT>";
  common_open (&mips_ops, name, from_tty, MON_IDT, monitor_prompt);
}