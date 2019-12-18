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
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct elf_s390_link_hash_entry {int /*<<< orphan*/  gotplt_refcount; struct elf_s390_dyn_relocs* dyn_relocs; } ;
struct elf_s390_dyn_relocs {struct elf_s390_dyn_relocs* next; TYPE_7__* sec; } ;
struct TYPE_24__ {int refcount; } ;
struct TYPE_23__ {int refcount; } ;
struct TYPE_19__ {scalar_t__ link; } ;
struct TYPE_20__ {TYPE_1__ i; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_6__ plt; TYPE_5__ got; TYPE_3__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_25__ {int reloc_count; } ;
typedef  TYPE_7__ asection ;
struct TYPE_27__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_26__ {unsigned long sh_info; } ;
struct TYPE_22__ {int refcount; } ;
struct TYPE_18__ {TYPE_4__ tls_ldm_got; } ;
struct TYPE_17__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_16__ {TYPE_8__ symtab_hdr; } ;
typedef  TYPE_8__ Elf_Internal_Shdr ;
typedef  TYPE_9__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 unsigned int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_390_12 162 
#define  R_390_16 161 
#define  R_390_20 160 
#define  R_390_32 159 
#define  R_390_8 158 
#define  R_390_GOT12 157 
#define  R_390_GOT16 156 
#define  R_390_GOT20 155 
#define  R_390_GOT32 154 
#define  R_390_GOTENT 153 
#define  R_390_GOTOFF16 152 
#define  R_390_GOTOFF32 151 
#define  R_390_GOTPC 150 
#define  R_390_GOTPCDBL 149 
#define  R_390_GOTPLT12 148 
#define  R_390_GOTPLT16 147 
#define  R_390_GOTPLT20 146 
#define  R_390_GOTPLT32 145 
#define  R_390_GOTPLTENT 144 
#define  R_390_PC16 143 
#define  R_390_PC16DBL 142 
#define  R_390_PC32 141 
#define  R_390_PC32DBL 140 
#define  R_390_PLT16DBL 139 
#define  R_390_PLT32 138 
#define  R_390_PLT32DBL 137 
#define  R_390_PLTOFF16 136 
#define  R_390_PLTOFF32 135 
#define  R_390_TLS_GD32 134 
#define  R_390_TLS_GOTIE12 133 
#define  R_390_TLS_GOTIE20 132 
#define  R_390_TLS_GOTIE32 131 
#define  R_390_TLS_IE32 130 
#define  R_390_TLS_IEENT 129 
#define  R_390_TLS_LDM32 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int* elf_local_got_refcounts (int /*<<< orphan*/ *) ; 
 TYPE_13__* elf_s390_hash_table (struct bfd_link_info*) ; 
 unsigned int elf_s390_tls_transition (struct bfd_link_info*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_11__* elf_section_data (TYPE_7__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_10__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf_s390_gc_sweep_hook (bfd *abfd,
			struct bfd_link_info *info,
			asection *sec,
			const Elf_Internal_Rela *relocs)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Elf_Internal_Rela *rel, *relend;

  elf_section_data (sec)->local_dynrel = NULL;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (abfd);
  local_got_refcounts = elf_local_got_refcounts (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      unsigned int r_type;
      struct elf_link_hash_entry *h = NULL;

      r_symndx = ELF32_R_SYM (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct elf_s390_link_hash_entry *eh;
	  struct elf_s390_dyn_relocs **pp;
	  struct elf_s390_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct elf_s390_link_hash_entry *) h;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      r_type = ELF32_R_TYPE (rel->r_info);
      r_type = elf_s390_tls_transition (info, r_type, h != NULL);
      switch (r_type)
	{
	case R_390_TLS_LDM32:
	  if (elf_s390_hash_table (info)->tls_ldm_got.refcount > 0)
	    elf_s390_hash_table (info)->tls_ldm_got.refcount -= 1;
	  break;

	case R_390_TLS_GD32:
	case R_390_TLS_IE32:
	case R_390_TLS_GOTIE12:
	case R_390_TLS_GOTIE20:
	case R_390_TLS_GOTIE32:
	case R_390_TLS_IEENT:
	case R_390_GOT12:
	case R_390_GOT16:
	case R_390_GOT20:
	case R_390_GOT32:
	case R_390_GOTOFF16:
	case R_390_GOTOFF32:
	case R_390_GOTPC:
	case R_390_GOTPCDBL:
	case R_390_GOTENT:
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

	case R_390_8:
	case R_390_12:
	case R_390_16:
	case R_390_20:
	case R_390_32:
	case R_390_PC16:
	case R_390_PC16DBL:
	case R_390_PC32DBL:
	case R_390_PC32:
	  if (info->shared)
	    break;
	  /* Fall through.  */

	case R_390_PLT16DBL:
	case R_390_PLT32DBL:
	case R_390_PLT32:
	case R_390_PLTOFF16:
	case R_390_PLTOFF32:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		h->plt.refcount -= 1;
	    }
	  break;

	case R_390_GOTPLT12:
	case R_390_GOTPLT16:
	case R_390_GOTPLT20:
	case R_390_GOTPLT32:
	case R_390_GOTPLTENT:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		{
		  ((struct elf_s390_link_hash_entry *) h)->gotplt_refcount--;
		  h->plt.refcount -= 1;
		}
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx] -= 1;
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}