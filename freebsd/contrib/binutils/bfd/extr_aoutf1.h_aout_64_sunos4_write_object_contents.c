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
struct internal_exec {int dummy; } ;
struct external_exec {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  exec_hdr_flags; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  M_386 ; 
 int /*<<< orphan*/  M_68010 ; 
 int /*<<< orphan*/  M_68020 ; 
 int /*<<< orphan*/  M_SPARC ; 
 int /*<<< orphan*/  M_SPARCLET ; 
 int /*<<< orphan*/  M_SPARCLITE_LE ; 
 int /*<<< orphan*/  M_UNKNOWN ; 
 int /*<<< orphan*/  N_SET_DYNAMIC (struct internal_exec,long) ; 
 int /*<<< orphan*/  N_SET_FLAGS (struct internal_exec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_SET_MACHTYPE (struct internal_exec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_HEADERS (int /*<<< orphan*/ *,struct internal_exec*) ; 
 TYPE_1__* aout_backend_info (int /*<<< orphan*/ *) ; 
#define  bfd_arch_i386 135 
#define  bfd_arch_m68k 134 
#define  bfd_arch_sparc 133 
 int bfd_get_arch (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_mach (int /*<<< orphan*/ *) ; 
#define  bfd_mach_m68000 132 
#define  bfd_mach_m68010 131 
#define  bfd_mach_m68020 130 
#define  bfd_mach_sparc_sparclet 129 
#define  bfd_mach_sparc_sparclite_le 128 
 int /*<<< orphan*/  choose_reloc_size (int /*<<< orphan*/ *) ; 
 struct internal_exec* exec_hdr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
sunos_write_object_contents (bfd *abfd)
{
  struct external_exec exec_bytes;
  struct internal_exec *execp = exec_hdr (abfd);

  /* Magic number, maestro, please!  */
  switch (bfd_get_arch (abfd))
    {
    case bfd_arch_m68k:
      switch (bfd_get_mach (abfd))
	{
	case bfd_mach_m68000:
	  N_SET_MACHTYPE (*execp, M_UNKNOWN);
	  break;
	case bfd_mach_m68010:
	  N_SET_MACHTYPE (*execp, M_68010);
	  break;
	default:
	case bfd_mach_m68020:
	  N_SET_MACHTYPE (*execp, M_68020);
	  break;
	}
      break;
    case bfd_arch_sparc:
      switch (bfd_get_mach (abfd))
	{
	case bfd_mach_sparc_sparclet:
	  N_SET_MACHTYPE (*execp, M_SPARCLET);
	  break;
	case bfd_mach_sparc_sparclite_le:
	  N_SET_MACHTYPE (*execp, M_SPARCLITE_LE);
	  break;
	default:
	  N_SET_MACHTYPE (*execp, M_SPARC);
	  break;
	}
      break;
    case bfd_arch_i386:
      N_SET_MACHTYPE (*execp, M_386);
      break;
    default:
      N_SET_MACHTYPE (*execp, M_UNKNOWN);
    }

  choose_reloc_size (abfd);

  N_SET_FLAGS (*execp, aout_backend_info (abfd)->exec_hdr_flags);

  N_SET_DYNAMIC (*execp, (long)(bfd_get_file_flags (abfd) & DYNAMIC));

  WRITE_HEADERS (abfd, execp);

  return TRUE;
}