#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {int flags; scalar_t__ sec_info_type; scalar_t__ output_offset; TYPE_1__* output_section; struct TYPE_12__* kept_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_15__ {int /*<<< orphan*/  sec_info; } ;
struct TYPE_14__ {scalar_t__ r_addend; } ;
struct TYPE_13__ {scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_11__ {scalar_t__ vma; } ;
typedef  TYPE_3__ Elf_Internal_Sym ;
typedef  TYPE_4__ Elf_Internal_Rela ;

/* Variables and functions */
 scalar_t__ ELF_INFO_TYPE_MERGE ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int SEC_EXCLUDE ; 
 int SEC_MERGE ; 
 scalar_t__ STT_SECTION ; 
 scalar_t__ _bfd_merged_section_offset (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* elf_section_data (TYPE_2__*) ; 

bfd_vma
_bfd_elf_rela_local_sym (bfd *abfd,
			 Elf_Internal_Sym *sym,
			 asection **psec,
			 Elf_Internal_Rela *rel)
{
  asection *sec = *psec;
  bfd_vma relocation;

  relocation = (sec->output_section->vma
		+ sec->output_offset
		+ sym->st_value);
  if ((sec->flags & SEC_MERGE)
      && ELF_ST_TYPE (sym->st_info) == STT_SECTION
      && sec->sec_info_type == ELF_INFO_TYPE_MERGE)
    {
      rel->r_addend =
	_bfd_merged_section_offset (abfd, psec,
				    elf_section_data (sec)->sec_info,
				    sym->st_value + rel->r_addend);
      if (sec != *psec)
	{
	  /* If we have changed the section, and our original section is
	     marked with SEC_EXCLUDE, it means that the original
	     SEC_MERGE section has been completely subsumed in some
	     other SEC_MERGE section.  In this case, we need to leave
	     some info around for --emit-relocs.  */
	  if ((sec->flags & SEC_EXCLUDE) != 0)
	    sec->kept_section = *psec;
	  sec = *psec;
	}
      rel->r_addend -= relocation;
      rel->r_addend += sec->output_section->vma + sec->output_offset;
    }
  return relocation;
}