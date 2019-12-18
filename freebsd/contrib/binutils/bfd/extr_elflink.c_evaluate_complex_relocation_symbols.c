#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {scalar_t__ string; } ;
struct TYPE_37__ {scalar_t__ link; } ;
struct TYPE_38__ {TYPE_4__ i; } ;
struct TYPE_40__ {scalar_t__ type; TYPE_6__ root; TYPE_5__ u; } ;
struct elf_link_hash_entry {scalar_t__ type; TYPE_7__ root; } ;
struct elf_final_link_info {TYPE_10__* internal_syms; TYPE_1__* info; } ;
struct elf_backend_data {TYPE_3__* s; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_41__ {char* filename; TYPE_9__* sections; } ;
typedef  TYPE_8__ bfd ;
struct TYPE_42__ {int flags; unsigned long reloc_count; int output_offset; char* name; TYPE_2__* output_section; int /*<<< orphan*/  linker_mark; struct TYPE_42__* next; } ;
typedef  TYPE_9__ asection ;
struct TYPE_36__ {int arch_size; } ;
struct TYPE_35__ {int vma; } ;
struct TYPE_34__ {TYPE_12__* relocs; } ;
struct TYPE_33__ {scalar_t__ relocatable; } ;
struct TYPE_30__ {int /*<<< orphan*/  sh_link; } ;
struct TYPE_32__ {TYPE_11__ symtab_hdr; } ;
struct TYPE_31__ {int r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_29__ {int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_10__ Elf_Internal_Sym ;
typedef  TYPE_11__ Elf_Internal_Shdr ;
typedef  TYPE_12__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int SEC_RELOC ; 
 int STN_UNDEF ; 
 scalar_t__ STT_RELC ; 
 scalar_t__ STT_SRELC ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_12__* _bfd_elf_link_read_relocs (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ *,TYPE_12__*,int) ; 
 char* bfd_elf_string_from_elf_section (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 scalar_t__ elf_bad_symtab (TYPE_8__*) ; 
 TYPE_21__* elf_section_data (TYPE_9__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (TYPE_8__*) ; 
 TYPE_18__* elf_tdata (TYPE_8__*) ; 
 scalar_t__ eval_symbol (int*,char*,char**,TYPE_8__*,struct elf_final_link_info*,int,int,size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_12__*) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_8__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_symbol_value (TYPE_8__*,struct elf_final_link_info*,int,int) ; 

__attribute__((used)) static bfd_boolean
evaluate_complex_relocation_symbols (bfd * input_bfd,
				     struct elf_final_link_info * finfo,
				     size_t locsymcount)
{
  const struct elf_backend_data * bed;
  Elf_Internal_Shdr *             symtab_hdr;
  struct elf_link_hash_entry **   sym_hashes;
  asection *                      reloc_sec;
  bfd_boolean                     result = TRUE;

  /* For each section, we're going to check and see if it has any
     complex relocations, and we're going to evaluate any of them
     we can.  */

  if (finfo->info->relocatable)
    return TRUE;

  symtab_hdr = & elf_tdata (input_bfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (input_bfd);
  bed = get_elf_backend_data (input_bfd);

  for (reloc_sec = input_bfd->sections; reloc_sec; reloc_sec = reloc_sec->next)
    {
      Elf_Internal_Rela * internal_relocs;
      unsigned long i;

      /* This section was omitted from the link.  */
      if (! reloc_sec->linker_mark)
	continue;

      /* Only process sections containing relocs.  */
      if ((reloc_sec->flags & SEC_RELOC) == 0)
	continue;

      if (reloc_sec->reloc_count == 0)
	continue;

      /* Read in the relocs for this section.  */
      internal_relocs
	= _bfd_elf_link_read_relocs (input_bfd, reloc_sec, NULL,
				     (Elf_Internal_Rela *) NULL,
				     FALSE);
      if (internal_relocs == NULL)
	continue;

      for (i = reloc_sec->reloc_count; i--;)
	{
	  Elf_Internal_Rela * rel;
	  char * sym_name;
	  bfd_vma index;
	  Elf_Internal_Sym * sym;
	  bfd_vma result;
	  bfd_vma section_offset;
	  bfd_vma addr;
	  int signed_p = 0;

	  rel = internal_relocs + i;
	  section_offset = reloc_sec->output_section->vma
	    + reloc_sec->output_offset;
	  addr = rel->r_offset;

	  index = ELF32_R_SYM (rel->r_info);
	  if (bed->s->arch_size == 64)
	    index >>= 24;

	  if (index == STN_UNDEF)
	    continue;

	  if (index < locsymcount)
	    {
	      /* The symbol is local.  */
	      sym = finfo->internal_syms + index;

	      /* We're only processing STT_RELC or STT_SRELC type symbols.  */
	      if ((ELF_ST_TYPE (sym->st_info) != STT_RELC) &&
		  (ELF_ST_TYPE (sym->st_info) != STT_SRELC))
		continue;

	      sym_name = bfd_elf_string_from_elf_section
		(input_bfd, symtab_hdr->sh_link, sym->st_name);

	      signed_p = (ELF_ST_TYPE (sym->st_info) == STT_SRELC);
	    }
	  else
	    {
	      /* The symbol is global.  */
	      struct elf_link_hash_entry * h;

	      if (elf_bad_symtab (input_bfd))
		continue;

	      h = sym_hashes [index - locsymcount];
	      while (   h->root.type == bfd_link_hash_indirect
		     || h->root.type == bfd_link_hash_warning)
		h = (struct elf_link_hash_entry *) h->root.u.i.link;

	      if (h->type != STT_RELC && h->type != STT_SRELC)
		continue;

	      signed_p = (h->type == STT_SRELC);
	      sym_name = (char *) h->root.root.string;
	    }
#ifdef DEBUG
	  printf ("Encountered a complex symbol!");
	  printf (" (input_bfd %s, section %s, reloc %ld\n",
		  input_bfd->filename, reloc_sec->name, i);
	  printf (" symbol: idx  %8.8lx, name %s\n",
		  index, sym_name);
	  printf (" reloc : info %8.8lx, addr %8.8lx\n",
		  rel->r_info, addr);
	  printf (" Evaluating '%s' ...\n ", sym_name);
#endif
	  if (eval_symbol (& result, sym_name, & sym_name, input_bfd, 
			   finfo, addr, section_offset, locsymcount,
			   signed_p))
	    /* Symbol evaluated OK.  Update to absolute value.  */
	    set_symbol_value (input_bfd, finfo, index, result);

	  else
	    result = FALSE;
	}

      if (internal_relocs != elf_section_data (reloc_sec)->relocs)
	free (internal_relocs);
    }

  /* If nothing went wrong, then we adjusted 
     everything we wanted to adjust.  */
  return result;
}