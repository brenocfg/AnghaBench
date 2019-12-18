#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {scalar_t__ value; TYPE_7__* section; } ;
struct TYPE_31__ {scalar_t__ link; } ;
struct TYPE_33__ {TYPE_2__ def; TYPE_1__ i; } ;
struct TYPE_34__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_36__ {TYPE_7__* sections; } ;
typedef  TYPE_6__ bfd ;
struct TYPE_37__ {scalar_t__ reloc_count; scalar_t__ vma; int flags; scalar_t__ output_offset; TYPE_5__* output_section; struct TYPE_37__* next; TYPE_6__* owner; } ;
typedef  TYPE_7__ asection ;
struct TYPE_39__ {unsigned long sh_info; int /*<<< orphan*/ * contents; } ;
struct TYPE_38__ {scalar_t__ st_value; scalar_t__ st_shndx; } ;
struct TYPE_35__ {scalar_t__ vma; } ;
struct TYPE_30__ {TYPE_9__ symtab_hdr; } ;
struct TYPE_29__ {TYPE_10__* opd_relocs; } ;
struct TYPE_28__ {scalar_t__ r_offset; scalar_t__ r_addend; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_8__ Elf_Internal_Sym ;
typedef  TYPE_9__ Elf_Internal_Shdr ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 unsigned long ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_PPC64_ADDR64 ; 
 scalar_t__ R_PPC64_TOC ; 
 int SEC_ALLOC ; 
 int SEC_LOAD ; 
 int SEC_MERGE ; 
 scalar_t__ SHN_HIRESERVE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_10__* _bfd_elf_link_read_relocs (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__* bfd_elf_get_elf_syms (TYPE_6__*,TYPE_9__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_section_contents (TYPE_6__*,TYPE_7__*,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_7__* bfd_section_from_elf_index (TYPE_6__*,scalar_t__) ; 
 struct elf_link_hash_entry** elf_sym_hashes (TYPE_6__*) ; 
 TYPE_15__* elf_tdata (TYPE_6__*) ; 
 TYPE_11__* ppc64_elf_tdata (TYPE_6__*) ; 

__attribute__((used)) static bfd_vma
opd_entry_value (asection *opd_sec,
		 bfd_vma offset,
		 asection **code_sec,
		 bfd_vma *code_off)
{
  bfd *opd_bfd = opd_sec->owner;
  Elf_Internal_Rela *relocs;
  Elf_Internal_Rela *lo, *hi, *look;
  bfd_vma val;

  /* No relocs implies we are linking a --just-symbols object.  */
  if (opd_sec->reloc_count == 0)
    {
      bfd_vma val;

      if (!bfd_get_section_contents (opd_bfd, opd_sec, &val, offset, 8))
	return (bfd_vma) -1;

      if (code_sec != NULL)
	{
	  asection *sec, *likely = NULL;
	  for (sec = opd_bfd->sections; sec != NULL; sec = sec->next)
	    if (sec->vma <= val
		&& (sec->flags & SEC_LOAD) != 0
		&& (sec->flags & SEC_ALLOC) != 0)
	      likely = sec;
	  if (likely != NULL)
	    {
	      *code_sec = likely;
	      if (code_off != NULL)
		*code_off = val - likely->vma;
	    }
	}
      return val;
    }

  relocs = ppc64_elf_tdata (opd_bfd)->opd_relocs;
  if (relocs == NULL)
    relocs = _bfd_elf_link_read_relocs (opd_bfd, opd_sec, NULL, NULL, TRUE);

  /* Go find the opd reloc at the sym address.  */
  lo = relocs;
  BFD_ASSERT (lo != NULL);
  hi = lo + opd_sec->reloc_count - 1; /* ignore last reloc */
  val = (bfd_vma) -1;
  while (lo < hi)
    {
      look = lo + (hi - lo) / 2;
      if (look->r_offset < offset)
	lo = look + 1;
      else if (look->r_offset > offset)
	hi = look;
      else
	{
	  Elf_Internal_Shdr *symtab_hdr = &elf_tdata (opd_bfd)->symtab_hdr;
	  if (ELF64_R_TYPE (look->r_info) == R_PPC64_ADDR64
	      && ELF64_R_TYPE ((look + 1)->r_info) == R_PPC64_TOC)
	    {
	      unsigned long symndx = ELF64_R_SYM (look->r_info);
	      asection *sec;

	      if (symndx < symtab_hdr->sh_info)
		{
		  Elf_Internal_Sym *sym;

		  sym = (Elf_Internal_Sym *) symtab_hdr->contents;
		  if (sym == NULL)
		    {
		      sym = bfd_elf_get_elf_syms (opd_bfd, symtab_hdr,
						  symtab_hdr->sh_info,
						  0, NULL, NULL, NULL);
		      if (sym == NULL)
			break;
		      symtab_hdr->contents = (bfd_byte *) sym;
		    }

		  sym += symndx;
		  val = sym->st_value;
		  sec = NULL;
		  if ((sym->st_shndx != SHN_UNDEF
		       && sym->st_shndx < SHN_LORESERVE)
		      || sym->st_shndx > SHN_HIRESERVE)
		    sec = bfd_section_from_elf_index (opd_bfd, sym->st_shndx);
		  BFD_ASSERT ((sec->flags & SEC_MERGE) == 0);
		}
	      else
		{
		  struct elf_link_hash_entry **sym_hashes;
		  struct elf_link_hash_entry *rh;

		  sym_hashes = elf_sym_hashes (opd_bfd);
		  rh = sym_hashes[symndx - symtab_hdr->sh_info];
		  while (rh->root.type == bfd_link_hash_indirect
			 || rh->root.type == bfd_link_hash_warning)
		    rh = ((struct elf_link_hash_entry *) rh->root.u.i.link);
		  BFD_ASSERT (rh->root.type == bfd_link_hash_defined
			      || rh->root.type == bfd_link_hash_defweak);
		  val = rh->root.u.def.value;
		  sec = rh->root.u.def.section;
		}
	      val += look->r_addend;
	      if (code_off != NULL)
		*code_off = val;
	      if (code_sec != NULL)
		*code_sec = sec;
	      if (sec != NULL && sec->output_section != NULL)
		val += sec->output_section->vma + sec->output_offset;
	    }
	  break;
	}
    }

  return val;
}