#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int refcount; } ;
struct TYPE_20__ {int refcount; } ;
struct TYPE_17__ {scalar_t__ link; } ;
struct TYPE_18__ {TYPE_1__ i; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_6__ plt; TYPE_4__ got; TYPE_3__ root; } ;
struct elf32_arm_relocs_copied {int count; int pc_count; struct elf32_arm_relocs_copied* next; TYPE_7__* section; } ;
struct TYPE_21__ {int refcount; } ;
struct elf32_arm_link_hash_table {TYPE_5__ tls_ldm_got; } ;
struct elf32_arm_link_hash_entry {struct elf32_arm_relocs_copied* relocs_copied; int /*<<< orphan*/  plt_thumb_refcount; } ;
struct bfd_link_info {int dummy; } ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_23__ {int reloc_count; } ;
typedef  TYPE_7__ asection ;
struct TYPE_25__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_24__ {unsigned long sh_info; } ;
struct TYPE_16__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_15__ {TYPE_8__ symtab_hdr; } ;
typedef  TYPE_8__ Elf_Internal_Shdr ;
typedef  TYPE_9__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int const ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_ARM_ABS32 150 
#define  R_ARM_ABS32_NOI 149 
#define  R_ARM_CALL 148 
#define  R_ARM_GOT32 147 
#define  R_ARM_GOT_PREL 146 
#define  R_ARM_JUMP24 145 
#define  R_ARM_MOVT_ABS 144 
#define  R_ARM_MOVT_PREL 143 
#define  R_ARM_MOVW_ABS_NC 142 
#define  R_ARM_MOVW_PREL_NC 141 
#define  R_ARM_PC24 140 
#define  R_ARM_PLT32 139 
#define  R_ARM_PREL31 138 
#define  R_ARM_REL32 137 
#define  R_ARM_REL32_NOI 136 
#define  R_ARM_THM_CALL 135 
#define  R_ARM_THM_MOVT_ABS 134 
#define  R_ARM_THM_MOVT_PREL 133 
#define  R_ARM_THM_MOVW_ABS_NC 132 
#define  R_ARM_THM_MOVW_PREL_NC 131 
#define  R_ARM_TLS_GD32 130 
#define  R_ARM_TLS_IE32 129 
#define  R_ARM_TLS_LDM32 128 
 int /*<<< orphan*/  TRUE ; 
 int arm_real_reloc_type (struct elf32_arm_link_hash_table*,int) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 int* elf_local_got_refcounts (int /*<<< orphan*/ *) ; 
 TYPE_11__* elf_section_data (TYPE_7__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_10__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_gc_sweep_hook (bfd *                     abfd,
			 struct bfd_link_info *    info,
			 asection *                sec,
			 const Elf_Internal_Rela * relocs)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Elf_Internal_Rela *rel, *relend;
  struct elf32_arm_link_hash_table * globals;

  globals = elf32_arm_hash_table (info);

  elf_section_data (sec)->local_dynrel = NULL;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  local_got_refcounts = elf_local_got_refcounts (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      struct elf_link_hash_entry *h = NULL;
      int r_type;

      r_symndx = ELF32_R_SYM (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	}

      r_type = ELF32_R_TYPE (rel->r_info);
      r_type = arm_real_reloc_type (globals, r_type);
      switch (r_type)
	{
	case R_ARM_GOT32:
	case R_ARM_GOT_PREL:
	case R_ARM_TLS_GD32:
	case R_ARM_TLS_IE32:
	  if (h != NULL)
	    {
	      if (h->got.refcount > 0)
		h->got.refcount -= 1;
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx] -= 1;
	    }
	  break;

	case R_ARM_TLS_LDM32:
	  elf32_arm_hash_table (info)->tls_ldm_got.refcount -= 1;
	  break;

	case R_ARM_ABS32:
	case R_ARM_ABS32_NOI:
	case R_ARM_REL32:
	case R_ARM_REL32_NOI:
	case R_ARM_PC24:
	case R_ARM_PLT32:
	case R_ARM_CALL:
	case R_ARM_JUMP24:
	case R_ARM_PREL31:
	case R_ARM_THM_CALL:
	case R_ARM_MOVW_ABS_NC:
	case R_ARM_MOVT_ABS:
	case R_ARM_MOVW_PREL_NC:
	case R_ARM_MOVT_PREL:
	case R_ARM_THM_MOVW_ABS_NC:
	case R_ARM_THM_MOVT_ABS:
	case R_ARM_THM_MOVW_PREL_NC:
	case R_ARM_THM_MOVT_PREL:
	  /* Should the interworking branches be here also?  */

	  if (h != NULL)
	    {
	      struct elf32_arm_link_hash_entry *eh;
	      struct elf32_arm_relocs_copied **pp;
	      struct elf32_arm_relocs_copied *p;

	      eh = (struct elf32_arm_link_hash_entry *) h;

	      if (h->plt.refcount > 0)
		{
		  h->plt.refcount -= 1;
		  if (ELF32_R_TYPE (rel->r_info) == R_ARM_THM_CALL)
		    eh->plt_thumb_refcount--;
		}

	      if (r_type == R_ARM_ABS32
		  || r_type == R_ARM_REL32
                  || r_type == R_ARM_ABS32_NOI
                  || r_type == R_ARM_REL32_NOI)
		{
		  for (pp = &eh->relocs_copied; (p = *pp) != NULL;
		       pp = &p->next)
		  if (p->section == sec)
		    {
		      p->count -= 1;
		      if (ELF32_R_TYPE (rel->r_info) == R_ARM_REL32
                          || ELF32_R_TYPE (rel->r_info) == R_ARM_REL32_NOI)
			p->pc_count -= 1;
		      if (p->count == 0)
			*pp = p->next;
		      break;
		    }
		}
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}