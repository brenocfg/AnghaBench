#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int dynamic_sections_created; } ;
struct TYPE_26__ {int refcount; } ;
struct ppc_elf_link_hash_table {scalar_t__ plt_type; scalar_t__ plt_initial_entry_size; int plt_slot_size; int plt_entry_size; TYPE_6__* relgot; TYPE_11__ elf; TYPE_5__ tlsld_got; TYPE_4__* sgotplt; TYPE_3__* srelplt2; TYPE_2__* relplt; scalar_t__ emit_stub_syms; TYPE_14__* glink; TYPE_14__* plt; } ;
struct TYPE_22__ {scalar_t__ value; TYPE_14__* section; } ;
struct TYPE_29__ {scalar_t__ link; } ;
struct TYPE_30__ {TYPE_1__ def; TYPE_8__ i; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_9__ u; } ;
struct TYPE_28__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct TYPE_18__ {struct plt_entry* plist; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  forced_local; int /*<<< orphan*/  def_regular; scalar_t__ def_dynamic; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  other; TYPE_10__ root; TYPE_7__ got; scalar_t__ needs_plt; TYPE_12__ plt; } ;
struct ppc_elf_link_hash_entry {int tls_mask; struct ppc_elf_dyn_relocs* dyn_relocs; struct elf_link_hash_entry elf; } ;
struct ppc_elf_dyn_relocs {int count; int /*<<< orphan*/  sec; struct ppc_elf_dyn_relocs* next; scalar_t__ pc_count; } ;
struct TYPE_19__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct plt_entry {TYPE_13__ plt; scalar_t__ glink_offset; struct plt_entry* next; } ;
struct bfd_link_info {scalar_t__ shared; scalar_t__ pie; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_20__ {scalar_t__ size; } ;
typedef  TYPE_14__ asection ;
struct TYPE_27__ {unsigned int size; } ;
struct TYPE_25__ {int size; } ;
struct TYPE_24__ {int size; } ;
struct TYPE_23__ {int size; } ;
struct TYPE_21__ {TYPE_14__* sreloc; } ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ ELIMINATE_COPY_RELOCS ; 
 int FALSE ; 
 scalar_t__ GLINK_ENTRY_SIZE ; 
 scalar_t__ PLT_NEW ; 
 int PLT_NUM_SINGLE_ENTRIES ; 
 scalar_t__ PLT_OLD ; 
 scalar_t__ PLT_VXWORKS ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int TLS_DTPREL ; 
 int TLS_GD ; 
 int TLS_LD ; 
 int TLS_TLS ; 
 int TLS_TPREL ; 
 int TLS_TPRELGD ; 
 int TRUE ; 
 int VXWORKS_PLTRESOLVE_RELOCS ; 
 int VXWORKS_PLT_NON_JMP_SLOT_RELOCS ; 
 scalar_t__ WILL_CALL_FINISH_DYNAMIC_SYMBOL (int,int /*<<< orphan*/ ,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  add_stub_sym (struct plt_entry*,struct elf_link_hash_entry*,struct bfd_link_info*) ; 
 scalar_t__ allocate_got (struct ppc_elf_link_hash_table*,unsigned int) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_15__* elf_section_data (int /*<<< orphan*/ ) ; 
 struct ppc_elf_link_hash_table* ppc_elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
allocate_dynrelocs (struct elf_link_hash_entry *h, void *inf)
{
  struct bfd_link_info *info = inf;
  struct ppc_elf_link_hash_entry *eh;
  struct ppc_elf_link_hash_table *htab;
  struct ppc_elf_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    /* When warning symbols are created, they **replace** the "real"
       entry in the hash table, thus we never get to see the real
       symbol in a hash traversal.  So look at it now.  */
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  htab = ppc_elf_hash_table (info);
  if (htab->elf.dynamic_sections_created)
    {
      struct plt_entry *ent;
      bfd_boolean doneone = FALSE;
      bfd_vma plt_offset = 0, glink_offset = 0;

      for (ent = h->plt.plist; ent != NULL; ent = ent->next)
	if (ent->plt.refcount > 0)
	  {
	    /* Make sure this symbol is output as a dynamic symbol.  */
	    if (h->dynindx == -1
		&& !h->forced_local)
	      {
		if (! bfd_elf_link_record_dynamic_symbol (info, h))
		  return FALSE;
	      }

	    if (info->shared
		|| WILL_CALL_FINISH_DYNAMIC_SYMBOL (1, 0, h))
	      {
		asection *s = htab->plt;

		if (htab->plt_type == PLT_NEW)
		  {
		    if (!doneone)
		      {
			plt_offset = s->size;
			s->size += 4;
		      }
		    ent->plt.offset = plt_offset;

		    s = htab->glink;
		    if (!doneone || info->shared || info->pie)
		      {
			glink_offset = s->size;
			s->size += GLINK_ENTRY_SIZE;
		      }
		    if (!doneone
			&& !info->shared
			&& !h->def_regular)
		      {
			h->root.u.def.section = s;
			h->root.u.def.value = glink_offset;
		      }
		    ent->glink_offset = glink_offset;

		    if (htab->emit_stub_syms
			&& !add_stub_sym (ent, h, info))
		      return FALSE;
		  }
		else
		  {
		    if (!doneone)
		      {
			/* If this is the first .plt entry, make room
			   for the special first entry.  */
			if (s->size == 0)
			  s->size += htab->plt_initial_entry_size;

			/* The PowerPC PLT is actually composed of two
			   parts, the first part is 2 words (for a load
			   and a jump), and then there is a remaining
			   word available at the end.  */
			plt_offset = (htab->plt_initial_entry_size
				      + (htab->plt_slot_size
					 * ((s->size
					     - htab->plt_initial_entry_size)
					    / htab->plt_entry_size)));

			/* If this symbol is not defined in a regular
			   file, and we are not generating a shared
			   library, then set the symbol to this location
			   in the .plt.  This is required to make
			   function pointers compare as equal between
			   the normal executable and the shared library.  */
			if (! info->shared
			    && !h->def_regular)
			  {
			    h->root.u.def.section = s;
			    h->root.u.def.value = plt_offset;
			  }

			/* Make room for this entry.  */
			s->size += htab->plt_entry_size;
			/* After the 8192nd entry, room for two entries
			   is allocated.  */
			if (htab->plt_type == PLT_OLD
			    && (s->size - htab->plt_initial_entry_size)
				/ htab->plt_entry_size
			       > PLT_NUM_SINGLE_ENTRIES)
			  s->size += htab->plt_entry_size;
		      }
		    ent->plt.offset = plt_offset;
		  }

		/* We also need to make an entry in the .rela.plt section.  */
		if (!doneone)
		  {
		    htab->relplt->size += sizeof (Elf32_External_Rela);

		    if (htab->plt_type == PLT_VXWORKS)
		      {
			/* Allocate space for the unloaded relocations.  */
			if (!info->shared)
			  {
			    if (ent->plt.offset
				== (bfd_vma) htab->plt_initial_entry_size)
			      {
				htab->srelplt2->size
				  += sizeof (Elf32_External_Rela)
				      * VXWORKS_PLTRESOLVE_RELOCS;
			      }

			    htab->srelplt2->size
			      += sizeof (Elf32_External_Rela)
				  * VXWORKS_PLT_NON_JMP_SLOT_RELOCS;
			  }

			/* Every PLT entry has an associated GOT entry in
			   .got.plt.  */
			htab->sgotplt->size += 4;
		      }
		    doneone = TRUE;
		  }
	      }
	    else
	      ent->plt.offset = (bfd_vma) -1;
	  }
	else
	  ent->plt.offset = (bfd_vma) -1;

      if (!doneone)
	{
	  h->plt.plist = NULL;
	  h->needs_plt = 0;
	}
    }
  else
    {
      h->plt.plist = NULL;
      h->needs_plt = 0;
    }

  eh = (struct ppc_elf_link_hash_entry *) h;
  if (eh->elf.got.refcount > 0)
    {
      /* Make sure this symbol is output as a dynamic symbol.  */
      if (eh->elf.dynindx == -1
	  && !eh->elf.forced_local)
	{
	  if (!bfd_elf_link_record_dynamic_symbol (info, &eh->elf))
	    return FALSE;
	}

      if (eh->tls_mask == (TLS_TLS | TLS_LD)
	  && !eh->elf.def_dynamic)
	{
	  /* If just an LD reloc, we'll just use htab->tlsld_got.offset.  */
	  htab->tlsld_got.refcount += 1;
	  eh->elf.got.offset = (bfd_vma) -1;
	}
      else
	{
	  bfd_boolean dyn;
	  unsigned int need = 0;
	  if ((eh->tls_mask & TLS_TLS) != 0)
	    {
	      if ((eh->tls_mask & TLS_LD) != 0)
		need += 8;
	      if ((eh->tls_mask & TLS_GD) != 0)
		need += 8;
	      if ((eh->tls_mask & (TLS_TPREL | TLS_TPRELGD)) != 0)
		need += 4;
	      if ((eh->tls_mask & TLS_DTPREL) != 0)
		need += 4;
	    }
	  else
	    need += 4;
	  eh->elf.got.offset = allocate_got (htab, need);
	  dyn = htab->elf.dynamic_sections_created;
	  if ((info->shared
	       || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, &eh->elf))
	      && (ELF_ST_VISIBILITY (eh->elf.other) == STV_DEFAULT
		  || eh->elf.root.type != bfd_link_hash_undefweak))
	    {
	      /* All the entries we allocated need relocs.
		 Except LD only needs one.  */
	      if ((eh->tls_mask & TLS_LD) != 0)
		need -= 4;
	      htab->relgot->size += need * (sizeof (Elf32_External_Rela) / 4);
	    }
	}
    }
  else
    eh->elf.got.offset = (bfd_vma) -1;

  if (eh->dyn_relocs == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for relocs that have become local due to symbol visibility
     changes.  */

  if (info->shared)
    {
      /* Relocs that use pc_count are those that appear on a call insn,
	 or certain REL relocs (see must_be_dyn_reloc) that can be
	 generated via assembly.  We want calls to protected symbols to
	 resolve directly to the function rather than going via the plt.
	 If people want function pointer comparisons to work as expected
	 then they should avoid writing weird assembly.  */
      if (SYMBOL_CALLS_LOCAL (info, h))
	{
	  struct ppc_elf_dyn_relocs **pp;

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
	  && h->def_dynamic
	  && !h->def_regular)
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
      sreloc->size += p->count * sizeof (Elf32_External_Rela);
    }

  return TRUE;
}