#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_21__ ;
typedef  struct TYPE_39__   TYPE_20__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_11__ ;

/* Type definitions */
struct spu_stub_hash_entry {scalar_t__ off; } ;
struct spu_link_hash_table {TYPE_3__* stub; int /*<<< orphan*/  stub_hash_table; } ;
struct TYPE_38__ {char* string; } ;
struct TYPE_37__ {TYPE_1__ root; } ;
struct elf_link_hash_entry {TYPE_11__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  emitrelocations; scalar_t__ relocatable; TYPE_4__* callbacks; } ;
struct TYPE_44__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ reloc_howto_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_45__ {int reloc_count; } ;
typedef  TYPE_6__ asection ;
struct TYPE_47__ {int r_offset; scalar_t__ r_info; scalar_t__ r_addend; } ;
struct TYPE_46__ {unsigned long sh_info; int sh_size; int sh_entsize; } ;
struct TYPE_43__ {int /*<<< orphan*/  (* warning ) (struct bfd_link_info*,char const*,char const*,int /*<<< orphan*/ *,TYPE_6__*,int) ;int /*<<< orphan*/  (* undefined_symbol ) (struct bfd_link_info*,char const*,int /*<<< orphan*/ *,TYPE_6__*,int,int) ;int /*<<< orphan*/  (* reloc_overflow ) (struct bfd_link_info*,TYPE_11__*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_6__*,int) ;} ;
struct TYPE_42__ {scalar_t__ output_offset; TYPE_2__* output_section; } ;
struct TYPE_41__ {scalar_t__ vma; } ;
struct TYPE_40__ {TYPE_7__ rel_hdr; } ;
struct TYPE_39__ {TYPE_7__ symtab_hdr; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;
typedef  TYPE_7__ Elf_Internal_Shdr ;
typedef  TYPE_8__ Elf_Internal_Rela ;

/* Variables and functions */
 unsigned long ELF32_R_SYM (scalar_t__) ; 
 int ELF32_R_TYPE (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  RELOC_FOR_GLOBAL_SYMBOL (struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_6__*,TYPE_8__*,unsigned long,TYPE_7__*,struct elf_link_hash_entry**,struct elf_link_hash_entry*,TYPE_6__*,scalar_t__,int,int) ; 
 int R_SPU_PPU32 ; 
 int R_SPU_PPU64 ; 
 int TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_clear_contents (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _bfd_elf_rela_local_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__**,TYPE_8__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,char const*) ; 
 int _bfd_final_link_relocate (TYPE_5__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 char* bfd_elf_sym_name (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  bfd_get_section_name (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char*,int,int) ; 
#define  bfd_reloc_dangerous 132 
#define  bfd_reloc_notsupported 131 
 int bfd_reloc_ok ; 
#define  bfd_reloc_outofrange 130 
#define  bfd_reloc_overflow 129 
#define  bfd_reloc_undefined 128 
 scalar_t__ elf_discarded_section (TYPE_6__*) ; 
 TYPE_5__* elf_howto_table ; 
 TYPE_21__* elf_section_data (TYPE_6__*) ; 
 scalar_t__ elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_20__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_branch (int /*<<< orphan*/ *) ; 
 scalar_t__ is_hint (int /*<<< orphan*/ *) ; 
 scalar_t__ needs_ovl_stub (char const*,TYPE_6__*,TYPE_6__*,struct spu_link_hash_table*,int) ; 
 struct spu_link_hash_table* spu_hash_table (struct bfd_link_info*) ; 
 char* spu_stub_name (TYPE_6__*,struct elf_link_hash_entry*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub2 (struct bfd_link_info*,TYPE_11__*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub3 (struct bfd_link_info*,char const*,int /*<<< orphan*/ *,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct bfd_link_info*,char const*,char const*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 

__attribute__((used)) static bfd_boolean
spu_elf_relocate_section (bfd *output_bfd,
			  struct bfd_link_info *info,
			  bfd *input_bfd,
			  asection *input_section,
			  bfd_byte *contents,
			  Elf_Internal_Rela *relocs,
			  Elf_Internal_Sym *local_syms,
			  asection **local_sections)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  Elf_Internal_Rela *rel, *relend;
  struct spu_link_hash_table *htab;
  bfd_boolean ret = TRUE;
  bfd_boolean emit_these_relocs = FALSE;

  htab = spu_hash_table (info);
  symtab_hdr = &elf_tdata (input_bfd)->symtab_hdr;
  sym_hashes = (struct elf_link_hash_entry **) (elf_sym_hashes (input_bfd));

  rel = relocs;
  relend = relocs + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      int r_type;
      reloc_howto_type *howto;
      unsigned long r_symndx;
      Elf_Internal_Sym *sym;
      asection *sec;
      struct elf_link_hash_entry *h;
      const char *sym_name;
      bfd_vma relocation;
      bfd_vma addend;
      bfd_reloc_status_type r;
      bfd_boolean unresolved_reloc;
      bfd_boolean warned;
      bfd_boolean branch;

      r_symndx = ELF32_R_SYM (rel->r_info);
      r_type = ELF32_R_TYPE (rel->r_info);
      if (r_type == R_SPU_PPU32 || r_type == R_SPU_PPU64)
	{
	  emit_these_relocs = TRUE;
	  continue;
	}

      howto = elf_howto_table + r_type;
      unresolved_reloc = FALSE;
      warned = FALSE;
      h = NULL;
      sym = NULL;
      sec = NULL;
      if (r_symndx < symtab_hdr->sh_info)
	{
	  sym = local_syms + r_symndx;
	  sec = local_sections[r_symndx];
	  sym_name = bfd_elf_sym_name (input_bfd, symtab_hdr, sym, sec);
	  relocation = _bfd_elf_rela_local_sym (output_bfd, sym, &sec, rel);
	}
      else
	{
	  RELOC_FOR_GLOBAL_SYMBOL (info, input_bfd, input_section, rel,
				   r_symndx, symtab_hdr, sym_hashes,
				   h, sec, relocation,
				   unresolved_reloc, warned);
	  sym_name = h->root.root.string;
	}

      if (sec != NULL && elf_discarded_section (sec))
	{
	  /* For relocs against symbols from removed linkonce sections,
	     or sections discarded by a linker script, we just want the
	     section contents zeroed.  Avoid any special processing.  */
	  _bfd_clear_contents (howto, input_bfd, contents + rel->r_offset);
	  rel->r_info = 0;
	  rel->r_addend = 0;
	  continue;
	}

      if (info->relocatable)
	continue;

      if (unresolved_reloc)
	{
	  (*_bfd_error_handler)
	    (_("%B(%s+0x%lx): unresolvable %s relocation against symbol `%s'"),
	     input_bfd,
	     bfd_get_section_name (input_bfd, input_section),
	     (long) rel->r_offset,
	     howto->name,
	     sym_name);
	  ret = FALSE;
	}

      /* If this symbol is in an overlay area, we may need to relocate
	 to the overlay stub.  */
      addend = rel->r_addend;
      branch = (is_branch (contents + rel->r_offset)
		|| is_hint (contents + rel->r_offset));
      if (needs_ovl_stub (sym_name, sec, input_section, htab, branch))
	{
	  char *stub_name;
	  struct spu_stub_hash_entry *sh;

	  stub_name = spu_stub_name (sec, h, rel);
	  if (stub_name == NULL)
	    return FALSE;

	  sh = (struct spu_stub_hash_entry *)
	    bfd_hash_lookup (&htab->stub_hash_table, stub_name, FALSE, FALSE);
	  if (sh != NULL)
	    {
	      relocation = (htab->stub->output_section->vma
			    + htab->stub->output_offset
			    + sh->off);
	      addend = 0;
	    }
	  free (stub_name);
	}

      r = _bfd_final_link_relocate (howto,
				    input_bfd,
				    input_section,
				    contents,
				    rel->r_offset, relocation, addend);

      if (r != bfd_reloc_ok)
	{
	  const char *msg = (const char *) 0;

	  switch (r)
	    {
	    case bfd_reloc_overflow:
	      if (!((*info->callbacks->reloc_overflow)
		    (info, (h ? &h->root : NULL), sym_name, howto->name,
		     (bfd_vma) 0, input_bfd, input_section, rel->r_offset)))
		return FALSE;
	      break;

	    case bfd_reloc_undefined:
	      if (!((*info->callbacks->undefined_symbol)
		    (info, sym_name, input_bfd, input_section,
		     rel->r_offset, TRUE)))
		return FALSE;
	      break;

	    case bfd_reloc_outofrange:
	      msg = _("internal error: out of range error");
	      goto common_error;

	    case bfd_reloc_notsupported:
	      msg = _("internal error: unsupported relocation error");
	      goto common_error;

	    case bfd_reloc_dangerous:
	      msg = _("internal error: dangerous error");
	      goto common_error;

	    default:
	      msg = _("internal error: unknown error");
	      /* fall through */

	    common_error:
	      if (!((*info->callbacks->warning)
		    (info, msg, sym_name, input_bfd, input_section,
		     rel->r_offset)))
		return FALSE;
	      break;
	    }
	}
    }

  if (ret
      && emit_these_relocs
      && !info->relocatable
      && !info->emitrelocations)
    {
      Elf_Internal_Rela *wrel;
      Elf_Internal_Shdr *rel_hdr;

      wrel = rel = relocs;
      relend = relocs + input_section->reloc_count;
      for (; rel < relend; rel++)
	{
	  int r_type;

	  r_type = ELF32_R_TYPE (rel->r_info);
	  if (r_type == R_SPU_PPU32 || r_type == R_SPU_PPU64)
	    *wrel++ = *rel;
	}
      input_section->reloc_count = wrel - relocs;
      /* Backflips for _bfd_elf_link_output_relocs.  */
      rel_hdr = &elf_section_data (input_section)->rel_hdr;
      rel_hdr->sh_size = input_section->reloc_count * rel_hdr->sh_entsize;
      ret = 2;
    }

  return ret;
}