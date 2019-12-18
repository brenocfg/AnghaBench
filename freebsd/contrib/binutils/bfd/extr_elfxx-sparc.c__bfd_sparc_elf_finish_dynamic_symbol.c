#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_19__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  string; } ;
struct TYPE_28__ {scalar_t__ value; TYPE_12__* section; } ;
struct TYPE_29__ {TYPE_1__ def; } ;
struct TYPE_31__ {TYPE_3__ root; TYPE_2__ u; } ;
struct TYPE_23__ {scalar_t__ offset; } ;
struct TYPE_35__ {scalar_t__ offset; } ;
struct elf_link_hash_entry {int dynindx; TYPE_4__ root; scalar_t__ needs_copy; TYPE_11__ got; scalar_t__ def_regular; int /*<<< orphan*/  ref_regular_nonweak; TYPE_8__ plt; } ;
struct elf_backend_data {TYPE_9__* s; } ;
struct bfd_link_info {scalar_t__ symbolic; scalar_t__ shared; } ;
struct TYPE_32__ {struct elf_link_hash_entry* hplt; struct elf_link_hash_entry* hgot; int /*<<< orphan*/ * dynobj; } ;
struct _bfd_sparc_elf_link_hash_table {int plt_header_size; int plt_entry_size; TYPE_5__ elf; scalar_t__ is_vxworks; TYPE_12__* srelgot; TYPE_12__* sgot; TYPE_7__* sgotplt; TYPE_12__* srelplt; TYPE_12__* splt; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_24__ {scalar_t__ output_offset; TYPE_10__* output_section; int /*<<< orphan*/  owner; int /*<<< orphan*/ * contents; int /*<<< orphan*/  size; } ;
typedef  TYPE_12__ asection ;
struct TYPE_36__ {int sizeof_rela; int /*<<< orphan*/  (* swap_reloca_out ) (int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_34__ {scalar_t__ output_offset; TYPE_6__* output_section; } ;
struct TYPE_33__ {scalar_t__ vma; } ;
struct TYPE_27__ {scalar_t__ tls_type; } ;
struct TYPE_26__ {scalar_t__ r_offset; scalar_t__ r_addend; void* r_info; } ;
struct TYPE_25__ {int /*<<< orphan*/  st_shndx; scalar_t__ st_value; } ;
struct TYPE_22__ {scalar_t__ vma; } ;
typedef  TYPE_13__ Elf_Internal_Sym ;
typedef  TYPE_14__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_64_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ GOT_TLS_GD ; 
 scalar_t__ GOT_TLS_IE ; 
 int PLT64_ENTRY_SIZE ; 
 int PLT64_LARGE_THRESHOLD ; 
 int /*<<< orphan*/  R_SPARC_COPY ; 
 int /*<<< orphan*/  R_SPARC_GLOB_DAT ; 
 int /*<<< orphan*/  R_SPARC_JMP_SLOT ; 
 int /*<<< orphan*/  R_SPARC_RELATIVE ; 
 int /*<<< orphan*/  SHN_ABS ; 
 int /*<<< orphan*/  SHN_UNDEF ; 
 int SPARC_ELF_BUILD_PLT_ENTRY (struct _bfd_sparc_elf_link_hash_table*,int /*<<< orphan*/ *,TYPE_12__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SPARC_ELF_PUT_WORD (struct _bfd_sparc_elf_link_hash_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* SPARC_ELF_R_INFO (struct _bfd_sparc_elf_link_hash_table*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_19__* _bfd_sparc_elf_hash_entry (struct elf_link_hash_entry*) ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 TYPE_12__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_elf_append_rela (int /*<<< orphan*/ *,TYPE_12__*,TYPE_14__*) ; 
 int /*<<< orphan*/  sparc_vxworks_build_plt_entry (int /*<<< orphan*/ *,struct bfd_link_info*,int,int,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_sparc_elf_finish_dynamic_symbol (bfd *output_bfd,
				      struct bfd_link_info *info,
				      struct elf_link_hash_entry *h,
				      Elf_Internal_Sym *sym)
{
  bfd *dynobj;
  struct _bfd_sparc_elf_link_hash_table *htab;
  const struct elf_backend_data *bed;

  htab = _bfd_sparc_elf_hash_table (info);
  dynobj = htab->elf.dynobj;
  bed = get_elf_backend_data (output_bfd);

  if (h->plt.offset != (bfd_vma) -1)
    {
      asection *splt;
      asection *srela;
      Elf_Internal_Rela rela;
      bfd_byte *loc;
      bfd_vma r_offset, got_offset;
      int rela_index;

      /* This symbol has an entry in the PLT.  Set it up.  */

      BFD_ASSERT (h->dynindx != -1);

      splt = htab->splt;
      srela = htab->srelplt;
      BFD_ASSERT (splt != NULL && srela != NULL);

      /* Fill in the entry in the .rela.plt section.  */
      if (htab->is_vxworks)
	{
	  /* Work out the index of this PLT entry.  */
	  rela_index = ((h->plt.offset - htab->plt_header_size)
			/ htab->plt_entry_size);

	  /* Calculate the offset of the associated .got.plt entry.
	     The first three entries are reserved.  */
	  got_offset = (rela_index + 3) * 4;

	  sparc_vxworks_build_plt_entry (output_bfd, info, h->plt.offset,
					 rela_index, got_offset);


	  /* On VxWorks, the relocation points to the .got.plt entry,
	     not the .plt entry.  */
	  rela.r_offset = (htab->sgotplt->output_section->vma
			   + htab->sgotplt->output_offset
			   + got_offset);
	  rela.r_addend = 0;
	}
      else
	{
	  /* Fill in the entry in the procedure linkage table.  */
	  rela_index = SPARC_ELF_BUILD_PLT_ENTRY (htab, output_bfd, splt,
						  h->plt.offset, splt->size,
						  &r_offset);

	  rela.r_offset = r_offset
	    + (splt->output_section->vma + splt->output_offset);
	  if (! ABI_64_P (output_bfd)
	      || h->plt.offset < (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE))
	    {
	      rela.r_addend = 0;
	    }
	  else
	    {
	      rela.r_addend = (-(h->plt.offset + 4)
			       - splt->output_section->vma
			       - splt->output_offset);
	    }
	}
      rela.r_info = SPARC_ELF_R_INFO (htab, NULL, h->dynindx, R_SPARC_JMP_SLOT);

      /* Adjust for the first 4 reserved elements in the .plt section
	 when setting the offset in the .rela.plt section.
	 Sun forgot to read their own ABI and copied elf32-sparc behaviour,
	 thus .plt[4] has corresponding .rela.plt[0] and so on.  */

      loc = srela->contents;
      loc += rela_index * bed->s->sizeof_rela;
      bed->s->swap_reloca_out (output_bfd, &rela, loc);

      if (!h->def_regular)
	{
	  /* Mark the symbol as undefined, rather than as defined in
	     the .plt section.  Leave the value alone.  */
	  sym->st_shndx = SHN_UNDEF;
	  /* If the symbol is weak, we do need to clear the value.
	     Otherwise, the PLT entry would provide a definition for
	     the symbol even if the symbol wasn't defined anywhere,
	     and so the symbol would never be NULL.  */
	  if (!h->ref_regular_nonweak)
	    sym->st_value = 0;
	}
    }

  if (h->got.offset != (bfd_vma) -1
      && _bfd_sparc_elf_hash_entry(h)->tls_type != GOT_TLS_GD
      && _bfd_sparc_elf_hash_entry(h)->tls_type != GOT_TLS_IE)
    {
      asection *sgot;
      asection *srela;
      Elf_Internal_Rela rela;

      /* This symbol has an entry in the GOT.  Set it up.  */

      sgot = htab->sgot;
      srela = htab->srelgot;
      BFD_ASSERT (sgot != NULL && srela != NULL);

      rela.r_offset = (sgot->output_section->vma
		       + sgot->output_offset
		       + (h->got.offset &~ (bfd_vma) 1));

      /* If this is a -Bsymbolic link, and the symbol is defined
	 locally, we just want to emit a RELATIVE reloc.  Likewise if
	 the symbol was forced to be local because of a version file.
	 The entry in the global offset table will already have been
	 initialized in the relocate_section function.  */
      if (info->shared
	  && (info->symbolic || h->dynindx == -1)
	  && h->def_regular)
	{
	  asection *sec = h->root.u.def.section;
	  rela.r_info = SPARC_ELF_R_INFO (htab, NULL, 0, R_SPARC_RELATIVE);
	  rela.r_addend = (h->root.u.def.value
			   + sec->output_section->vma
			   + sec->output_offset);
	}
      else
	{
	  rela.r_info = SPARC_ELF_R_INFO (htab, NULL, h->dynindx, R_SPARC_GLOB_DAT);
	  rela.r_addend = 0;
	}

      SPARC_ELF_PUT_WORD (htab, output_bfd, 0,
			  sgot->contents + (h->got.offset & ~(bfd_vma) 1));
      sparc_elf_append_rela (output_bfd, srela, &rela);
    }

  if (h->needs_copy)
    {
      asection *s;
      Elf_Internal_Rela rela;

      /* This symbols needs a copy reloc.  Set it up.  */
      BFD_ASSERT (h->dynindx != -1);

      s = bfd_get_section_by_name (h->root.u.def.section->owner,
				   ".rela.bss");
      BFD_ASSERT (s != NULL);

      rela.r_offset = (h->root.u.def.value
		       + h->root.u.def.section->output_section->vma
		       + h->root.u.def.section->output_offset);
      rela.r_info = SPARC_ELF_R_INFO (htab, NULL, h->dynindx, R_SPARC_COPY);
      rela.r_addend = 0;
      sparc_elf_append_rela (output_bfd, s, &rela);
    }

  /* Mark some specially defined symbols as absolute.  On VxWorks,
     _GLOBAL_OFFSET_TABLE_ is not absolute: it is relative to the
     ".got" section.  Likewise _PROCEDURE_LINKAGE_TABLE_ and ".plt".  */
  if (strcmp (h->root.root.string, "_DYNAMIC") == 0
      || (!htab->is_vxworks
	  && (h == htab->elf.hgot || h == htab->elf.hplt)))
    sym->st_shndx = SHN_ABS;

  return TRUE;
}