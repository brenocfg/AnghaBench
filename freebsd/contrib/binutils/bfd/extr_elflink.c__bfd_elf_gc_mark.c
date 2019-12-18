#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_23__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_11__ ;

/* Type definitions */
struct TYPE_38__ {scalar_t__ link; } ;
struct TYPE_39__ {TYPE_2__ i; } ;
struct TYPE_40__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
struct elf_backend_data {TYPE_1__* s; } ;
struct bfd_link_info {int /*<<< orphan*/  keep_memory; } ;
typedef  TYPE_5__* (* elf_gc_mark_hook_fn ) (TYPE_5__*,struct bfd_link_info*,TYPE_7__*,struct elf_link_hash_entry*,TYPE_7__*) ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_41__ {int gc_mark; int flags; scalar_t__ reloc_count; int gc_mark_from_eh; int /*<<< orphan*/ * owner; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ asection ;
struct TYPE_42__ {int r_info; int /*<<< orphan*/  st_info; } ;
struct TYPE_37__ {TYPE_7__* relocs; TYPE_5__* next_in_group; } ;
struct TYPE_34__ {size_t sh_size; size_t sh_info; unsigned char* contents; } ;
struct TYPE_36__ {TYPE_11__ symtab_hdr; } ;
struct TYPE_35__ {size_t sizeof_sym; int int_rels_per_ext_rel; int arch_size; } ;
typedef  TYPE_7__ Elf_Internal_Sym ;
typedef  TYPE_11__ Elf_Internal_Shdr ;
typedef  TYPE_7__ Elf_Internal_Rela ;

/* Variables and functions */
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int SEC_RELOC ; 
 scalar_t__ STB_LOCAL ; 
 int TRUE ; 
 TYPE_7__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__* bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_11__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ elf_bad_symtab (int /*<<< orphan*/ *) ; 
 TYPE_23__* elf_section_data (TYPE_5__*) ; 
 struct elf_link_hash_entry** elf_sym_hashes (int /*<<< orphan*/ *) ; 
 TYPE_22__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* stub1 (TYPE_5__*,struct bfd_link_info*,TYPE_7__*,struct elf_link_hash_entry*,TYPE_7__*) ; 
 TYPE_5__* stub2 (TYPE_5__*,struct bfd_link_info*,TYPE_7__*,struct elf_link_hash_entry*,TYPE_7__*) ; 

bfd_boolean
_bfd_elf_gc_mark (struct bfd_link_info *info,
		  asection *sec,
		  elf_gc_mark_hook_fn gc_mark_hook)
{
  bfd_boolean ret;
  bfd_boolean is_eh;
  asection *group_sec;

  sec->gc_mark = 1;

  /* Mark all the sections in the group.  */
  group_sec = elf_section_data (sec)->next_in_group;
  if (group_sec && !group_sec->gc_mark)
    if (!_bfd_elf_gc_mark (info, group_sec, gc_mark_hook))
      return FALSE;

  /* Look through the section relocs.  */
  ret = TRUE;
  is_eh = strcmp (sec->name, ".eh_frame") == 0;
  if ((sec->flags & SEC_RELOC) != 0 && sec->reloc_count > 0)
    {
      Elf_Internal_Rela *relstart, *rel, *relend;
      Elf_Internal_Shdr *symtab_hdr;
      struct elf_link_hash_entry **sym_hashes;
      size_t nlocsyms;
      size_t extsymoff;
      bfd *input_bfd = sec->owner;
      const struct elf_backend_data *bed = get_elf_backend_data (input_bfd);
      Elf_Internal_Sym *isym = NULL;
      int r_sym_shift;

      symtab_hdr = &elf_tdata (input_bfd)->symtab_hdr;
      sym_hashes = elf_sym_hashes (input_bfd);

      /* Read the local symbols.  */
      if (elf_bad_symtab (input_bfd))
	{
	  nlocsyms = symtab_hdr->sh_size / bed->s->sizeof_sym;
	  extsymoff = 0;
	}
      else
	extsymoff = nlocsyms = symtab_hdr->sh_info;

      isym = (Elf_Internal_Sym *) symtab_hdr->contents;
      if (isym == NULL && nlocsyms != 0)
	{
	  isym = bfd_elf_get_elf_syms (input_bfd, symtab_hdr, nlocsyms, 0,
				       NULL, NULL, NULL);
	  if (isym == NULL)
	    return FALSE;
	}

      /* Read the relocations.  */
      relstart = _bfd_elf_link_read_relocs (input_bfd, sec, NULL, NULL,
					    info->keep_memory);
      if (relstart == NULL)
	{
	  ret = FALSE;
	  goto out1;
	}
      relend = relstart + sec->reloc_count * bed->s->int_rels_per_ext_rel;

      if (bed->s->arch_size == 32)
	r_sym_shift = 8;
      else
	r_sym_shift = 32;

      for (rel = relstart; rel < relend; rel++)
	{
	  unsigned long r_symndx;
	  asection *rsec;
	  struct elf_link_hash_entry *h;

	  r_symndx = rel->r_info >> r_sym_shift;
	  if (r_symndx == 0)
	    continue;

	  if (r_symndx >= nlocsyms
	      || ELF_ST_BIND (isym[r_symndx].st_info) != STB_LOCAL)
	    {
	      h = sym_hashes[r_symndx - extsymoff];
	      while (h->root.type == bfd_link_hash_indirect
		     || h->root.type == bfd_link_hash_warning)
		h = (struct elf_link_hash_entry *) h->root.u.i.link;
	      rsec = (*gc_mark_hook) (sec, info, rel, h, NULL);
	    }
	  else
	    {
	      rsec = (*gc_mark_hook) (sec, info, rel, NULL, &isym[r_symndx]);
	    }

	  if (rsec && !rsec->gc_mark)
	    {
	      if (bfd_get_flavour (rsec->owner) != bfd_target_elf_flavour)
		rsec->gc_mark = 1;
	      else if (is_eh)
		rsec->gc_mark_from_eh = 1;
	      else if (!_bfd_elf_gc_mark (info, rsec, gc_mark_hook))
		{
		  ret = FALSE;
		  goto out2;
		}
	    }
	}

    out2:
      if (elf_section_data (sec)->relocs != relstart)
	free (relstart);
    out1:
      if (isym != NULL && symtab_hdr->contents != (unsigned char *) isym)
	{
	  if (! info->keep_memory)
	    free (isym);
	  else
	    symtab_hdr->contents = (unsigned char *) isym;
	}
    }

  return ret;
}