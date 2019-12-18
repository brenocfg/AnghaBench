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
struct TYPE_24__ {int refcount; } ;
struct TYPE_23__ {int refcount; } ;
struct TYPE_19__ {scalar_t__ link; } ;
struct TYPE_20__ {TYPE_1__ i; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_6__ plt; TYPE_5__ got; TYPE_3__ root; } ;
struct elf64_x86_64_link_hash_entry {struct elf64_x86_64_dyn_relocs* dyn_relocs; } ;
struct elf64_x86_64_dyn_relocs {struct elf64_x86_64_dyn_relocs* next; TYPE_7__* sec; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_25__ {int reloc_count; } ;
typedef  TYPE_7__ asection ;
struct TYPE_27__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_26__ {unsigned long sh_info; } ;
struct TYPE_22__ {int refcount; } ;
struct TYPE_18__ {TYPE_4__ tls_ld_got; } ;
struct TYPE_17__ {int /*<<< orphan*/ * local_dynrel; } ;
struct TYPE_16__ {TYPE_8__ symtab_hdr; } ;
typedef  TYPE_8__ Elf_Internal_Shdr ;
typedef  TYPE_9__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 unsigned int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_X86_64_16 148 
#define  R_X86_64_32 147 
#define  R_X86_64_32S 146 
#define  R_X86_64_64 145 
#define  R_X86_64_8 144 
#define  R_X86_64_GOT32 143 
#define  R_X86_64_GOT64 142 
#define  R_X86_64_GOTPC32_TLSDESC 141 
#define  R_X86_64_GOTPCREL 140 
#define  R_X86_64_GOTPCREL64 139 
#define  R_X86_64_GOTPLT64 138 
#define  R_X86_64_GOTTPOFF 137 
#define  R_X86_64_PC16 136 
#define  R_X86_64_PC32 135 
#define  R_X86_64_PC64 134 
#define  R_X86_64_PC8 133 
#define  R_X86_64_PLT32 132 
#define  R_X86_64_PLTOFF64 131 
#define  R_X86_64_TLSDESC_CALL 130 
#define  R_X86_64_TLSGD 129 
#define  R_X86_64_TLSLD 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_13__* elf64_x86_64_hash_table (struct bfd_link_info*) ; 
 unsigned int elf64_x86_64_tls_transition (struct bfd_link_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int* elf_local_got_refcounts (int /*<<< orphan*/ *) ; 
 TYPE_11__* elf_section_data (TYPE_7__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_10__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_gc_sweep_hook (bfd *abfd, struct bfd_link_info *info,
			    asection *sec, const Elf_Internal_Rela *relocs)
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

      r_symndx = ELF64_R_SYM (rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct elf64_x86_64_link_hash_entry *eh;
	  struct elf64_x86_64_dyn_relocs **pp;
	  struct elf64_x86_64_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct elf64_x86_64_link_hash_entry *) h;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      r_type = ELF64_R_TYPE (rel->r_info);
      r_type = elf64_x86_64_tls_transition (info, r_type, h != NULL);
      switch (r_type)
	{
	case R_X86_64_TLSLD:
	  if (elf64_x86_64_hash_table (info)->tls_ld_got.refcount > 0)
	    elf64_x86_64_hash_table (info)->tls_ld_got.refcount -= 1;
	  break;

	case R_X86_64_TLSGD:
	case R_X86_64_GOTPC32_TLSDESC:
	case R_X86_64_TLSDESC_CALL:
	case R_X86_64_GOTTPOFF:
	case R_X86_64_GOT32:
	case R_X86_64_GOTPCREL:
	case R_X86_64_GOT64:
	case R_X86_64_GOTPCREL64:
	case R_X86_64_GOTPLT64:
	  if (h != NULL)
	    {
	      if (r_type == R_X86_64_GOTPLT64 && h->plt.refcount > 0)
	        h->plt.refcount -= 1;
	      if (h->got.refcount > 0)
		h->got.refcount -= 1;
	    }
	  else if (local_got_refcounts != NULL)
	    {
	      if (local_got_refcounts[r_symndx] > 0)
		local_got_refcounts[r_symndx] -= 1;
	    }
	  break;

	case R_X86_64_8:
	case R_X86_64_16:
	case R_X86_64_32:
	case R_X86_64_64:
	case R_X86_64_32S:
	case R_X86_64_PC8:
	case R_X86_64_PC16:
	case R_X86_64_PC32:
	case R_X86_64_PC64:
	  if (info->shared)
	    break;
	  /* Fall thru */

	case R_X86_64_PLT32:
	case R_X86_64_PLTOFF64:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		h->plt.refcount -= 1;
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}