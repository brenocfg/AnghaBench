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
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct ppc_link_hash_table {int dummy; } ;
struct ppc_link_hash_entry {struct ppc_dyn_relocs* dyn_relocs; } ;
struct ppc_dyn_relocs {struct ppc_dyn_relocs* next; TYPE_8__* sec; } ;
struct TYPE_25__ {int refcount; } ;
struct plt_entry {TYPE_7__ plt; int /*<<< orphan*/  addend; struct plt_entry* next; } ;
struct TYPE_23__ {int refcount; } ;
struct got_entry {char tls_type; TYPE_5__ got; int /*<<< orphan*/ * owner; int /*<<< orphan*/  addend; struct got_entry* next; } ;
struct TYPE_24__ {struct plt_entry* plist; } ;
struct TYPE_22__ {struct got_entry* glist; } ;
struct TYPE_19__ {scalar_t__ link; } ;
struct TYPE_20__ {TYPE_1__ i; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_6__ plt; TYPE_4__ got; TYPE_3__ root; } ;
struct bfd_link_info {int dummy; } ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_26__ {int flags; int reloc_count; } ;
typedef  TYPE_8__ asection ;
struct TYPE_27__ {unsigned long sh_info; } ;
struct TYPE_18__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_17__ {TYPE_9__ symtab_hdr; } ;
struct TYPE_16__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_9__ Elf_Internal_Shdr ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_PPC64_GOT16 158 
#define  R_PPC64_GOT16_DS 157 
#define  R_PPC64_GOT16_HA 156 
#define  R_PPC64_GOT16_HI 155 
#define  R_PPC64_GOT16_LO 154 
#define  R_PPC64_GOT16_LO_DS 153 
#define  R_PPC64_GOT_DTPREL16_DS 152 
#define  R_PPC64_GOT_DTPREL16_HA 151 
#define  R_PPC64_GOT_DTPREL16_HI 150 
#define  R_PPC64_GOT_DTPREL16_LO_DS 149 
#define  R_PPC64_GOT_TLSGD16 148 
#define  R_PPC64_GOT_TLSGD16_HA 147 
#define  R_PPC64_GOT_TLSGD16_HI 146 
#define  R_PPC64_GOT_TLSGD16_LO 145 
#define  R_PPC64_GOT_TLSLD16 144 
#define  R_PPC64_GOT_TLSLD16_HA 143 
#define  R_PPC64_GOT_TLSLD16_HI 142 
#define  R_PPC64_GOT_TLSLD16_LO 141 
#define  R_PPC64_GOT_TPREL16_DS 140 
#define  R_PPC64_GOT_TPREL16_HA 139 
#define  R_PPC64_GOT_TPREL16_HI 138 
#define  R_PPC64_GOT_TPREL16_LO_DS 137 
#define  R_PPC64_PLT16_HA 136 
#define  R_PPC64_PLT16_HI 135 
#define  R_PPC64_PLT16_LO 134 
#define  R_PPC64_PLT32 133 
#define  R_PPC64_PLT64 132 
#define  R_PPC64_REL14 131 
#define  R_PPC64_REL14_BRNTAKEN 130 
#define  R_PPC64_REL14_BRTAKEN 129 
#define  R_PPC64_REL24 128 
 int SEC_ALLOC ; 
 char TLS_DTPREL ; 
 char TLS_GD ; 
 char TLS_LD ; 
 char TLS_TLS ; 
 char TLS_TPREL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct got_entry** elf_local_got_ents (int /*<<< orphan*/ *) ; 
 TYPE_14__* elf_section_data (TYPE_8__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_13__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
ppc64_elf_gc_sweep_hook (bfd *abfd, struct bfd_link_info *info,
			 asection *sec, const Elf_Internal_Rela *relocs)
{
  struct ppc_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  struct got_entry **local_got_ents;
  const Elf_Internal_Rela *rel, *relend;

  if ((sec->flags & SEC_ALLOC) == 0)
    return TRUE;

  elf_section_data (sec)->local_dynrel = NULL;

  htab = ppc_hash_table (info);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  local_got_ents = elf_local_got_ents (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      enum elf_ppc64_reloc_type r_type;
      struct elf_link_hash_entry *h = NULL;
      char tls_type = 0;

      r_symndx = ELF64_R_SYM (rel->r_info);
      r_type = ELF64_R_TYPE (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct ppc_link_hash_entry *eh;
	  struct ppc_dyn_relocs **pp;
	  struct ppc_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct ppc_link_hash_entry *) h;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      switch (r_type)
	{
	case R_PPC64_GOT_TLSLD16:
	case R_PPC64_GOT_TLSLD16_LO:
	case R_PPC64_GOT_TLSLD16_HI:
	case R_PPC64_GOT_TLSLD16_HA:
	  tls_type = TLS_TLS | TLS_LD;
	  goto dogot;

	case R_PPC64_GOT_TLSGD16:
	case R_PPC64_GOT_TLSGD16_LO:
	case R_PPC64_GOT_TLSGD16_HI:
	case R_PPC64_GOT_TLSGD16_HA:
	  tls_type = TLS_TLS | TLS_GD;
	  goto dogot;

	case R_PPC64_GOT_TPREL16_DS:
	case R_PPC64_GOT_TPREL16_LO_DS:
	case R_PPC64_GOT_TPREL16_HI:
	case R_PPC64_GOT_TPREL16_HA:
	  tls_type = TLS_TLS | TLS_TPREL;
	  goto dogot;

	case R_PPC64_GOT_DTPREL16_DS:
	case R_PPC64_GOT_DTPREL16_LO_DS:
	case R_PPC64_GOT_DTPREL16_HI:
	case R_PPC64_GOT_DTPREL16_HA:
	  tls_type = TLS_TLS | TLS_DTPREL;
	  goto dogot;

	case R_PPC64_GOT16:
	case R_PPC64_GOT16_DS:
	case R_PPC64_GOT16_HA:
	case R_PPC64_GOT16_HI:
	case R_PPC64_GOT16_LO:
	case R_PPC64_GOT16_LO_DS:
	dogot:
	  {
	    struct got_entry *ent;

	    if (h != NULL)
	      ent = h->got.glist;
	    else
	      ent = local_got_ents[r_symndx];

	    for (; ent != NULL; ent = ent->next)
	      if (ent->addend == rel->r_addend
		  && ent->owner == abfd
		  && ent->tls_type == tls_type)
		break;
	    if (ent == NULL)
	      abort ();
	    if (ent->got.refcount > 0)
	      ent->got.refcount -= 1;
	  }
	  break;

	case R_PPC64_PLT16_HA:
	case R_PPC64_PLT16_HI:
	case R_PPC64_PLT16_LO:
	case R_PPC64_PLT32:
	case R_PPC64_PLT64:
	case R_PPC64_REL14:
	case R_PPC64_REL14_BRNTAKEN:
	case R_PPC64_REL14_BRTAKEN:
	case R_PPC64_REL24:
	  if (h != NULL)
	    {
	      struct plt_entry *ent;

	      for (ent = h->plt.plist; ent != NULL; ent = ent->next)
		if (ent->addend == rel->r_addend)
		  break;
	      if (ent != NULL && ent->plt.refcount > 0)
		ent->plt.refcount -= 1;
	    }
	  break;

	default:
	  break;
	}
    }
  return TRUE;
}