#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ sh_offset; } ;
struct bfd_elf_section_data {TYPE_2__* rel_hdr2; TYPE_2__ this_hdr; TYPE_2__ rel_hdr; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_8__ {int flags; scalar_t__ reloc_count; scalar_t__ rel_filepos; scalar_t__ size; int /*<<< orphan*/ * relocation; } ;
typedef  TYPE_1__ asection ;
typedef  int /*<<< orphan*/  arelent ;
typedef  TYPE_2__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int NUM_SHDR_ENTRIES (TYPE_2__*) ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_alloc (int /*<<< orphan*/ *,int) ; 
 struct bfd_elf_section_data* elf_section_data (TYPE_1__*) ; 
 int /*<<< orphan*/  mips_elf64_slurp_one_reloc_table (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
mips_elf64_slurp_reloc_table (bfd *abfd, asection *asect,
			      asymbol **symbols, bfd_boolean dynamic)
{
  struct bfd_elf_section_data * const d = elf_section_data (asect);
  Elf_Internal_Shdr *rel_hdr;
  Elf_Internal_Shdr *rel_hdr2;
  bfd_size_type reloc_count;
  bfd_size_type reloc_count2;
  arelent *relents;
  bfd_size_type amt;

  if (asect->relocation != NULL)
    return TRUE;

  if (! dynamic)
    {
      if ((asect->flags & SEC_RELOC) == 0
	  || asect->reloc_count == 0)
	return TRUE;

      rel_hdr = &d->rel_hdr;
      reloc_count = NUM_SHDR_ENTRIES (rel_hdr);
      rel_hdr2 = d->rel_hdr2;
      reloc_count2 = (rel_hdr2 ? NUM_SHDR_ENTRIES (rel_hdr2) : 0);

      BFD_ASSERT (asect->reloc_count == reloc_count + reloc_count2);
      BFD_ASSERT (asect->rel_filepos == rel_hdr->sh_offset
		  || (rel_hdr2 && asect->rel_filepos == rel_hdr2->sh_offset));

    }
  else
    {
      /* Note that ASECT->RELOC_COUNT tends not to be accurate in this
	 case because relocations against this section may use the
	 dynamic symbol table, and in that case bfd_section_from_shdr
	 in elf.c does not update the RELOC_COUNT.  */
      if (asect->size == 0)
	return TRUE;

      rel_hdr = &d->this_hdr;
      reloc_count = NUM_SHDR_ENTRIES (rel_hdr);
      rel_hdr2 = NULL;
      reloc_count2 = 0;
    }

  /* Allocate space for 3 arelent structures for each Rel structure.  */
  amt = (reloc_count + reloc_count2) * 3 * sizeof (arelent);
  relents = bfd_alloc (abfd, amt);
  if (relents == NULL)
    return FALSE;

  /* The slurp_one_reloc_table routine increments reloc_count.  */
  asect->reloc_count = 0;

  if (! mips_elf64_slurp_one_reloc_table (abfd, asect,
					  rel_hdr, reloc_count,
					  relents,
					  symbols, dynamic))
    return FALSE;
  if (d->rel_hdr2 != NULL)
    {
      if (! mips_elf64_slurp_one_reloc_table (abfd, asect,
					      rel_hdr2, reloc_count2,
					      relents + reloc_count * 3,
					      symbols, dynamic))
	return FALSE;
    }

  asect->relocation = relents;
  return TRUE;
}