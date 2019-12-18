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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int e_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_NOTE_SECTION ; 
 int EF_ARM_MAVERICK_FLOAT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_arch_arm ; 
 unsigned int bfd_arm_get_mach_from_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int bfd_mach_arm_ep9312 ; 
 unsigned int bfd_mach_arm_unknown ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_object_p (bfd *abfd)
{
  unsigned int mach;

  mach = bfd_arm_get_mach_from_notes (abfd, ARM_NOTE_SECTION);

  if (mach != bfd_mach_arm_unknown)
    bfd_default_set_arch_mach (abfd, bfd_arch_arm, mach);

  else if (elf_elfheader (abfd)->e_flags & EF_ARM_MAVERICK_FLOAT)
    bfd_default_set_arch_mach (abfd, bfd_arch_arm, bfd_mach_arm_ep9312);

  else
    bfd_default_set_arch_mach (abfd, bfd_arch_arm, mach);

  return TRUE;
}