#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_11__ ;

/* Type definitions */
struct elf_reloc_cookie {int locsymcount; int extsymoff; int r_sym_shift; int /*<<< orphan*/ * locsyms; int /*<<< orphan*/ * rels; int /*<<< orphan*/ * relend; int /*<<< orphan*/ * rel; scalar_t__ bad_symtab; int /*<<< orphan*/  sym_hashes; TYPE_3__* abfd; } ;
struct elf_backend_data {scalar_t__ (* elf_backend_discard_info ) (TYPE_3__*,struct elf_reloc_cookie*,struct bfd_link_info*) ;TYPE_2__* s; } ;
struct bfd_link_info {int /*<<< orphan*/  relocatable; scalar_t__ eh_frame_hdr; int /*<<< orphan*/  keep_memory; TYPE_1__* callbacks; TYPE_3__* input_bfds; int /*<<< orphan*/  hash; scalar_t__ traditional_format; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_30__ {int flags; struct TYPE_30__* link_next; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_31__ {scalar_t__ size; scalar_t__ sec_info_type; unsigned int reloc_count; int /*<<< orphan*/  output_section; } ;
typedef  TYPE_4__ asection ;
struct TYPE_32__ {int sh_size; int sh_info; unsigned char* contents; } ;
struct TYPE_33__ {TYPE_5__ symtab_hdr; } ;
struct TYPE_29__ {int sizeof_sym; int arch_size; unsigned int int_rels_per_ext_rel; } ;
struct TYPE_28__ {int /*<<< orphan*/  (* einfo ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_27__ {int /*<<< orphan*/ * relocs; int /*<<< orphan*/  sec_info; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;
typedef  TYPE_5__ Elf_Internal_Shdr ;

/* Variables and functions */
 int DYNAMIC ; 
 scalar_t__ ELF_INFO_TYPE_STABS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ _bfd_discard_section_stabs (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct elf_reloc_cookie*) ; 
 scalar_t__ _bfd_elf_discard_section_eh_frame (TYPE_3__*,struct bfd_link_info*,TYPE_4__*,int /*<<< orphan*/ ,struct elf_reloc_cookie*) ; 
 scalar_t__ _bfd_elf_discard_section_eh_frame_hdr (TYPE_3__*,struct bfd_link_info*) ; 
 void* _bfd_elf_link_read_relocs (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_elf_get_elf_syms (TYPE_3__*,TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_elf_reloc_symbol_deleted_p ; 
 scalar_t__ bfd_get_flavour (TYPE_3__*) ; 
 TYPE_4__* bfd_get_section_by_name (TYPE_3__*,char*) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ elf_bad_symtab (TYPE_3__*) ; 
 TYPE_11__* elf_section_data (TYPE_4__*) ; 
 int /*<<< orphan*/  elf_sym_hashes (TYPE_3__*) ; 
 TYPE_8__* elf_tdata (TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (TYPE_3__*) ; 
 int /*<<< orphan*/  is_elf_hash_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_3__*,struct elf_reloc_cookie*,struct bfd_link_info*) ; 

bfd_boolean
bfd_elf_discard_info (bfd *output_bfd, struct bfd_link_info *info)
{
  struct elf_reloc_cookie cookie;
  asection *stab, *eh;
  Elf_Internal_Shdr *symtab_hdr;
  const struct elf_backend_data *bed;
  bfd *abfd;
  unsigned int count;
  bfd_boolean ret = FALSE;

  if (info->traditional_format
      || !is_elf_hash_table (info->hash))
    return FALSE;

  for (abfd = info->input_bfds; abfd != NULL; abfd = abfd->link_next)
    {
      if (bfd_get_flavour (abfd) != bfd_target_elf_flavour)
	continue;

      bed = get_elf_backend_data (abfd);

      if ((abfd->flags & DYNAMIC) != 0)
	continue;

      eh = NULL;
      if (!info->relocatable)
	{
	  eh = bfd_get_section_by_name (abfd, ".eh_frame");
	  if (eh != NULL
	      && (eh->size == 0
		  || bfd_is_abs_section (eh->output_section)))
	    eh = NULL;
	}

      stab = bfd_get_section_by_name (abfd, ".stab");
      if (stab != NULL
	  && (stab->size == 0
	      || bfd_is_abs_section (stab->output_section)
	      || stab->sec_info_type != ELF_INFO_TYPE_STABS))
	stab = NULL;

      if (stab == NULL
	  && eh == NULL
	  && bed->elf_backend_discard_info == NULL)
	continue;

      symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
      cookie.abfd = abfd;
      cookie.sym_hashes = elf_sym_hashes (abfd);
      cookie.bad_symtab = elf_bad_symtab (abfd);
      if (cookie.bad_symtab)
	{
	  cookie.locsymcount = symtab_hdr->sh_size / bed->s->sizeof_sym;
	  cookie.extsymoff = 0;
	}
      else
	{
	  cookie.locsymcount = symtab_hdr->sh_info;
	  cookie.extsymoff = symtab_hdr->sh_info;
	}

      if (bed->s->arch_size == 32)
	cookie.r_sym_shift = 8;
      else
	cookie.r_sym_shift = 32;

      cookie.locsyms = (Elf_Internal_Sym *) symtab_hdr->contents;
      if (cookie.locsyms == NULL && cookie.locsymcount != 0)
	{
	  cookie.locsyms = bfd_elf_get_elf_syms (abfd, symtab_hdr,
						 cookie.locsymcount, 0,
						 NULL, NULL, NULL);
	  if (cookie.locsyms == NULL)
	    {
	      info->callbacks->einfo (_("%P%X: can not read symbols: %E\n"));
	      return FALSE;
	    }
	}

      if (stab != NULL)
	{
	  cookie.rels = NULL;
	  count = stab->reloc_count;
	  if (count != 0)
	    cookie.rels = _bfd_elf_link_read_relocs (abfd, stab, NULL, NULL,
						     info->keep_memory);
	  if (cookie.rels != NULL)
	    {
	      cookie.rel = cookie.rels;
	      cookie.relend = cookie.rels;
	      cookie.relend += count * bed->s->int_rels_per_ext_rel;
	      if (_bfd_discard_section_stabs (abfd, stab,
					      elf_section_data (stab)->sec_info,
					      bfd_elf_reloc_symbol_deleted_p,
					      &cookie))
		ret = TRUE;
	      if (elf_section_data (stab)->relocs != cookie.rels)
		free (cookie.rels);
	    }
	}

      if (eh != NULL)
	{
	  cookie.rels = NULL;
	  count = eh->reloc_count;
	  if (count != 0)
	    cookie.rels = _bfd_elf_link_read_relocs (abfd, eh, NULL, NULL,
						     info->keep_memory);
	  cookie.rel = cookie.rels;
	  cookie.relend = cookie.rels;
	  if (cookie.rels != NULL)
	    cookie.relend += count * bed->s->int_rels_per_ext_rel;

	  if (_bfd_elf_discard_section_eh_frame (abfd, info, eh,
						 bfd_elf_reloc_symbol_deleted_p,
						 &cookie))
	    ret = TRUE;

	  if (cookie.rels != NULL
	      && elf_section_data (eh)->relocs != cookie.rels)
	    free (cookie.rels);
	}

      if (bed->elf_backend_discard_info != NULL
	  && (*bed->elf_backend_discard_info) (abfd, &cookie, info))
	ret = TRUE;

      if (cookie.locsyms != NULL
	  && symtab_hdr->contents != (unsigned char *) cookie.locsyms)
	{
	  if (! info->keep_memory)
	    free (cookie.locsyms);
	  else
	    symtab_hdr->contents = (unsigned char *) cookie.locsyms;
	}
    }

  if (info->eh_frame_hdr
      && !info->relocatable
      && _bfd_elf_discard_section_eh_frame_hdr (output_bfd, info))
    ret = TRUE;

  return ret;
}