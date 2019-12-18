#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {scalar_t__* e_ident; scalar_t__ e_shnum; scalar_t__ e_shstrndx; scalar_t__ e_shentsize; scalar_t__ e_phnum; scalar_t__ e_phentsize; scalar_t__ e_ehsize; int /*<<< orphan*/  e_machine; scalar_t__ e_flags; scalar_t__ e_shoff; scalar_t__ e_phoff; scalar_t__ e_entry; scalar_t__ e_version; int /*<<< orphan*/  e_type; } ;
struct TYPE_4__ {scalar_t__ sh_size; scalar_t__ sh_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEC ; 
 size_t EI_ABIVERSION ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 int EI_NIDENT ; 
 size_t EI_OSABI ; 
 size_t EI_VERSION ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 int EV_CURRENT ; 
 int EV_NONE ; 
 int /*<<< orphan*/  PREFIX_HEX ; 
 scalar_t__ SHN_HIRESERVE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ SHN_XINDEX ; 
 char* _ (char*) ; 
 scalar_t__ do_header ; 
 TYPE_3__ elf_header ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* get_data_encoding (int) ; 
 char* get_elf_class (int) ; 
 char* get_file_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_machine_flags (scalar_t__,int /*<<< orphan*/ ) ; 
 char* get_machine_name (int /*<<< orphan*/ ) ; 
 char* get_osabi_name (int) ; 
 int /*<<< orphan*/  print_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 TYPE_1__* section_headers ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
process_file_header (void)
{
  if (   elf_header.e_ident[EI_MAG0] != ELFMAG0
      || elf_header.e_ident[EI_MAG1] != ELFMAG1
      || elf_header.e_ident[EI_MAG2] != ELFMAG2
      || elf_header.e_ident[EI_MAG3] != ELFMAG3)
    {
      error
	(_("Not an ELF file - it has the wrong magic bytes at the start\n"));
      return 0;
    }

  if (do_header)
    {
      int i;

      printf (_("ELF Header:\n"));
      printf (_("  Magic:   "));
      for (i = 0; i < EI_NIDENT; i++)
	printf ("%2.2x ", elf_header.e_ident[i]);
      printf ("\n");
      printf (_("  Class:                             %s\n"),
	      get_elf_class (elf_header.e_ident[EI_CLASS]));
      printf (_("  Data:                              %s\n"),
	      get_data_encoding (elf_header.e_ident[EI_DATA]));
      printf (_("  Version:                           %d %s\n"),
	      elf_header.e_ident[EI_VERSION],
	      (elf_header.e_ident[EI_VERSION] == EV_CURRENT
	       ? "(current)"
	       : (elf_header.e_ident[EI_VERSION] != EV_NONE
		  ? "<unknown: %lx>"
		  : "")));
      printf (_("  OS/ABI:                            %s\n"),
	      get_osabi_name (elf_header.e_ident[EI_OSABI]));
      printf (_("  ABI Version:                       %d\n"),
	      elf_header.e_ident[EI_ABIVERSION]);
      printf (_("  Type:                              %s\n"),
	      get_file_type (elf_header.e_type));
      printf (_("  Machine:                           %s\n"),
	      get_machine_name (elf_header.e_machine));
      printf (_("  Version:                           0x%lx\n"),
	      (unsigned long) elf_header.e_version);

      printf (_("  Entry point address:               "));
      print_vma ((bfd_vma) elf_header.e_entry, PREFIX_HEX);
      printf (_("\n  Start of program headers:          "));
      print_vma ((bfd_vma) elf_header.e_phoff, DEC);
      printf (_(" (bytes into file)\n  Start of section headers:          "));
      print_vma ((bfd_vma) elf_header.e_shoff, DEC);
      printf (_(" (bytes into file)\n"));

      printf (_("  Flags:                             0x%lx%s\n"),
	      (unsigned long) elf_header.e_flags,
	      get_machine_flags (elf_header.e_flags, elf_header.e_machine));
      printf (_("  Size of this header:               %ld (bytes)\n"),
	      (long) elf_header.e_ehsize);
      printf (_("  Size of program headers:           %ld (bytes)\n"),
	      (long) elf_header.e_phentsize);
      printf (_("  Number of program headers:         %ld\n"),
	      (long) elf_header.e_phnum);
      printf (_("  Size of section headers:           %ld (bytes)\n"),
	      (long) elf_header.e_shentsize);
      printf (_("  Number of section headers:         %ld"),
	      (long) elf_header.e_shnum);
      if (section_headers != NULL && elf_header.e_shnum == 0)
	printf (" (%ld)", (long) section_headers[0].sh_size);
      putc ('\n', stdout);
      printf (_("  Section header string table index: %ld"),
	      (long) elf_header.e_shstrndx);
      if (section_headers != NULL && elf_header.e_shstrndx == SHN_XINDEX)
	printf (" (%ld)", (long) section_headers[0].sh_link);
      else if (elf_header.e_shstrndx != SHN_UNDEF
	       && (elf_header.e_shstrndx >= elf_header.e_shnum
		   || (elf_header.e_shstrndx >= SHN_LORESERVE
		       && elf_header.e_shstrndx <= SHN_HIRESERVE)))
	printf (" <corrupt: out of range>");
      putc ('\n', stdout);
    }

  if (section_headers != NULL)
    {
      if (elf_header.e_shnum == 0)
	elf_header.e_shnum = section_headers[0].sh_size;
      if (elf_header.e_shstrndx == SHN_XINDEX)
	elf_header.e_shstrndx = section_headers[0].sh_link;
      else if (elf_header.e_shstrndx != SHN_UNDEF
	       && (elf_header.e_shstrndx >= elf_header.e_shnum
		   || (elf_header.e_shstrndx >= SHN_LORESERVE
		       && elf_header.e_shstrndx <= SHN_HIRESERVE)))
	elf_header.e_shstrndx = SHN_UNDEF;
      free (section_headers);
      section_headers = NULL;
    }

  return 1;
}