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
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_23__ {int /*<<< orphan*/  string; } ;
struct TYPE_19__ {scalar_t__ link; } ;
struct TYPE_20__ {TYPE_1__ i; } ;
struct TYPE_24__ {scalar_t__ type; TYPE_5__ root; TYPE_2__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/  refcount; } ;
struct elf_link_hash_entry {TYPE_7__ plt; TYPE_6__ root; TYPE_4__ got; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
struct TYPE_21__ {int refcount; } ;
struct _bfd_sparc_elf_link_hash_table {TYPE_3__ tls_ldm_got; } ;
struct _bfd_sparc_elf_link_hash_entry {struct _bfd_sparc_elf_dyn_relocs* dyn_relocs; } ;
struct _bfd_sparc_elf_dyn_relocs {struct _bfd_sparc_elf_dyn_relocs* next; TYPE_8__* sec; } ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_26__ {int reloc_count; } ;
typedef  TYPE_8__ asection ;
struct TYPE_27__ {unsigned long sh_info; } ;
struct TYPE_18__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_17__ {TYPE_9__ symtab_hdr; } ;
struct TYPE_16__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_9__ Elf_Internal_Shdr ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
#define  R_SPARC_10 176 
#define  R_SPARC_11 175 
#define  R_SPARC_13 174 
#define  R_SPARC_16 173 
#define  R_SPARC_22 172 
#define  R_SPARC_32 171 
#define  R_SPARC_5 170 
#define  R_SPARC_6 169 
#define  R_SPARC_64 168 
#define  R_SPARC_7 167 
#define  R_SPARC_8 166 
#define  R_SPARC_DISP16 165 
#define  R_SPARC_DISP32 164 
#define  R_SPARC_DISP64 163 
#define  R_SPARC_DISP8 162 
#define  R_SPARC_GOT10 161 
#define  R_SPARC_GOT13 160 
#define  R_SPARC_GOT22 159 
#define  R_SPARC_H44 158 
#define  R_SPARC_HH22 157 
#define  R_SPARC_HI22 156 
#define  R_SPARC_HIX22 155 
#define  R_SPARC_HM10 154 
#define  R_SPARC_L44 153 
#define  R_SPARC_LM22 152 
#define  R_SPARC_LO10 151 
#define  R_SPARC_LOX10 150 
#define  R_SPARC_M44 149 
#define  R_SPARC_OLO10 148 
#define  R_SPARC_PC10 147 
#define  R_SPARC_PC22 146 
#define  R_SPARC_PC_HH22 145 
#define  R_SPARC_PC_HM10 144 
#define  R_SPARC_PC_LM22 143 
#define  R_SPARC_PLT32 142 
#define  R_SPARC_TLS_GD_HI22 141 
#define  R_SPARC_TLS_GD_LO10 140 
#define  R_SPARC_TLS_IE_HI22 139 
#define  R_SPARC_TLS_IE_LO10 138 
#define  R_SPARC_TLS_LDM_HI22 137 
#define  R_SPARC_TLS_LDM_LO10 136 
#define  R_SPARC_UA16 135 
#define  R_SPARC_UA32 134 
#define  R_SPARC_UA64 133 
#define  R_SPARC_WDISP16 132 
#define  R_SPARC_WDISP19 131 
#define  R_SPARC_WDISP22 130 
#define  R_SPARC_WDISP30 129 
#define  R_SPARC_WPLT30 128 
 unsigned long SPARC_ELF_R_SYMNDX (struct _bfd_sparc_elf_link_hash_table*,int /*<<< orphan*/ ) ; 
 unsigned int SPARC_ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/ * elf_local_got_refcounts (int /*<<< orphan*/ *) ; 
 TYPE_12__* elf_section_data (TYPE_8__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_11__* elf_tdata (int /*<<< orphan*/ *) ; 
 unsigned int sparc_elf_tls_transition (struct bfd_link_info*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

bfd_boolean
_bfd_sparc_elf_gc_sweep_hook (bfd *abfd, struct bfd_link_info *info,
			      asection *sec, const Elf_Internal_Rela *relocs)
{
  struct _bfd_sparc_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Elf_Internal_Rela *rel, *relend;

  elf_section_data (sec)->local_dynrel = NULL;

  htab = _bfd_sparc_elf_hash_table (info);
  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  local_got_refcounts = elf_local_got_refcounts (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      unsigned int r_type;
      struct elf_link_hash_entry *h = NULL;

      r_symndx = SPARC_ELF_R_SYMNDX (htab, rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct _bfd_sparc_elf_link_hash_entry *eh;
	  struct _bfd_sparc_elf_dyn_relocs **pp;
	  struct _bfd_sparc_elf_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct _bfd_sparc_elf_link_hash_entry *) h;
	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      r_type = SPARC_ELF_R_TYPE (rel->r_info);
      r_type = sparc_elf_tls_transition (info, abfd, r_type, h != NULL);
      switch (r_type)
	{
	case R_SPARC_TLS_LDM_HI22:
	case R_SPARC_TLS_LDM_LO10:
	  if (_bfd_sparc_elf_hash_table (info)->tls_ldm_got.refcount > 0)
	    _bfd_sparc_elf_hash_table (info)->tls_ldm_got.refcount -= 1;
	  break;

	case R_SPARC_TLS_GD_HI22:
	case R_SPARC_TLS_GD_LO10:
	case R_SPARC_TLS_IE_HI22:
	case R_SPARC_TLS_IE_LO10:
	case R_SPARC_GOT10:
	case R_SPARC_GOT13:
	case R_SPARC_GOT22:
	  if (h != NULL)
	    {
	      if (h->got.refcount > 0)
		h->got.refcount--;
	    }
	  else
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx]--;
	    }
	  break;

	case R_SPARC_PC10:
	case R_SPARC_PC22:
	case R_SPARC_PC_HH22:
	case R_SPARC_PC_HM10:
	case R_SPARC_PC_LM22:
	  if (h != NULL
	      && strcmp (h->root.root.string, "_GLOBAL_OFFSET_TABLE_") == 0)
	    break;
	  /* Fall through.  */

	case R_SPARC_DISP8:
	case R_SPARC_DISP16:
	case R_SPARC_DISP32:
	case R_SPARC_DISP64:
	case R_SPARC_WDISP30:
	case R_SPARC_WDISP22:
	case R_SPARC_WDISP19:
	case R_SPARC_WDISP16:
	case R_SPARC_8:
	case R_SPARC_16:
	case R_SPARC_32:
	case R_SPARC_HI22:
	case R_SPARC_22:
	case R_SPARC_13:
	case R_SPARC_LO10:
	case R_SPARC_UA16:
	case R_SPARC_UA32:
	case R_SPARC_PLT32:
	case R_SPARC_10:
	case R_SPARC_11:
	case R_SPARC_64:
	case R_SPARC_OLO10:
	case R_SPARC_HH22:
	case R_SPARC_HM10:
	case R_SPARC_LM22:
	case R_SPARC_7:
	case R_SPARC_5:
	case R_SPARC_6:
	case R_SPARC_HIX22:
	case R_SPARC_LOX10:
	case R_SPARC_H44:
	case R_SPARC_M44:
	case R_SPARC_L44:
	case R_SPARC_UA64:
	  if (info->shared)
	    break;
	  /* Fall through.  */

	case R_SPARC_WPLT30:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		h->plt.refcount--;
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}