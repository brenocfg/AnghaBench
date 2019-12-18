#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ dynamic_sections_created; int /*<<< orphan*/ * dynobj; } ;
struct elf64_x86_64_link_hash_table {scalar_t__ tlsdesc_plt; scalar_t__ tlsdesc_got; TYPE_5__* sgot; TYPE_5__* sgotplt; TYPE_5__* splt; TYPE_3__* srelplt; TYPE_2__ elf; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {scalar_t__ contents; scalar_t__ size; scalar_t__ output_offset; scalar_t__ vma; TYPE_8__* output_section; } ;
typedef  TYPE_5__ asection ;
struct TYPE_19__ {scalar_t__ vma; } ;
struct TYPE_12__ {int sh_entsize; } ;
struct TYPE_18__ {TYPE_1__ this_hdr; } ;
struct TYPE_15__ {scalar_t__ d_ptr; scalar_t__ d_val; } ;
struct TYPE_17__ {int d_tag; TYPE_4__ d_un; } ;
struct TYPE_14__ {TYPE_5__* output_section; } ;
typedef  TYPE_6__ Elf_Internal_Dyn ;
typedef  int /*<<< orphan*/  Elf64_External_Dyn ;

/* Variables and functions */
#define  DT_JMPREL 133 
#define  DT_PLTGOT 132 
#define  DT_PLTRELSZ 131 
#define  DT_RELASZ 130 
#define  DT_TLSDESC_GOT 129 
#define  DT_TLSDESC_PLT 128 
 int GOT_ENTRY_SIZE ; 
 int PLT_ENTRY_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_elf64_swap_dyn_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  bfd_elf64_swap_dyn_out (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bfd_put_64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct elf64_x86_64_link_hash_table* elf64_x86_64_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf64_x86_64_plt0_entry ; 
 TYPE_7__* elf_section_data (TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_finish_dynamic_sections (bfd *output_bfd, struct bfd_link_info *info)
{
  struct elf64_x86_64_link_hash_table *htab;
  bfd *dynobj;
  asection *sdyn;

  htab = elf64_x86_64_hash_table (info);
  dynobj = htab->elf.dynobj;
  sdyn = bfd_get_section_by_name (dynobj, ".dynamic");

  if (htab->elf.dynamic_sections_created)
    {
      Elf64_External_Dyn *dyncon, *dynconend;

      if (sdyn == NULL || htab->sgot == NULL)
	abort ();

      dyncon = (Elf64_External_Dyn *) sdyn->contents;
      dynconend = (Elf64_External_Dyn *) (sdyn->contents + sdyn->size);
      for (; dyncon < dynconend; dyncon++)
	{
	  Elf_Internal_Dyn dyn;
	  asection *s;

	  bfd_elf64_swap_dyn_in (dynobj, dyncon, &dyn);

	  switch (dyn.d_tag)
	    {
	    default:
	      continue;

	    case DT_PLTGOT:
	      s = htab->sgotplt;
	      dyn.d_un.d_ptr = s->output_section->vma + s->output_offset;
	      break;

	    case DT_JMPREL:
	      dyn.d_un.d_ptr = htab->srelplt->output_section->vma;
	      break;

	    case DT_PLTRELSZ:
	      s = htab->srelplt->output_section;
	      dyn.d_un.d_val = s->size;
	      break;

	    case DT_RELASZ:
	      /* The procedure linkage table relocs (DT_JMPREL) should
		 not be included in the overall relocs (DT_RELA).
		 Therefore, we override the DT_RELASZ entry here to
		 make it not include the JMPREL relocs.  Since the
		 linker script arranges for .rela.plt to follow all
		 other relocation sections, we don't have to worry
		 about changing the DT_RELA entry.  */
	      if (htab->srelplt != NULL)
		{
		  s = htab->srelplt->output_section;
		  dyn.d_un.d_val -= s->size;
		}
	      break;

	    case DT_TLSDESC_PLT:
	      s = htab->splt;
	      dyn.d_un.d_ptr = s->output_section->vma + s->output_offset
		+ htab->tlsdesc_plt;
	      break;

	    case DT_TLSDESC_GOT:
	      s = htab->sgot;
	      dyn.d_un.d_ptr = s->output_section->vma + s->output_offset
		+ htab->tlsdesc_got;
	      break;
	    }

	  bfd_elf64_swap_dyn_out (output_bfd, &dyn, dyncon);
	}

      /* Fill in the special first entry in the procedure linkage table.  */
      if (htab->splt && htab->splt->size > 0)
	{
	  /* Fill in the first entry in the procedure linkage table.  */
	  memcpy (htab->splt->contents, elf64_x86_64_plt0_entry,
		  PLT_ENTRY_SIZE);
	  /* Add offset for pushq GOT+8(%rip), since the instruction
	     uses 6 bytes subtract this value.  */
	  bfd_put_32 (output_bfd,
		      (htab->sgotplt->output_section->vma
		       + htab->sgotplt->output_offset
		       + 8
		       - htab->splt->output_section->vma
		       - htab->splt->output_offset
		       - 6),
		      htab->splt->contents + 2);
	  /* Add offset for jmp *GOT+16(%rip). The 12 is the offset to
	     the end of the instruction.  */
	  bfd_put_32 (output_bfd,
		      (htab->sgotplt->output_section->vma
		       + htab->sgotplt->output_offset
		       + 16
		       - htab->splt->output_section->vma
		       - htab->splt->output_offset
		       - 12),
		      htab->splt->contents + 8);

	  elf_section_data (htab->splt->output_section)->this_hdr.sh_entsize =
	    PLT_ENTRY_SIZE;

	  if (htab->tlsdesc_plt)
	    {
	      bfd_put_64 (output_bfd, (bfd_vma) 0,
			  htab->sgot->contents + htab->tlsdesc_got);

	      memcpy (htab->splt->contents + htab->tlsdesc_plt,
		      elf64_x86_64_plt0_entry,
		      PLT_ENTRY_SIZE);

	      /* Add offset for pushq GOT+8(%rip), since the
		 instruction uses 6 bytes subtract this value.  */
	      bfd_put_32 (output_bfd,
			  (htab->sgotplt->output_section->vma
			   + htab->sgotplt->output_offset
			   + 8
			   - htab->splt->output_section->vma
			   - htab->splt->output_offset
			   - htab->tlsdesc_plt
			   - 6),
			  htab->splt->contents + htab->tlsdesc_plt + 2);
	      /* Add offset for jmp *GOT+TDG(%rip), where TGD stands for
		 htab->tlsdesc_got. The 12 is the offset to the end of
		 the instruction.  */
	      bfd_put_32 (output_bfd,
			  (htab->sgot->output_section->vma
			   + htab->sgot->output_offset
			   + htab->tlsdesc_got
			   - htab->splt->output_section->vma
			   - htab->splt->output_offset
			   - htab->tlsdesc_plt
			   - 12),
			  htab->splt->contents + htab->tlsdesc_plt + 8);
	    }
	}
    }

  if (htab->sgotplt)
    {
      /* Fill in the first three entries in the global offset table.  */
      if (htab->sgotplt->size > 0)
	{
	  /* Set the first entry in the global offset table to the address of
	     the dynamic section.  */
	  if (sdyn == NULL)
	    bfd_put_64 (output_bfd, (bfd_vma) 0, htab->sgotplt->contents);
	  else
	    bfd_put_64 (output_bfd,
			sdyn->output_section->vma + sdyn->output_offset,
			htab->sgotplt->contents);
	  /* Write GOT[1] and GOT[2], needed for the dynamic linker.  */
	  bfd_put_64 (output_bfd, (bfd_vma) 0, htab->sgotplt->contents + GOT_ENTRY_SIZE);
	  bfd_put_64 (output_bfd, (bfd_vma) 0, htab->sgotplt->contents + GOT_ENTRY_SIZE*2);
	}

      elf_section_data (htab->sgotplt->output_section)->this_hdr.sh_entsize =
	GOT_ENTRY_SIZE;
    }

  if (htab->sgot && htab->sgot->size > 0)
    elf_section_data (htab->sgot->output_section)->this_hdr.sh_entsize
      = GOT_ENTRY_SIZE;

  return TRUE;
}