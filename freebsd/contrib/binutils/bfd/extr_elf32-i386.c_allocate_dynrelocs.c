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
struct TYPE_24__ {scalar_t__ value; TYPE_12__* section; } ;
struct TYPE_22__ {scalar_t__ link; } ;
struct TYPE_25__ {TYPE_5__ def; TYPE_3__ i; } ;
struct TYPE_26__ {scalar_t__ type; TYPE_6__ u; } ;
struct TYPE_21__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct TYPE_16__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  forced_local; TYPE_7__ root; int /*<<< orphan*/  def_regular; scalar_t__ def_dynamic; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  other; TYPE_2__ got; scalar_t__ needs_plt; TYPE_11__ plt; } ;
struct TYPE_23__ {int dynamic_sections_created; } ;
struct elf_i386_link_hash_table {TYPE_4__ elf; TYPE_9__* srelplt; TYPE_1__* srelgot; TYPE_8__* sgotplt; TYPE_12__* sgot; TYPE_10__* srelplt2; scalar_t__ is_vxworks; int /*<<< orphan*/  next_tls_desc_index; TYPE_12__* splt; } ;
struct elf_i386_link_hash_entry {struct elf_i386_dyn_relocs* dyn_relocs; void* tlsdesc_got; } ;
struct elf_i386_dyn_relocs {int count; int /*<<< orphan*/  sec; struct elf_i386_dyn_relocs* next; scalar_t__ pc_count; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  void* bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_17__ {scalar_t__ size; } ;
typedef  TYPE_12__ asection ;
struct TYPE_28__ {int size; } ;
struct TYPE_27__ {void* size; } ;
struct TYPE_20__ {int size; } ;
struct TYPE_19__ {int tls_type; } ;
struct TYPE_18__ {TYPE_12__* sreloc; } ;
struct TYPE_15__ {int size; } ;
typedef  int /*<<< orphan*/  Elf32_External_Rel ;

/* Variables and functions */
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ ELIMINATE_COPY_RELOCS ; 
 int FALSE ; 
 scalar_t__ GOT_TLS_GDESC_P (int) ; 
 scalar_t__ GOT_TLS_GD_P (int) ; 
 int GOT_TLS_IE ; 
 int GOT_TLS_IE_BOTH ; 
 scalar_t__ PLT_ENTRY_SIZE ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int TRUE ; 
 scalar_t__ WILL_CALL_FINISH_DYNAMIC_SYMBOL (int,int /*<<< orphan*/ ,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 void* elf_i386_compute_jump_table_size (struct elf_i386_link_hash_table*) ; 
 TYPE_14__* elf_i386_hash_entry (struct elf_link_hash_entry*) ; 
 struct elf_i386_link_hash_table* elf_i386_hash_table (struct bfd_link_info*) ; 
 TYPE_13__* elf_section_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
allocate_dynrelocs (struct elf_link_hash_entry *h, void *inf)
{
  struct bfd_link_info *info;
  struct elf_i386_link_hash_table *htab;
  struct elf_i386_link_hash_entry *eh;
  struct elf_i386_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    /* When warning symbols are created, they **replace** the "real"
       entry in the hash table, thus we never get to see the real
       symbol in a hash traversal.  So look at it now.  */
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  info = (struct bfd_link_info *) inf;
  htab = elf_i386_hash_table (info);

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

      if (info->shared
	  || WILL_CALL_FINISH_DYNAMIC_SYMBOL (1, 0, h))
	{
	  asection *s = htab->splt;

	  /* If this is the first .plt entry, make room for the special
	     first entry.  */
	  if (s->size == 0)
	    s->size += PLT_ENTRY_SIZE;

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
	  s->size += PLT_ENTRY_SIZE;

	  /* We also need to make an entry in the .got.plt section, which
	     will be placed in the .got section by the linker script.  */
	  htab->sgotplt->size += 4;

	  /* We also need to make an entry in the .rel.plt section.  */
	  htab->srelplt->size += sizeof (Elf32_External_Rel);
	  htab->next_tls_desc_index++;

	  if (htab->is_vxworks && !info->shared)
	    {
	      /* VxWorks has a second set of relocations for each PLT entry
		 in executables.  They go in a separate relocation section,
		 which is processed by the kernel loader.  */

	      /* There are two relocations for the initial PLT entry: an
		 R_386_32 relocation for _GLOBAL_OFFSET_TABLE_ + 4 and an
		 R_386_32 relocation for _GLOBAL_OFFSET_TABLE_ + 8.  */

	      if (h->plt.offset == PLT_ENTRY_SIZE)
		htab->srelplt2->size += (sizeof (Elf32_External_Rel) * 2);

	      /* There are two extra relocations for each subsequent PLT entry:
		 an R_386_32 relocation for the GOT entry, and an R_386_32
		 relocation for the PLT entry.  */

	      htab->srelplt2->size += (sizeof (Elf32_External_Rel) * 2);
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

  eh = (struct elf_i386_link_hash_entry *) h;
  eh->tlsdesc_got = (bfd_vma) -1;

  /* If R_386_TLS_{IE_32,IE,GOTIE} symbol is now local to the binary,
     make it a R_386_TLS_LE_32 requiring no TLS entry.  */
  if (h->got.refcount > 0
      && !info->shared
      && h->dynindx == -1
      && (elf_i386_hash_entry(h)->tls_type & GOT_TLS_IE))
    h->got.offset = (bfd_vma) -1;
  else if (h->got.refcount > 0)
    {
      asection *s;
      bfd_boolean dyn;
      int tls_type = elf_i386_hash_entry(h)->tls_type;

      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      s = htab->sgot;
      if (GOT_TLS_GDESC_P (tls_type))
	{
	  eh->tlsdesc_got = htab->sgotplt->size
	    - elf_i386_compute_jump_table_size (htab);
	  htab->sgotplt->size += 8;
	  h->got.offset = (bfd_vma) -2;
	}
      if (! GOT_TLS_GDESC_P (tls_type)
	  || GOT_TLS_GD_P (tls_type))
	{
	  h->got.offset = s->size;
	  s->size += 4;
	  /* R_386_TLS_GD needs 2 consecutive GOT slots.  */
	  if (GOT_TLS_GD_P (tls_type) || tls_type == GOT_TLS_IE_BOTH)
	    s->size += 4;
	}
      dyn = htab->elf.dynamic_sections_created;
      /* R_386_TLS_IE_32 needs one dynamic relocation,
	 R_386_TLS_IE resp. R_386_TLS_GOTIE needs one dynamic relocation,
	 (but if both R_386_TLS_IE_32 and R_386_TLS_IE is present, we
	 need two), R_386_TLS_GD needs one if local symbol and two if
	 global.  */
      if (tls_type == GOT_TLS_IE_BOTH)
	htab->srelgot->size += 2 * sizeof (Elf32_External_Rel);
      else if ((GOT_TLS_GD_P (tls_type) && h->dynindx == -1)
	       || (tls_type & GOT_TLS_IE))
	htab->srelgot->size += sizeof (Elf32_External_Rel);
      else if (GOT_TLS_GD_P (tls_type))
	htab->srelgot->size += 2 * sizeof (Elf32_External_Rel);
      else if (! GOT_TLS_GDESC_P (tls_type)
	       && (ELF_ST_VISIBILITY (h->other) == STV_DEFAULT
		   || h->root.type != bfd_link_hash_undefweak)
	       && (info->shared
		   || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, h)))
	htab->srelgot->size += sizeof (Elf32_External_Rel);
      if (GOT_TLS_GDESC_P (tls_type))
	htab->srelplt->size += sizeof (Elf32_External_Rel);
    }
  else
    h->got.offset = (bfd_vma) -1;

  if (eh->dyn_relocs == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for pc-relative relocs that have become local due to symbol
     visibility changes.  */

  if (info->shared)
    {
      /* The only reloc that uses pc_count is R_386_PC32, which will
	 appear on a call or on something like ".long foo - .".  We
	 want calls to protected symbols to resolve directly to the
	 function rather than going via the plt.  If people want
	 function pointer comparisons to work as expected then they
	 should avoid writing assembly like ".long foo - .".  */
      if (SYMBOL_CALLS_LOCAL (info, h))
	{
	  struct elf_i386_dyn_relocs **pp;

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
  else if (ELIMINATE_COPY_RELOCS)
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
      sreloc->size += p->count * sizeof (Elf32_External_Rel);
    }

  return TRUE;
}