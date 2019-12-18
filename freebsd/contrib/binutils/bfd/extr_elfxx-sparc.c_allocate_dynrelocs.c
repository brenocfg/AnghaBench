#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int value; TYPE_12__* section; } ;
struct TYPE_22__ {scalar_t__ link; } ;
struct TYPE_25__ {TYPE_5__ def; TYPE_3__ i; } ;
struct TYPE_26__ {scalar_t__ type; TYPE_6__ u; } ;
struct TYPE_21__ {scalar_t__ refcount; int offset; } ;
struct TYPE_27__ {scalar_t__ refcount; int offset; } ;
struct elf_link_hash_entry {int dynindx; scalar_t__ forced_local; TYPE_7__ root; scalar_t__ def_regular; scalar_t__ def_dynamic; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  other; TYPE_2__ got; scalar_t__ needs_plt; TYPE_8__ plt; } ;
struct bfd_link_info {scalar_t__ symbolic; scalar_t__ shared; } ;
struct TYPE_23__ {int dynamic_sections_created; } ;
struct _bfd_sparc_elf_link_hash_table {int plt_header_size; TYPE_4__ elf; TYPE_1__* srelgot; TYPE_12__* sgot; TYPE_11__* srelplt2; TYPE_10__* sgotplt; scalar_t__ is_vxworks; TYPE_9__* srelplt; scalar_t__ plt_entry_size; TYPE_12__* splt; } ;
struct _bfd_sparc_elf_link_hash_entry {struct _bfd_sparc_elf_dyn_relocs* dyn_relocs; } ;
struct _bfd_sparc_elf_dyn_relocs {int count; int /*<<< orphan*/  sec; struct _bfd_sparc_elf_dyn_relocs* next; scalar_t__ pc_count; } ;
typedef  int bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_17__ {int size; } ;
typedef  TYPE_12__ asection ;
struct TYPE_28__ {int size; } ;
struct TYPE_20__ {int size; } ;
struct TYPE_19__ {int tls_type; } ;
struct TYPE_18__ {TYPE_12__* sreloc; } ;
struct TYPE_16__ {int size; } ;
struct TYPE_15__ {int size; } ;
typedef  scalar_t__ PTR ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GOT_TLS_GD ; 
 int GOT_TLS_IE ; 
 int PLT64_ENTRY_SIZE ; 
 int PLT64_LARGE_THRESHOLD ; 
 int SPARC_ELF_RELA_BYTES (struct _bfd_sparc_elf_link_hash_table*) ; 
 int SPARC_ELF_WORD_BYTES (struct _bfd_sparc_elf_link_hash_table*) ; 
 scalar_t__ STV_DEFAULT ; 
 int TRUE ; 
 scalar_t__ WILL_CALL_FINISH_DYNAMIC_SYMBOL (int,scalar_t__,struct elf_link_hash_entry*) ; 
 TYPE_14__* _bfd_sparc_elf_hash_entry (struct elf_link_hash_entry*) ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_13__* elf_section_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
allocate_dynrelocs (struct elf_link_hash_entry *h, PTR inf)
{
  struct bfd_link_info *info;
  struct _bfd_sparc_elf_link_hash_table *htab;
  struct _bfd_sparc_elf_link_hash_entry *eh;
  struct _bfd_sparc_elf_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    /* When warning symbols are created, they **replace** the "real"
       entry in the hash table, thus we never get to see the real
       symbol in a hash traversal.  So look at it now.  */
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  info = (struct bfd_link_info *) inf;
  htab = _bfd_sparc_elf_hash_table (info);

  if (htab->elf.dynamic_sections_created
      && h->plt.refcount > 0)
    {
      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      if (WILL_CALL_FINISH_DYNAMIC_SYMBOL (1, info->shared, h))
	{
	  asection *s = htab->splt;

	  /* Allocate room for the header.  */
	  if (s->size == 0)
	    {
	      s->size = htab->plt_header_size;

	      /* Allocate space for the .rela.plt.unloaded relocations.  */
	      if (htab->is_vxworks && !info->shared)
		htab->srelplt2->size = sizeof (Elf32_External_Rela) * 2;
	    }

	  /* The procedure linkage table size is bounded by the magnitude
	     of the offset we can describe in the entry.  */
	  if (s->size >= (SPARC_ELF_WORD_BYTES(htab) == 8 ?
			  (((bfd_vma)1 << 31) << 1) : 0x400000))
	    {
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }

	  if (SPARC_ELF_WORD_BYTES(htab) == 8
	      && s->size >= PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE)
	    {
	      bfd_vma off = s->size - PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE;


	      off = (off % (160 * PLT64_ENTRY_SIZE)) / PLT64_ENTRY_SIZE;

	      h->plt.offset = (s->size - (off * 8));
	    }
	  else
	    h->plt.offset = s->size;

	  /* If this symbol is not defined in a regular file, and we are
	     not generating a shared library, then set the symbol to this
	     location in the .plt.  This is required to make function
	     pointers compare as equal between the normal executable and
	     the shared library.  */
	  if (! info->shared
	      && !h->def_regular)
	    {
	      h->root.u.def.section = s;
	      h->root.u.def.value = h->plt.offset;
	    }

	  /* Make room for this entry.  */
	  s->size += htab->plt_entry_size;

	  /* We also need to make an entry in the .rela.plt section.  */
	  htab->srelplt->size += SPARC_ELF_RELA_BYTES (htab);

	  if (htab->is_vxworks)
	    {
	      /* Allocate space for the .got.plt entry.  */
	      htab->sgotplt->size += 4;

	      /* ...and for the .rela.plt.unloaded relocations.  */
	      if (!info->shared)
		htab->srelplt2->size += sizeof (Elf32_External_Rela) * 3;
	    }
	}
      else
	{
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	}
    }
  else
    {
      h->plt.offset = (bfd_vma) -1;
      h->needs_plt = 0;
    }

  /* If R_SPARC_TLS_IE_{HI22,LO10} symbol is now local to the binary,
     make it a R_SPARC_TLS_LE_{HI22,LO10} requiring no TLS entry.  */
  if (h->got.refcount > 0
      && !info->shared
      && h->dynindx == -1
      && _bfd_sparc_elf_hash_entry(h)->tls_type == GOT_TLS_IE)
    h->got.offset = (bfd_vma) -1;
  else if (h->got.refcount > 0)
    {
      asection *s;
      bfd_boolean dyn;
      int tls_type = _bfd_sparc_elf_hash_entry(h)->tls_type;

      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      s = htab->sgot;
      h->got.offset = s->size;
      s->size += SPARC_ELF_WORD_BYTES (htab);
      /* R_SPARC_TLS_GD_HI{22,LO10} needs 2 consecutive GOT slots.  */
      if (tls_type == GOT_TLS_GD)
	s->size += SPARC_ELF_WORD_BYTES (htab);
      dyn = htab->elf.dynamic_sections_created;
      /* R_SPARC_TLS_IE_{HI22,LO10} needs one dynamic relocation,
	 R_SPARC_TLS_GD_{HI22,LO10} needs one if local symbol and two if
	 global.  */
      if ((tls_type == GOT_TLS_GD && h->dynindx == -1)
	  || tls_type == GOT_TLS_IE)
	htab->srelgot->size += SPARC_ELF_RELA_BYTES (htab);
      else if (tls_type == GOT_TLS_GD)
	htab->srelgot->size += 2 * SPARC_ELF_RELA_BYTES (htab);
      else if (WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, info->shared, h))
	htab->srelgot->size += SPARC_ELF_RELA_BYTES (htab);
    }
  else
    h->got.offset = (bfd_vma) -1;

  eh = (struct _bfd_sparc_elf_link_hash_entry *) h;
  if (eh->dyn_relocs == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for pc-relative relocs that have become local due to symbol
     visibility changes.  */

  if (info->shared)
    {
      if (h->def_regular
	  && (h->forced_local
	      || info->symbolic))
	{
	  struct _bfd_sparc_elf_dyn_relocs **pp;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; )
	    {
	      p->count -= p->pc_count;
	      p->pc_count = 0;
	      if (p->count == 0)
		*pp = p->next;
	      else
		pp = &p->next;
	    }
	}

      /* Also discard relocs on undefined weak syms with non-default
	 visibility.  */
      if (eh->dyn_relocs != NULL
	  && h->root.type == bfd_link_hash_undefweak)
	{
	  if (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT)
	    eh->dyn_relocs = NULL;

	  /* Make sure undefined weak symbols are output as a dynamic
	     symbol in PIEs.  */
	  else if (h->dynindx == -1
		   && !h->forced_local)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }
	}
    }
  else
    {
      /* For the non-shared case, discard space for relocs against
	 symbols which turn out to need copy relocs or are not
	 dynamic.  */

      if (!h->non_got_ref
	  && ((h->def_dynamic
	       && !h->def_regular)
	      || (htab->elf.dynamic_sections_created
		  && (h->root.type == bfd_link_hash_undefweak
		      || h->root.type == bfd_link_hash_undefined))))
	{
	  /* Make sure this symbol is output as a dynamic symbol.
	     Undefined weak syms won't yet be marked as dynamic.  */
	  if (h->dynindx == -1
	      && !h->forced_local)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }

	  /* If that succeeded, we know we'll be keeping all the
	     relocs.  */
	  if (h->dynindx != -1)
	    goto keep;
	}

      eh->dyn_relocs = NULL;

    keep: ;
    }

  /* Finally, allocate space.  */
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      asection *sreloc = elf_section_data (p->sec)->sreloc;
      sreloc->size += p->count * SPARC_ELF_RELA_BYTES (htab);
    }

  return TRUE;
}