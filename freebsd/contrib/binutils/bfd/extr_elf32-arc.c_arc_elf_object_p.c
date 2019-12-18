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
struct TYPE_2__ {scalar_t__ e_machine; unsigned long e_flags; } ;

/* Variables and functions */
 unsigned long EF_ARC_MACH ; 
 scalar_t__ EM_ARC ; 
#define  E_ARC_MACH_ARC5 131 
#define  E_ARC_MACH_ARC6 130 
#define  E_ARC_MACH_ARC7 129 
#define  E_ARC_MACH_ARC8 128 
 int /*<<< orphan*/  bfd_arch_arc ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int bfd_mach_arc_5 ; 
 unsigned int bfd_mach_arc_6 ; 
 unsigned int bfd_mach_arc_7 ; 
 unsigned int bfd_mach_arc_8 ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
arc_elf_object_p (bfd *abfd)
{
  unsigned int mach = bfd_mach_arc_6;

  if (elf_elfheader(abfd)->e_machine == EM_ARC)
    {
      unsigned long arch = elf_elfheader (abfd)->e_flags & EF_ARC_MACH;

      switch (arch)
	{
	case E_ARC_MACH_ARC5:
	  mach = bfd_mach_arc_5;
	  break;
	default:
	case E_ARC_MACH_ARC6:
	  mach = bfd_mach_arc_6;
	  break;
	case E_ARC_MACH_ARC7:
	  mach = bfd_mach_arc_7;
	  break;
	case E_ARC_MACH_ARC8:
	  mach = bfd_mach_arc_8;
	  break;
	}
    }
  return bfd_default_set_arch_mach (abfd, bfd_arch_arc, mach);
}