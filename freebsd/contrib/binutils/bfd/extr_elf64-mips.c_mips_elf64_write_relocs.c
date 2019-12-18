#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_14__ {int flags; unsigned int reloc_count; TYPE_3__** orelocation; } ;
typedef  TYPE_2__ asection ;
struct TYPE_15__ {scalar_t__ address; TYPE_1__** sym_ptr_ptr; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_16__ {int sh_entsize; } ;
struct TYPE_13__ {scalar_t__ value; int /*<<< orphan*/  section; } ;
struct TYPE_12__ {TYPE_4__ rel_hdr; } ;
typedef  TYPE_4__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf64_Mips_External_Rela ;
typedef  int /*<<< orphan*/  Elf64_Mips_External_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 TYPE_10__* elf_section_data (TYPE_2__*) ; 
 int /*<<< orphan*/  mips_elf64_write_rel (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,int*,void*) ; 
 int /*<<< orphan*/  mips_elf64_write_rela (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,int*,void*) ; 

__attribute__((used)) static void
mips_elf64_write_relocs (bfd *abfd, asection *sec, void *data)
{
  bfd_boolean *failedp = data;
  int count;
  Elf_Internal_Shdr *rel_hdr;
  unsigned int idx;

  /* If we have already failed, don't do anything.  */
  if (*failedp)
    return;

  if ((sec->flags & SEC_RELOC) == 0)
    return;

  /* The linker backend writes the relocs out itself, and sets the
     reloc_count field to zero to inhibit writing them here.  Also,
     sometimes the SEC_RELOC flag gets set even when there aren't any
     relocs.  */
  if (sec->reloc_count == 0)
    return;

  /* We can combine up to three relocs that refer to the same address
     if the latter relocs have no associated symbol.  */
  count = 0;
  for (idx = 0; idx < sec->reloc_count; idx++)
    {
      bfd_vma addr;
      unsigned int i;

      ++count;

      addr = sec->orelocation[idx]->address;
      for (i = 0; i < 2; i++)
	{
	  arelent *r;

	  if (idx + 1 >= sec->reloc_count)
	    break;
	  r = sec->orelocation[idx + 1];
	  if (r->address != addr
	      || ! bfd_is_abs_section ((*r->sym_ptr_ptr)->section)
	      || (*r->sym_ptr_ptr)->value != 0)
	    break;

	  /* We can merge the reloc at IDX + 1 with the reloc at IDX.  */

	  ++idx;
	}
    }

  rel_hdr = &elf_section_data (sec)->rel_hdr;

  /* Do the actual relocation.  */

  if (rel_hdr->sh_entsize == sizeof(Elf64_Mips_External_Rel))
    mips_elf64_write_rel (abfd, sec, rel_hdr, &count, data);
  else if (rel_hdr->sh_entsize == sizeof(Elf64_Mips_External_Rela))
    mips_elf64_write_rela (abfd, sec, rel_hdr, &count, data);
  else
    BFD_ASSERT (0);
}