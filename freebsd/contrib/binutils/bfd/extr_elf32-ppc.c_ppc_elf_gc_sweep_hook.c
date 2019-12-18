#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
struct TYPE_23__ {struct elf_link_hash_entry* hgot; } ;
struct ppc_elf_link_hash_table {TYPE_5__ elf; } ;
struct ppc_elf_link_hash_entry {struct ppc_elf_dyn_relocs* dyn_relocs; } ;
struct ppc_elf_dyn_relocs {struct ppc_elf_dyn_relocs* next; TYPE_7__* sec; } ;
struct TYPE_24__ {int refcount; } ;
struct plt_entry {TYPE_6__ plt; } ;
struct TYPE_22__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_19__ {scalar_t__ link; } ;
struct TYPE_20__ {TYPE_1__ i; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_4__ got; TYPE_3__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  enum elf_ppc_reloc_type { ____Placeholder_elf_ppc_reloc_type } elf_ppc_reloc_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_25__ {int flags; int reloc_count; } ;
typedef  TYPE_7__ asection ;
struct TYPE_27__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_26__ {unsigned long sh_info; } ;
struct TYPE_18__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_17__ {TYPE_8__ symtab_hdr; } ;
typedef  TYPE_8__ Elf_Internal_Shdr ;
typedef  TYPE_9__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_PPC_ADDR14 169 
#define  R_PPC_ADDR14_BRNTAKEN 168 
#define  R_PPC_ADDR14_BRTAKEN 167 
#define  R_PPC_ADDR16 166 
#define  R_PPC_ADDR16_HA 165 
#define  R_PPC_ADDR16_HI 164 
#define  R_PPC_ADDR16_LO 163 
#define  R_PPC_ADDR24 162 
#define  R_PPC_ADDR32 161 
#define  R_PPC_GOT16 160 
#define  R_PPC_GOT16_HA 159 
#define  R_PPC_GOT16_HI 158 
#define  R_PPC_GOT16_LO 157 
#define  R_PPC_GOT_DTPREL16 156 
#define  R_PPC_GOT_DTPREL16_HA 155 
#define  R_PPC_GOT_DTPREL16_HI 154 
#define  R_PPC_GOT_DTPREL16_LO 153 
#define  R_PPC_GOT_TLSGD16 152 
#define  R_PPC_GOT_TLSGD16_HA 151 
#define  R_PPC_GOT_TLSGD16_HI 150 
#define  R_PPC_GOT_TLSGD16_LO 149 
#define  R_PPC_GOT_TLSLD16 148 
#define  R_PPC_GOT_TLSLD16_HA 147 
#define  R_PPC_GOT_TLSLD16_HI 146 
#define  R_PPC_GOT_TLSLD16_LO 145 
#define  R_PPC_GOT_TPREL16 144 
#define  R_PPC_GOT_TPREL16_HA 143 
#define  R_PPC_GOT_TPREL16_HI 142 
#define  R_PPC_GOT_TPREL16_LO 141 
#define  R_PPC_PLT16_HA 140 
#define  R_PPC_PLT16_HI 139 
#define  R_PPC_PLT16_LO 138 
#define  R_PPC_PLT32 137 
#define  R_PPC_PLTREL24 136 
#define  R_PPC_PLTREL32 135 
#define  R_PPC_REL14 134 
#define  R_PPC_REL14_BRNTAKEN 133 
#define  R_PPC_REL14_BRTAKEN 132 
#define  R_PPC_REL24 131 
#define  R_PPC_REL32 130 
#define  R_PPC_UADDR16 129 
#define  R_PPC_UADDR32 128 
 int SEC_ALLOC ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_7__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/ * elf_local_got_refcounts (int /*<<< orphan*/ *) ; 
 TYPE_14__* elf_section_data (TYPE_7__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_13__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct plt_entry* find_plt_ent (struct elf_link_hash_entry*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 struct ppc_elf_link_hash_table* ppc_elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
ppc_elf_gc_sweep_hook (bfd *abfd,
		       struct bfd_link_info *info,
		       asection *sec,
		       const Elf_Internal_Rela *relocs)
{
  struct ppc_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Elf_Internal_Rela *rel, *relend;
  asection *got2;

  if ((sec->flags & SEC_ALLOC) == 0)
    return TRUE;

  elf_section_data (sec)->local_dynrel = NULL;

  htab = ppc_elf_hash_table (info);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  local_got_refcounts = elf_local_got_refcounts (abfd);
  got2 = bfd_get_section_by_name (abfd, ".got2");

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      enum elf_ppc_reloc_type r_type;
      struct elf_link_hash_entry *h = NULL;

      r_symndx = ELF32_R_SYM (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct ppc_elf_dyn_relocs **pp, *p;
	  struct ppc_elf_link_hash_entry *eh;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct ppc_elf_link_hash_entry *) h;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      r_type = ELF32_R_TYPE (rel->r_info);
      switch (r_type)
	{
	case R_PPC_GOT_TLSLD16:
	case R_PPC_GOT_TLSLD16_LO:
	case R_PPC_GOT_TLSLD16_HI:
	case R_PPC_GOT_TLSLD16_HA:
	case R_PPC_GOT_TLSGD16:
	case R_PPC_GOT_TLSGD16_LO:
	case R_PPC_GOT_TLSGD16_HI:
	case R_PPC_GOT_TLSGD16_HA:
	case R_PPC_GOT_TPREL16:
	case R_PPC_GOT_TPREL16_LO:
	case R_PPC_GOT_TPREL16_HI:
	case R_PPC_GOT_TPREL16_HA:
	case R_PPC_GOT_DTPREL16:
	case R_PPC_GOT_DTPREL16_LO:
	case R_PPC_GOT_DTPREL16_HI:
	case R_PPC_GOT_DTPREL16_HA:
	case R_PPC_GOT16:
	case R_PPC_GOT16_LO:
	case R_PPC_GOT16_HI:
	case R_PPC_GOT16_HA:
	  if (h != NULL)
	    {
	      if (h->got.refcount > 0)
		h->got.refcount--;
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx]--;
	    }
	  break;

	case R_PPC_REL24:
	case R_PPC_REL14:
	case R_PPC_REL14_BRTAKEN:
	case R_PPC_REL14_BRNTAKEN:
	case R_PPC_REL32:
	  if (h == NULL || h == htab->elf.hgot)
	    break;
	  /* Fall thru */

	case R_PPC_ADDR32:
	case R_PPC_ADDR24:
	case R_PPC_ADDR16:
	case R_PPC_ADDR16_LO:
	case R_PPC_ADDR16_HI:
	case R_PPC_ADDR16_HA:
	case R_PPC_ADDR14:
	case R_PPC_ADDR14_BRTAKEN:
	case R_PPC_ADDR14_BRNTAKEN:
	case R_PPC_UADDR32:
	case R_PPC_UADDR16:
	  if (info->shared)
	    break;

	case R_PPC_PLT32:
	case R_PPC_PLTREL24:
	case R_PPC_PLTREL32:
	case R_PPC_PLT16_LO:
	case R_PPC_PLT16_HI:
	case R_PPC_PLT16_HA:
	  if (h != NULL)
	    {
	      bfd_vma addend = r_type == R_PPC_PLTREL24 ? rel->r_addend : 0;
	      struct plt_entry *ent = find_plt_ent (h, got2, addend);
	      if (ent->plt.refcount > 0)
		ent->plt.refcount -= 1;
	    }
	  break;

	default:
	  break;
	}
    }
  return TRUE;
}