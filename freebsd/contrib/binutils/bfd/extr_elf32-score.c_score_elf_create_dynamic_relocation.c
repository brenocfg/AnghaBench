#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int dynindx; int /*<<< orphan*/  def_regular; } ;
struct score_elf_link_hash_entry {TYPE_1__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  symbolic; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {int reloc_count; int size; scalar_t__ output_offset; TYPE_9__* output_section; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_3__ asection ;
struct TYPE_19__ {scalar_t__ vma; } ;
struct TYPE_15__ {int /*<<< orphan*/  sh_flags; } ;
struct TYPE_18__ {TYPE_2__ this_hdr; } ;
struct TYPE_17__ {scalar_t__ r_offset; void* r_info; } ;
struct TYPE_13__ {int /*<<< orphan*/ * dynobj; } ;
typedef  TYPE_4__ Elf_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 void* ELF32_R_INFO (unsigned long,int) ; 
 int ELF32_R_TYPE (void*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ MINUS_ONE ; 
 scalar_t__ MINUS_TWO ; 
 int R_SCORE_NONE ; 
 int R_SCORE_REL32 ; 
 int SCORE_ELF_REL_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHF_WRITE ; 
 scalar_t__ TRUE ; 
 void* _bfd_elf_section_offset (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  bfd_elf32_swap_reloc_out (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_10__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_8__* elf_section_data (TYPE_9__*) ; 
 TYPE_3__* score_elf_rel_dyn_section (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
score_elf_create_dynamic_relocation (bfd *output_bfd,
				     struct bfd_link_info *info,
				     const Elf_Internal_Rela *rel,
				     struct score_elf_link_hash_entry *h,
				     bfd_vma symbol,
				     bfd_vma *addendp, asection *input_section)
{
  Elf_Internal_Rela outrel[3];
  asection *sreloc;
  bfd *dynobj;
  int r_type;
  long indx;
  bfd_boolean defined_p;

  r_type = ELF32_R_TYPE (rel->r_info);
  dynobj = elf_hash_table (info)->dynobj;
  sreloc = score_elf_rel_dyn_section (dynobj, FALSE);
  BFD_ASSERT (sreloc != NULL);
  BFD_ASSERT (sreloc->contents != NULL);
  BFD_ASSERT (sreloc->reloc_count * SCORE_ELF_REL_SIZE (output_bfd) < sreloc->size);

  outrel[0].r_offset =
    _bfd_elf_section_offset (output_bfd, info, input_section, rel[0].r_offset);
  outrel[1].r_offset =
    _bfd_elf_section_offset (output_bfd, info, input_section, rel[1].r_offset);
  outrel[2].r_offset =
    _bfd_elf_section_offset (output_bfd, info, input_section, rel[2].r_offset);

  if (outrel[0].r_offset == MINUS_ONE)
    /* The relocation field has been deleted.  */
    return TRUE;

  if (outrel[0].r_offset == MINUS_TWO)
    {
      /* The relocation field has been converted into a relative value of
	 some sort.  Functions like _bfd_elf_write_section_eh_frame expect
	 the field to be fully relocated, so add in the symbol's value.  */
      *addendp += symbol;
      return TRUE;
    }

  /* We must now calculate the dynamic symbol table index to use
     in the relocation.  */
  if (h != NULL
      && (! info->symbolic || !h->root.def_regular)
      /* h->root.dynindx may be -1 if this symbol was marked to
	 become local.  */
      && h->root.dynindx != -1)
    {
      indx = h->root.dynindx;
	/* ??? glibc's ld.so just adds the final GOT entry to the
	   relocation field.  It therefore treats relocs against
	   defined symbols in the same way as relocs against
	   undefined symbols.  */
      defined_p = FALSE;
    }
  else
    {
      indx = 0;
      defined_p = TRUE;
    }

  /* If the relocation was previously an absolute relocation and
     this symbol will not be referred to by the relocation, we must
     adjust it by the value we give it in the dynamic symbol table.
     Otherwise leave the job up to the dynamic linker.  */
  if (defined_p && r_type != R_SCORE_REL32)
    *addendp += symbol;

  /* The relocation is always an REL32 relocation because we don't
     know where the shared library will wind up at load-time.  */
  outrel[0].r_info = ELF32_R_INFO ((unsigned long) indx, R_SCORE_REL32);

  /* For strict adherence to the ABI specification, we should
     generate a R_SCORE_64 relocation record by itself before the
     _REL32/_64 record as well, such that the addend is read in as
     a 64-bit value (REL32 is a 32-bit relocation, after all).
     However, since none of the existing ELF64 SCORE dynamic
     loaders seems to care, we don't waste space with these
     artificial relocations.  If this turns out to not be true,
     score_elf_allocate_dynamic_relocations() should be tweaked so
     as to make room for a pair of dynamic relocations per
     invocation if ABI_64_P, and here we should generate an
     additional relocation record with R_SCORE_64 by itself for a
     NULL symbol before this relocation record.  */
  outrel[1].r_info = ELF32_R_INFO (0, R_SCORE_NONE);
  outrel[2].r_info = ELF32_R_INFO (0, R_SCORE_NONE);

  /* Adjust the output offset of the relocation to reference the
     correct location in the output file.  */
  outrel[0].r_offset += (input_section->output_section->vma
			 + input_section->output_offset);
  outrel[1].r_offset += (input_section->output_section->vma
			 + input_section->output_offset);
  outrel[2].r_offset += (input_section->output_section->vma
			 + input_section->output_offset);

  /* Put the relocation back out.  We have to use the special
     relocation outputter in the 64-bit case since the 64-bit
     relocation format is non-standard.  */
  bfd_elf32_swap_reloc_out
      (output_bfd, &outrel[0],
       (sreloc->contents + sreloc->reloc_count * sizeof (Elf32_External_Rel)));

  /* We've now added another relocation.  */
  ++sreloc->reloc_count;

  /* Make sure the output section is writable.  The dynamic linker
     will be writing to it.  */
  elf_section_data (input_section->output_section)->this_hdr.sh_flags |= SHF_WRITE;

  return TRUE;
}