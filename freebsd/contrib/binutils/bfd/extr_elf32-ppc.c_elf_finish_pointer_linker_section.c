#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  def_regular; } ;
struct ppc_elf_link_hash_entry {TYPE_4__* linker_section_pointer; TYPE_1__ elf; } ;
struct elf_link_hash_entry {int dummy; } ;
struct TYPE_14__ {char* name; TYPE_2__* section; } ;
typedef  TYPE_3__ elf_linker_section_t ;
struct TYPE_15__ {int offset; int addend; } ;
typedef  TYPE_4__ elf_linker_section_pointers_t ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_13__ {int output_offset; scalar_t__ contents; int /*<<< orphan*/  owner; } ;
typedef  TYPE_5__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_4__* elf_find_pointer_linker_section (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_4__** elf_local_ptr_offsets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,long,long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bfd_vma
elf_finish_pointer_linker_section (bfd *input_bfd,
				   elf_linker_section_t *lsect,
				   struct elf_link_hash_entry *h,
				   bfd_vma relocation,
				   const Elf_Internal_Rela *rel)
{
  elf_linker_section_pointers_t *linker_section_ptr;

  BFD_ASSERT (lsect != NULL);

  if (h != NULL)
    {
      /* Handle global symbol.  */
      struct ppc_elf_link_hash_entry *eh;

      eh = (struct ppc_elf_link_hash_entry *) h;
      BFD_ASSERT (eh->elf.def_regular);
      linker_section_ptr = eh->linker_section_pointer;
    }
  else
    {
      /* Handle local symbol.  */
      unsigned long r_symndx = ELF32_R_SYM (rel->r_info);

      BFD_ASSERT (elf_local_ptr_offsets (input_bfd) != NULL);
      linker_section_ptr = elf_local_ptr_offsets (input_bfd)[r_symndx];
    }

  linker_section_ptr = elf_find_pointer_linker_section (linker_section_ptr,
							rel->r_addend,
							lsect);
  BFD_ASSERT (linker_section_ptr != NULL);

  /* Offset will always be a multiple of four, so use the bottom bit
     as a "written" flag.  */
  if ((linker_section_ptr->offset & 1) == 0)
    {
      bfd_put_32 (lsect->section->owner,
		  relocation + linker_section_ptr->addend,
		  lsect->section->contents + linker_section_ptr->offset);
      linker_section_ptr->offset += 1;
    }

  relocation = (lsect->section->output_offset
		+ linker_section_ptr->offset - 1
		- 0x8000);

#ifdef DEBUG
  fprintf (stderr,
	   "Finish pointer in linker section %s, offset = %ld (0x%lx)\n",
	   lsect->name, (long) relocation, (long) relocation);
#endif

  /* Subtract out the addend, because it will get added back in by the normal
     processing.  */
  return relocation - linker_section_ptr->addend;
}