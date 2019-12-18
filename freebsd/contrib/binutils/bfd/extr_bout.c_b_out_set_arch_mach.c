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
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_arch_i960 ; 
 int bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 
#define  bfd_mach_i960_ca 135 
#define  bfd_mach_i960_core 134 
#define  bfd_mach_i960_hx 133 
#define  bfd_mach_i960_jx 132 
#define  bfd_mach_i960_ka_sa 131 
#define  bfd_mach_i960_kb_sb 130 
#define  bfd_mach_i960_mc 129 
#define  bfd_mach_i960_xa 128 

__attribute__((used)) static bfd_boolean
b_out_set_arch_mach (bfd *abfd,
		     enum bfd_architecture arch,
		     unsigned long machine)
{
  bfd_default_set_arch_mach (abfd, arch, machine);

  if (arch == bfd_arch_unknown)	/* Unknown machine arch is OK.  */
    return TRUE;

  if (arch == bfd_arch_i960)	/* i960 default is OK.  */
    switch (machine)
      {
      case bfd_mach_i960_core:
      case bfd_mach_i960_kb_sb:
      case bfd_mach_i960_mc:
      case bfd_mach_i960_xa:
      case bfd_mach_i960_ca:
      case bfd_mach_i960_ka_sa:
      case bfd_mach_i960_jx:
      case bfd_mach_i960_hx:
      case 0:
	return TRUE;
      default:
	return FALSE;
      }

  return FALSE;
}