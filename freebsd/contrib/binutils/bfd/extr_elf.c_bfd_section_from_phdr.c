#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_section_from_phdr ) (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ;} ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int p_type; int /*<<< orphan*/  p_filesz; int /*<<< orphan*/  p_offset; } ;
typedef  TYPE_1__ Elf_Internal_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  PT_DYNAMIC 137 
#define  PT_GNU_EH_FRAME 136 
#define  PT_GNU_RELRO 135 
#define  PT_GNU_STACK 134 
#define  PT_INTERP 133 
#define  PT_LOAD 132 
#define  PT_NOTE 131 
#define  PT_NULL 130 
#define  PT_PHDR 129 
#define  PT_SHLIB 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_make_section_from_phdr (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  elfcore_read_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 

bfd_boolean
bfd_section_from_phdr (bfd *abfd, Elf_Internal_Phdr *hdr, int index)
{
  const struct elf_backend_data *bed;

  switch (hdr->p_type)
    {
    case PT_NULL:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "null");

    case PT_LOAD:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "load");

    case PT_DYNAMIC:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "dynamic");

    case PT_INTERP:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "interp");

    case PT_NOTE:
      if (! _bfd_elf_make_section_from_phdr (abfd, hdr, index, "note"))
	return FALSE;
      if (! elfcore_read_notes (abfd, hdr->p_offset, hdr->p_filesz))
	return FALSE;
      return TRUE;

    case PT_SHLIB:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "shlib");

    case PT_PHDR:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "phdr");

    case PT_GNU_EH_FRAME:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index,
					      "eh_frame_hdr");

    case PT_GNU_STACK:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "stack");

    case PT_GNU_RELRO:
      return _bfd_elf_make_section_from_phdr (abfd, hdr, index, "relro");

    default:
      /* Check for any processor-specific program segment types.  */
      bed = get_elf_backend_data (abfd);
      return bed->elf_backend_section_from_phdr (abfd, hdr, index, "proc");
    }
}