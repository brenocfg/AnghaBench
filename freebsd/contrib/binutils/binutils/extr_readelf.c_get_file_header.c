#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ehdr64 ;
typedef  int /*<<< orphan*/  ehdr32 ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_6__ {int* e_ident; scalar_t__ e_type; void* e_shoff; void* e_shstrndx; void* e_shnum; void* e_shentsize; void* e_phnum; void* e_phentsize; void* e_ehsize; void* e_flags; void* e_phoff; void* e_entry; void* e_version; void* e_machine; } ;
struct TYPE_5__ {int* e_type; int* e_machine; int* e_version; int* e_entry; int* e_phoff; int* e_shoff; int* e_flags; int* e_ehsize; int* e_phentsize; int* e_phnum; int* e_shentsize; int* e_shnum; int* e_shstrndx; } ;
struct TYPE_4__ {int* e_type; int* e_machine; int* e_version; int* e_entry; int* e_phoff; int* e_shoff; int* e_flags; int* e_ehsize; int* e_phentsize; int* e_phnum; int* e_shentsize; int* e_shnum; int* e_shstrndx; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf64_External_Ehdr ;
typedef  TYPE_2__ Elf32_External_Ehdr ;

/* Variables and functions */
 void* BYTE_GET (int*) ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 scalar_t__ EI_NIDENT ; 
 int ELFCLASS64 ; 
#define  ELFDATA2LSB 130 
#define  ELFDATA2MSB 129 
#define  ELFDATANONE 128 
 scalar_t__ ET_REL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  byte_get ; 
 int /*<<< orphan*/  byte_get_big_endian ; 
 int /*<<< orphan*/  byte_get_little_endian ; 
 int /*<<< orphan*/  byte_put ; 
 int /*<<< orphan*/  byte_put_big_endian ; 
 int /*<<< orphan*/  byte_put_little_endian ; 
 TYPE_3__ elf_header ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int fread (int*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_32bit_section_headers (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_64bit_section_headers (int /*<<< orphan*/ *,int) ; 
 int is_32bit_elf ; 
 int is_relocatable ; 

__attribute__((used)) static int
get_file_header (FILE *file)
{
  /* Read in the identity array.  */
  if (fread (elf_header.e_ident, EI_NIDENT, 1, file) != 1)
    return 0;

  /* Determine how to read the rest of the header.  */
  switch (elf_header.e_ident[EI_DATA])
    {
    default: /* fall through */
    case ELFDATANONE: /* fall through */
    case ELFDATA2LSB:
      byte_get = byte_get_little_endian;
      byte_put = byte_put_little_endian;
      break;
    case ELFDATA2MSB:
      byte_get = byte_get_big_endian;
      byte_put = byte_put_big_endian;
      break;
    }

  /* For now we only support 32 bit and 64 bit ELF files.  */
  is_32bit_elf = (elf_header.e_ident[EI_CLASS] != ELFCLASS64);

  /* Read in the rest of the header.  */
  if (is_32bit_elf)
    {
      Elf32_External_Ehdr ehdr32;

      if (fread (ehdr32.e_type, sizeof (ehdr32) - EI_NIDENT, 1, file) != 1)
	return 0;

      elf_header.e_type      = BYTE_GET (ehdr32.e_type);
      elf_header.e_machine   = BYTE_GET (ehdr32.e_machine);
      elf_header.e_version   = BYTE_GET (ehdr32.e_version);
      elf_header.e_entry     = BYTE_GET (ehdr32.e_entry);
      elf_header.e_phoff     = BYTE_GET (ehdr32.e_phoff);
      elf_header.e_shoff     = BYTE_GET (ehdr32.e_shoff);
      elf_header.e_flags     = BYTE_GET (ehdr32.e_flags);
      elf_header.e_ehsize    = BYTE_GET (ehdr32.e_ehsize);
      elf_header.e_phentsize = BYTE_GET (ehdr32.e_phentsize);
      elf_header.e_phnum     = BYTE_GET (ehdr32.e_phnum);
      elf_header.e_shentsize = BYTE_GET (ehdr32.e_shentsize);
      elf_header.e_shnum     = BYTE_GET (ehdr32.e_shnum);
      elf_header.e_shstrndx  = BYTE_GET (ehdr32.e_shstrndx);
    }
  else
    {
      Elf64_External_Ehdr ehdr64;

      /* If we have been compiled with sizeof (bfd_vma) == 4, then
	 we will not be able to cope with the 64bit data found in
	 64 ELF files.  Detect this now and abort before we start
	 overwriting things.  */
      if (sizeof (bfd_vma) < 8)
	{
	  error (_("This instance of readelf has been built without support for a\n\
64 bit data type and so it cannot read 64 bit ELF files.\n"));
	  return 0;
	}

      if (fread (ehdr64.e_type, sizeof (ehdr64) - EI_NIDENT, 1, file) != 1)
	return 0;

      elf_header.e_type      = BYTE_GET (ehdr64.e_type);
      elf_header.e_machine   = BYTE_GET (ehdr64.e_machine);
      elf_header.e_version   = BYTE_GET (ehdr64.e_version);
      elf_header.e_entry     = BYTE_GET (ehdr64.e_entry);
      elf_header.e_phoff     = BYTE_GET (ehdr64.e_phoff);
      elf_header.e_shoff     = BYTE_GET (ehdr64.e_shoff);
      elf_header.e_flags     = BYTE_GET (ehdr64.e_flags);
      elf_header.e_ehsize    = BYTE_GET (ehdr64.e_ehsize);
      elf_header.e_phentsize = BYTE_GET (ehdr64.e_phentsize);
      elf_header.e_phnum     = BYTE_GET (ehdr64.e_phnum);
      elf_header.e_shentsize = BYTE_GET (ehdr64.e_shentsize);
      elf_header.e_shnum     = BYTE_GET (ehdr64.e_shnum);
      elf_header.e_shstrndx  = BYTE_GET (ehdr64.e_shstrndx);
    }

  if (elf_header.e_shoff)
    {
      /* There may be some extensions in the first section header.  Don't
	 bomb if we can't read it.  */
      if (is_32bit_elf)
	get_32bit_section_headers (file, 1);
      else
	get_64bit_section_headers (file, 1);
    }

  is_relocatable = elf_header.e_type == ET_REL;

  return 1;
}