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
typedef  enum machine_type { ____Placeholder_machine_type } machine_type ;
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
#define  M_386 138 
#define  M_386_DYNIX 137 
#define  M_68010 136 
#define  M_68020 135 
#define  M_HP200 134 
#define  M_HP300 133 
#define  M_HPUX 132 
#define  M_SPARC 131 
#define  M_SPARCLET 130 
#define  M_SPARCLITE_LE 129 
#define  M_UNKNOWN 128 
 int bfd_arch_i386 ; 
 int bfd_arch_m68k ; 
 int bfd_arch_obscure ; 
 int bfd_arch_sparc ; 
 unsigned long bfd_mach_m68000 ; 
 unsigned long bfd_mach_m68010 ; 
 unsigned long bfd_mach_m68020 ; 
 unsigned long bfd_mach_sparc_sparclet ; 
 unsigned long bfd_mach_sparc_sparclite_le ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 

__attribute__((used)) static void
sunos_set_arch_mach (bfd *abfd, enum machine_type machtype)
{
  /* Determine the architecture and machine type of the object file.  */
  enum bfd_architecture arch;
  unsigned long machine;

  switch (machtype)
    {
    case M_UNKNOWN:
      /* Some Sun3s make magic numbers without cpu types in them, so
	 we'll default to the 68000.  */
      arch = bfd_arch_m68k;
      machine = bfd_mach_m68000;
      break;

    case M_68010:
    case M_HP200:
      arch = bfd_arch_m68k;
      machine = bfd_mach_m68010;
      break;

    case M_68020:
    case M_HP300:
      arch = bfd_arch_m68k;
      machine = bfd_mach_m68020;
      break;

    case M_SPARC:
      arch = bfd_arch_sparc;
      machine = 0;
      break;

    case M_SPARCLET:
      arch = bfd_arch_sparc;
      machine = bfd_mach_sparc_sparclet;
      break;

    case M_SPARCLITE_LE:
      arch = bfd_arch_sparc;
      machine = bfd_mach_sparc_sparclite_le;
      break;

    case M_386:
    case M_386_DYNIX:
      arch = bfd_arch_i386;
      machine = 0;
      break;

    case M_HPUX:
      arch = bfd_arch_m68k;
      machine = 0;
      break;

    default:
      arch = bfd_arch_obscure;
      machine = 0;
      break;
    }
  bfd_set_arch_mach (abfd, arch, machine);
}