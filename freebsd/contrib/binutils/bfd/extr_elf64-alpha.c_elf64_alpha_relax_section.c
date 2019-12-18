#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_29__ ;
typedef  struct TYPE_40__   TYPE_28__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct bfd_link_info {scalar_t__ relax_trip; int /*<<< orphan*/  keep_memory; scalar_t__ relocatable; } ;
struct alpha_relax_info {TYPE_10__* contents; scalar_t__ changed_relocs; scalar_t__ changed_contents; struct alpha_elf_got_entry* gotent; TYPE_22__* tsec; int /*<<< orphan*/ * gotobj; struct alpha_elf_got_entry** first_gotent; int /*<<< orphan*/  other; struct alpha_elf_link_hash_entry* h; struct bfd_link_info* link_info; scalar_t__ gp; TYPE_10__* relend; TYPE_10__* relocs; TYPE_11__* symtab_hdr; TYPE_9__* sec; int /*<<< orphan*/ * abfd; } ;
struct TYPE_43__ {scalar_t__ value; TYPE_22__* section; } ;
struct TYPE_42__ {scalar_t__ link; } ;
struct TYPE_44__ {TYPE_3__ def; TYPE_2__ i; } ;
struct TYPE_45__ {scalar_t__ type; TYPE_4__ u; } ;
struct TYPE_46__ {int /*<<< orphan*/  other; TYPE_5__ root; int /*<<< orphan*/  def_regular; } ;
struct alpha_elf_link_hash_entry {struct alpha_elf_got_entry* got_entries; TYPE_6__ root; } ;
struct alpha_elf_got_entry {unsigned long reloc_type; scalar_t__ addend; int /*<<< orphan*/ * gotobj; struct alpha_elf_got_entry* next; } ;
typedef  int /*<<< orphan*/  info ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_49__ {int flags; scalar_t__ reloc_count; scalar_t__ output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_9__ asection ;
struct TYPE_48__ {TYPE_10__* contents; } ;
struct TYPE_47__ {scalar_t__ vma; } ;
struct TYPE_41__ {scalar_t__ relax_trip; } ;
struct TYPE_40__ {TYPE_9__* got; int /*<<< orphan*/ * gotobj; struct alpha_elf_got_entry** local_got_entries; } ;
struct TYPE_39__ {scalar_t__ output_offset; TYPE_7__* output_section; } ;
struct TYPE_38__ {scalar_t__ vma; } ;
struct TYPE_37__ {scalar_t__ dynamic_sections_created; } ;
struct TYPE_36__ {TYPE_10__* relocs; TYPE_8__ this_hdr; } ;
struct TYPE_34__ {unsigned long sh_info; unsigned char* contents; } ;
struct TYPE_35__ {TYPE_11__ symtab_hdr; } ;
struct TYPE_33__ {scalar_t__ st_value; scalar_t__ st_shndx; scalar_t__ r_addend; int /*<<< orphan*/  r_info; int /*<<< orphan*/  st_other; } ;
typedef  int /*<<< orphan*/  PTR ;
typedef  TYPE_10__ Elf_Internal_Sym ;
typedef  TYPE_11__ Elf_Internal_Shdr ;
typedef  TYPE_10__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 unsigned long ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 unsigned long ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
#define  R_ALPHA_GOTDTPREL 134 
#define  R_ALPHA_GOTTPREL 133 
#define  R_ALPHA_GPRELHIGH 132 
#define  R_ALPHA_GPRELLOW 131 
#define  R_ALPHA_LITERAL 130 
 unsigned long R_ALPHA_LITUSE ; 
#define  R_ALPHA_TLSGD 129 
#define  R_ALPHA_TLSLDM 128 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_RELOC ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_COMMON ; 
 scalar_t__ SHN_UNDEF ; 
 int TRUE ; 
 TYPE_10__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_29__* alpha_elf_hash_table (struct bfd_link_info*) ; 
 struct alpha_elf_link_hash_entry** alpha_elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_28__* alpha_elf_tdata (int /*<<< orphan*/ *) ; 
 scalar_t__ alpha_get_tprel_base (struct bfd_link_info*) ; 
 void* bfd_abs_section_ptr ; 
 TYPE_22__* bfd_com_section_ptr ; 
 TYPE_10__* bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_11__*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_9__*,TYPE_10__**) ; 
 TYPE_22__* bfd_section_from_elf_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  elf64_alpha_relax_got_load (struct alpha_relax_info*,scalar_t__,TYPE_10__*,unsigned long) ; 
 int /*<<< orphan*/  elf64_alpha_relax_tls_get_addr (struct alpha_relax_info*,scalar_t__,TYPE_10__*,int) ; 
 int /*<<< orphan*/  elf64_alpha_relax_with_lituse (struct alpha_relax_info*,scalar_t__,TYPE_10__*) ; 
 int /*<<< orphan*/  elf64_alpha_size_got_sections (struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf64_alpha_size_plt_section (struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf64_alpha_size_rela_got_section (struct bfd_link_info*) ; 
 TYPE_17__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_15__* elf_section_data (TYPE_9__*) ; 
 TYPE_14__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_10__*) ; 
 int /*<<< orphan*/  memset (struct alpha_relax_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfd_boolean
elf64_alpha_relax_section (bfd *abfd, asection *sec,
			   struct bfd_link_info *link_info, bfd_boolean *again)
{
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Rela *internal_relocs;
  Elf_Internal_Rela *irel, *irelend;
  Elf_Internal_Sym *isymbuf = NULL;
  struct alpha_elf_got_entry **local_got_entries;
  struct alpha_relax_info info;

  /* There's nothing to change, yet.  */
  *again = FALSE;

  if (link_info->relocatable
      || ((sec->flags & (SEC_CODE | SEC_RELOC | SEC_ALLOC))
	  != (SEC_CODE | SEC_RELOC | SEC_ALLOC))
      || sec->reloc_count == 0)
    return TRUE;

  /* Make sure our GOT and PLT tables are up-to-date.  */
  if (alpha_elf_hash_table(link_info)->relax_trip != link_info->relax_trip)
    {
      alpha_elf_hash_table(link_info)->relax_trip = link_info->relax_trip;

      /* This should never fail after the initial round, since the only
	 error is GOT overflow, and relaxation only shrinks the table.  */
      if (!elf64_alpha_size_got_sections (link_info))
	abort ();
      if (elf_hash_table (link_info)->dynamic_sections_created)
	{
	  elf64_alpha_size_plt_section (link_info);
	  elf64_alpha_size_rela_got_section (link_info);
	}
    }

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  local_got_entries = alpha_elf_tdata(abfd)->local_got_entries;

  /* Load the relocations for this section.  */
  internal_relocs = (_bfd_elf_link_read_relocs
		     (abfd, sec, (PTR) NULL, (Elf_Internal_Rela *) NULL,
		      link_info->keep_memory));
  if (internal_relocs == NULL)
    return FALSE;

  memset(&info, 0, sizeof (info));
  info.abfd = abfd;
  info.sec = sec;
  info.link_info = link_info;
  info.symtab_hdr = symtab_hdr;
  info.relocs = internal_relocs;
  info.relend = irelend = internal_relocs + sec->reloc_count;

  /* Find the GP for this object.  Do not store the result back via
     _bfd_set_gp_value, since this could change again before final.  */
  info.gotobj = alpha_elf_tdata (abfd)->gotobj;
  if (info.gotobj)
    {
      asection *sgot = alpha_elf_tdata (info.gotobj)->got;
      info.gp = (sgot->output_section->vma
		 + sgot->output_offset
		 + 0x8000);
    }

  /* Get the section contents.  */
  if (elf_section_data (sec)->this_hdr.contents != NULL)
    info.contents = elf_section_data (sec)->this_hdr.contents;
  else
    {
      if (!bfd_malloc_and_get_section (abfd, sec, &info.contents))
	goto error_return;
    }

  for (irel = internal_relocs; irel < irelend; irel++)
    {
      bfd_vma symval;
      struct alpha_elf_got_entry *gotent;
      unsigned long r_type = ELF64_R_TYPE (irel->r_info);
      unsigned long r_symndx = ELF64_R_SYM (irel->r_info);

      /* Early exit for unhandled or unrelaxable relocations.  */
      switch (r_type)
	{
	case R_ALPHA_LITERAL:
	case R_ALPHA_GPRELHIGH:
	case R_ALPHA_GPRELLOW:
	case R_ALPHA_GOTDTPREL:
	case R_ALPHA_GOTTPREL:
	case R_ALPHA_TLSGD:
	  break;

	case R_ALPHA_TLSLDM:
	  /* The symbol for a TLSLDM reloc is ignored.  Collapse the
             reloc to the 0 symbol so that they all match.  */
	  r_symndx = 0;
	  break;

	default:
	  continue;
	}

      /* Get the value of the symbol referred to by the reloc.  */
      if (r_symndx < symtab_hdr->sh_info)
	{
	  /* A local symbol.  */
	  Elf_Internal_Sym *isym;

	  /* Read this BFD's local symbols.  */
	  if (isymbuf == NULL)
	    {
	      isymbuf = (Elf_Internal_Sym *) symtab_hdr->contents;
	      if (isymbuf == NULL)
		isymbuf = bfd_elf_get_elf_syms (abfd, symtab_hdr,
						symtab_hdr->sh_info, 0,
						NULL, NULL, NULL);
	      if (isymbuf == NULL)
		goto error_return;
	    }

	  isym = isymbuf + r_symndx;

	  /* Given the symbol for a TLSLDM reloc is ignored, this also
	     means forcing the symbol value to the tp base.  */
	  if (r_type == R_ALPHA_TLSLDM)
	    {
	      info.tsec = bfd_abs_section_ptr;
	      symval = alpha_get_tprel_base (info.link_info);
	    }
	  else
	    {
	      symval = isym->st_value;
	      if (isym->st_shndx == SHN_UNDEF)
	        continue;
	      else if (isym->st_shndx == SHN_ABS)
	        info.tsec = bfd_abs_section_ptr;
	      else if (isym->st_shndx == SHN_COMMON)
	        info.tsec = bfd_com_section_ptr;
	      else
	        info.tsec = bfd_section_from_elf_index (abfd, isym->st_shndx);
	    }

	  info.h = NULL;
	  info.other = isym->st_other;
	  if (local_got_entries)
	    info.first_gotent = &local_got_entries[r_symndx];
	  else
	    {
	      info.first_gotent = &info.gotent;
	      info.gotent = NULL;
	    }
	}
      else
	{
	  unsigned long indx;
	  struct alpha_elf_link_hash_entry *h;

	  indx = r_symndx - symtab_hdr->sh_info;
	  h = alpha_elf_sym_hashes (abfd)[indx];
	  BFD_ASSERT (h != NULL);

	  while (h->root.root.type == bfd_link_hash_indirect
		 || h->root.root.type == bfd_link_hash_warning)
	    h = (struct alpha_elf_link_hash_entry *)h->root.root.u.i.link;

	  /* If the symbol is undefined, we can't do anything with it.  */
	  if (h->root.root.type == bfd_link_hash_undefined)
	    continue;

	  /* If the symbol isn't defined in the current module,
	     again we can't do anything.  */
	  if (h->root.root.type == bfd_link_hash_undefweak)
	    {
	      info.tsec = bfd_abs_section_ptr;
	      symval = 0;
	    }
	  else if (!h->root.def_regular)
	    {
	      /* Except for TLSGD relocs, which can sometimes be
		 relaxed to GOTTPREL relocs.  */
	      if (r_type != R_ALPHA_TLSGD)
		continue;
	      info.tsec = bfd_abs_section_ptr;
	      symval = 0;
	    }
	  else
	    {
	      info.tsec = h->root.root.u.def.section;
	      symval = h->root.root.u.def.value;
	    }

	  info.h = h;
	  info.other = h->root.other;
	  info.first_gotent = &h->got_entries;
	}

      /* Search for the got entry to be used by this relocation.  */
      for (gotent = *info.first_gotent; gotent ; gotent = gotent->next)
	if (gotent->gotobj == info.gotobj
	    && gotent->reloc_type == r_type
	    && gotent->addend == irel->r_addend)
	  break;
      info.gotent = gotent;

      symval += info.tsec->output_section->vma + info.tsec->output_offset;
      symval += irel->r_addend;

      switch (r_type)
	{
	case R_ALPHA_LITERAL:
	  BFD_ASSERT(info.gotent != NULL);

	  /* If there exist LITUSE relocations immediately following, this
	     opens up all sorts of interesting optimizations, because we
	     now know every location that this address load is used.  */
	  if (irel+1 < irelend
	      && ELF64_R_TYPE (irel[1].r_info) == R_ALPHA_LITUSE)
	    {
	      if (!elf64_alpha_relax_with_lituse (&info, symval, irel))
		goto error_return;
	    }
	  else
	    {
	      if (!elf64_alpha_relax_got_load (&info, symval, irel, r_type))
		goto error_return;
	    }
	  break;

	case R_ALPHA_GOTDTPREL:
	case R_ALPHA_GOTTPREL:
	  BFD_ASSERT(info.gotent != NULL);
	  if (!elf64_alpha_relax_got_load (&info, symval, irel, r_type))
	    goto error_return;
	  break;

	case R_ALPHA_TLSGD:
	case R_ALPHA_TLSLDM:
	  BFD_ASSERT(info.gotent != NULL);
	  if (!elf64_alpha_relax_tls_get_addr (&info, symval, irel,
					       r_type == R_ALPHA_TLSGD))
	    goto error_return;
	  break;
	}
    }

  if (isymbuf != NULL
      && symtab_hdr->contents != (unsigned char *) isymbuf)
    {
      if (!link_info->keep_memory)
	free (isymbuf);
      else
	{
	  /* Cache the symbols for elf_link_input_bfd.  */
	  symtab_hdr->contents = (unsigned char *) isymbuf;
	}
    }

  if (info.contents != NULL
      && elf_section_data (sec)->this_hdr.contents != info.contents)
    {
      if (!info.changed_contents && !link_info->keep_memory)
	free (info.contents);
      else
	{
	  /* Cache the section contents for elf_link_input_bfd.  */
	  elf_section_data (sec)->this_hdr.contents = info.contents;
	}
    }

  if (elf_section_data (sec)->relocs != internal_relocs)
    {
      if (!info.changed_relocs)
	free (internal_relocs);
      else
	elf_section_data (sec)->relocs = internal_relocs;
    }

  *again = info.changed_contents || info.changed_relocs;

  return TRUE;

 error_return:
  if (isymbuf != NULL
      && symtab_hdr->contents != (unsigned char *) isymbuf)
    free (isymbuf);
  if (info.contents != NULL
      && elf_section_data (sec)->this_hdr.contents != info.contents)
    free (info.contents);
  if (internal_relocs != NULL
      && elf_section_data (sec)->relocs != internal_relocs)
    free (internal_relocs);
  return FALSE;
}