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
typedef  enum gdb_osabi { ____Placeholder_gdb_osabi } gdb_osabi ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {unsigned int* e_ident; } ;

/* Variables and functions */
 size_t EI_OSABI ; 
#define  ELFOSABI_FREEBSD 134 
#define  ELFOSABI_HPUX 133 
#define  ELFOSABI_HURD 132 
#define  ELFOSABI_LINUX 131 
#define  ELFOSABI_NETBSD 130 
#define  ELFOSABI_NONE 129 
#define  ELFOSABI_SOLARIS 128 
 int GDB_OSABI_FREEBSD_ELF ; 
 int GDB_OSABI_HPUX_ELF ; 
 int GDB_OSABI_HURD ; 
 int GDB_OSABI_LINUX ; 
 int GDB_OSABI_NETBSD_ELF ; 
 int GDB_OSABI_SOLARIS ; 
 int GDB_OSABI_UNKNOWN ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_elf_osabi_sniff_abi_tag_sections ; 
 scalar_t__ strcmp (unsigned int*,char*) ; 

__attribute__((used)) static enum gdb_osabi
generic_elf_osabi_sniffer (bfd *abfd)
{
  unsigned int elfosabi;
  enum gdb_osabi osabi = GDB_OSABI_UNKNOWN;

  elfosabi = elf_elfheader (abfd)->e_ident[EI_OSABI];

  switch (elfosabi)
    {
    case ELFOSABI_NONE:
      /* When elfosabi is ELFOSABI_NONE (0), then the ELF structures in the
         file are conforming to the base specification for that machine
	 (there are no OS-specific extensions).  In order to determine the
	 real OS in use we must look for OS notes that have been added.  */
      bfd_map_over_sections (abfd,
			     generic_elf_osabi_sniff_abi_tag_sections,
			     &osabi);
      break;

    case ELFOSABI_FREEBSD:
      osabi = GDB_OSABI_FREEBSD_ELF;
      break;

    case ELFOSABI_NETBSD:
      osabi = GDB_OSABI_NETBSD_ELF;
      break;

    case ELFOSABI_LINUX:
      osabi = GDB_OSABI_LINUX;
      break;

    case ELFOSABI_HURD:
      osabi = GDB_OSABI_HURD;
      break;

    case ELFOSABI_SOLARIS:
      osabi = GDB_OSABI_SOLARIS;
      break;

    case ELFOSABI_HPUX:
      osabi = GDB_OSABI_HPUX_ELF;
      break;
    }

  if (osabi == GDB_OSABI_UNKNOWN)
    {
      /* The FreeBSD folks have been naughty; they stored the string
         "FreeBSD" in the padding of the e_ident field of the ELF
         header to "brand" their ELF binaries in FreeBSD 3.x.  */
      if (strcmp (&elf_elfheader (abfd)->e_ident[8], "FreeBSD") == 0)
	osabi = GDB_OSABI_FREEBSD_ELF;
    }

  return osabi;
}