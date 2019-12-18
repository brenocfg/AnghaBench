#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ value; TYPE_13__* section; } ;
struct TYPE_23__ {scalar_t__ link; } ;
struct TYPE_17__ {TYPE_9__ def; TYPE_1__ i; } ;
struct TYPE_30__ {char* string; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_10__ u; TYPE_8__ root; } ;
struct TYPE_29__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct TYPE_27__ {scalar_t__ refcount; scalar_t__ offset; } ;
struct elf_link_hash_entry {int dynindx; int forced_local; TYPE_12__ root; scalar_t__ def_regular; scalar_t__ def_dynamic; int /*<<< orphan*/  non_got_ref; int /*<<< orphan*/  other; void* type; TYPE_7__ got; scalar_t__ needs_plt; TYPE_5__ plt; } ;
struct elf32_arm_relocs_copied {int count; int /*<<< orphan*/  section; struct elf32_arm_relocs_copied* next; scalar_t__ pc_count; } ;
struct TYPE_18__ {int dynamic_sections_created; scalar_t__ is_relocatable_executable; } ;
struct elf32_arm_link_hash_table {scalar_t__ plt_header_size; scalar_t__ plt_entry_size; TYPE_11__ root; int /*<<< orphan*/  use_blx; TYPE_6__* srelgot; TYPE_13__* sgot; int /*<<< orphan*/  symbian_p; TYPE_4__* srelplt2; scalar_t__ vxworks_p; TYPE_3__* srelplt; TYPE_2__* sgotplt; TYPE_13__* splt; } ;
struct elf32_arm_link_hash_entry {scalar_t__ plt_thumb_refcount; int plt_got_offset; struct elf32_arm_relocs_copied* relocs_copied; struct elf_link_hash_entry* export_glue; } ;
struct bfd_link_info {scalar_t__ shared; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  void* bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_20__ {scalar_t__ size; int /*<<< orphan*/  owner; } ;
typedef  TYPE_13__ asection ;
struct TYPE_28__ {int size; } ;
struct TYPE_26__ {int size; } ;
struct TYPE_25__ {int size; } ;
struct TYPE_24__ {int size; } ;
struct TYPE_22__ {int tls_type; } ;
struct TYPE_21__ {TYPE_13__* sreloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  ELF_ST_BIND (void*) ; 
 void* ELF_ST_INFO (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ELF_ST_TYPE (void*) ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GOT_NORMAL ; 
 int GOT_TLS_GD ; 
 int GOT_TLS_IE ; 
 int GOT_UNKNOWN ; 
 scalar_t__ PLT_THUMB_STUB_SIZE ; 
 int RELOC_SIZE (struct elf32_arm_link_hash_table*) ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 scalar_t__ STT_ARM_TFUNC ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  SYMBOL_REFERENCES_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int TRUE ; 
 scalar_t__ WILL_CALL_FINISH_DYNAMIC_SYMBOL (int,scalar_t__,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_13__*,scalar_t__,int /*<<< orphan*/ *,int,int,struct bfd_link_hash_entry**) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_15__* elf32_arm_hash_entry (struct elf_link_hash_entry*) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 TYPE_14__* elf_section_data (int /*<<< orphan*/ ) ; 
 struct elf_link_hash_entry* record_arm_to_thumb_glue (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static bfd_boolean
allocate_dynrelocs (struct elf_link_hash_entry *h, void * inf)
{
  struct bfd_link_info *info;
  struct elf32_arm_link_hash_table *htab;
  struct elf32_arm_link_hash_entry *eh;
  struct elf32_arm_relocs_copied *p;

  eh = (struct elf32_arm_link_hash_entry *) h;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    /* When warning symbols are created, they **replace** the "real"
       entry in the hash table, thus we never get to see the real
       symbol in a hash traversal.  So look at it now.  */
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  info = (struct bfd_link_info *) inf;
  htab = elf32_arm_hash_table (info);

  if (htab->root.dynamic_sections_created
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
	    s->size += htab->plt_header_size;

	  h->plt.offset = s->size;

	  /* If we will insert a Thumb trampoline before this PLT, leave room
	     for it.  */
	  if (!htab->use_blx && eh->plt_thumb_refcount > 0)
	    {
	      h->plt.offset += PLT_THUMB_STUB_SIZE;
	      s->size += PLT_THUMB_STUB_SIZE;
	    }

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

	      /* Make sure the function is not marked as Thumb, in case
		 it is the target of an ABS32 relocation, which will
		 point to the PLT entry.  */
	      if (ELF_ST_TYPE (h->type) == STT_ARM_TFUNC)
		h->type = ELF_ST_INFO (ELF_ST_BIND (h->type), STT_FUNC);
	    }

	  /* Make room for this entry.  */
	  s->size += htab->plt_entry_size;

	  if (!htab->symbian_p)
	    {
	      /* We also need to make an entry in the .got.plt section, which
		 will be placed in the .got section by the linker script.  */
	      eh->plt_got_offset = htab->sgotplt->size;
	      htab->sgotplt->size += 4;
	    }

	  /* We also need to make an entry in the .rel(a).plt section.  */
	  htab->srelplt->size += RELOC_SIZE (htab);

	  /* VxWorks executables have a second set of relocations for
	     each PLT entry.  They go in a separate relocation section,
	     which is processed by the kernel loader.  */
	  if (htab->vxworks_p && !info->shared)
	    {
	      /* There is a relocation for the initial PLT entry:
		 an R_ARM_32 relocation for _GLOBAL_OFFSET_TABLE_.  */
	      if (h->plt.offset == htab->plt_header_size)
		htab->srelplt2->size += RELOC_SIZE (htab);

	      /* There are two extra relocations for each subsequent
		 PLT entry: an R_ARM_32 relocation for the GOT entry,
		 and an R_ARM_32 relocation for the PLT entry.  */
	      htab->srelplt2->size += RELOC_SIZE (htab) * 2;
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

  if (h->got.refcount > 0)
    {
      asection *s;
      bfd_boolean dyn;
      int tls_type = elf32_arm_hash_entry (h)->tls_type;
      int indx;

      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      if (!htab->symbian_p)
	{
	  s = htab->sgot;
	  h->got.offset = s->size;

	  if (tls_type == GOT_UNKNOWN)
	    abort ();

	  if (tls_type == GOT_NORMAL)
	    /* Non-TLS symbols need one GOT slot.  */
	    s->size += 4;
	  else
	    {
	      if (tls_type & GOT_TLS_GD)
		/* R_ARM_TLS_GD32 needs 2 consecutive GOT slots.  */
		s->size += 8;
	      if (tls_type & GOT_TLS_IE)
		/* R_ARM_TLS_IE32 needs one GOT slot.  */
		s->size += 4;
	    }

	  dyn = htab->root.dynamic_sections_created;

	  indx = 0;
	  if (WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, info->shared, h)
	      && (!info->shared
		  || !SYMBOL_REFERENCES_LOCAL (info, h)))
	    indx = h->dynindx;

	  if (tls_type != GOT_NORMAL
	      && (info->shared || indx != 0)
	      && (ELF_ST_VISIBILITY (h->other) == STV_DEFAULT
		  || h->root.type != bfd_link_hash_undefweak))
	    {
	      if (tls_type & GOT_TLS_IE)
		htab->srelgot->size += RELOC_SIZE (htab);

	      if (tls_type & GOT_TLS_GD)
		htab->srelgot->size += RELOC_SIZE (htab);

	      if ((tls_type & GOT_TLS_GD) && indx != 0)
		htab->srelgot->size += RELOC_SIZE (htab);
	    }
	  else if ((ELF_ST_VISIBILITY (h->other) == STV_DEFAULT
		    || h->root.type != bfd_link_hash_undefweak)
		   && (info->shared
	    	   || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, h)))
	    htab->srelgot->size += RELOC_SIZE (htab);
	}
    }
  else
    h->got.offset = (bfd_vma) -1;

  /* Allocate stubs for exported Thumb functions on v4t.  */
  if (!htab->use_blx && h->dynindx != -1
      && h->def_regular
      && ELF_ST_TYPE (h->type) == STT_ARM_TFUNC
      && ELF_ST_VISIBILITY (h->other) == STV_DEFAULT)
    {
      struct elf_link_hash_entry * th;
      struct bfd_link_hash_entry * bh;
      struct elf_link_hash_entry * myh;
      char name[1024];
      asection *s;
      bh = NULL;
      /* Create a new symbol to regist the real location of the function.  */
      s = h->root.u.def.section;
      sprintf(name, "__real_%s", h->root.root.string);
      _bfd_generic_link_add_one_symbol (info, s->owner,
					name, BSF_GLOBAL, s,
					h->root.u.def.value,
					NULL, TRUE, FALSE, &bh);

      myh = (struct elf_link_hash_entry *) bh;
      myh->type = ELF_ST_INFO (STB_LOCAL, STT_ARM_TFUNC);
      myh->forced_local = 1;
      eh->export_glue = myh;
      th = record_arm_to_thumb_glue (info, h);
      /* Point the symbol at the stub.  */
      h->type = ELF_ST_INFO (ELF_ST_BIND (h->type), STT_FUNC);
      h->root.u.def.section = th->root.u.def.section;
      h->root.u.def.value = th->root.u.def.value & ~1;
    }

  if (eh->relocs_copied == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for pc-relative relocs that have become local due to symbol
     visibility changes.  */

  if (info->shared || htab->root.is_relocatable_executable)
    {
      /* The only relocs that use pc_count are R_ARM_REL32 and
         R_ARM_REL32_NOI, which will appear on something like
         ".long foo - .".  We want calls to protected symbols to resolve
         directly to the function rather than going via the plt.  If people
         want function pointer comparisons to work as expected then they
         should avoid writing assembly like ".long foo - .".  */
      if (SYMBOL_CALLS_LOCAL (info, h))
	{
	  struct elf32_arm_relocs_copied **pp;

	  for (pp = &eh->relocs_copied; (p = *pp) != NULL; )
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
      if (eh->relocs_copied != NULL
	  && h->root.type == bfd_link_hash_undefweak)
	{
	  if (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT)
	    eh->relocs_copied = NULL;

	  /* Make sure undefined weak symbols are output as a dynamic
	     symbol in PIEs.  */
	  else if (h->dynindx == -1
		   && !h->forced_local)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }
	}

      else if (htab->root.is_relocatable_executable && h->dynindx == -1
	       && h->root.type == bfd_link_hash_new)
	{
	  /* Output absolute symbols so that we can create relocations
	     against them.  For normal symbols we output a relocation
	     against the section that contains them.  */
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
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
	      || (htab->root.dynamic_sections_created
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

      eh->relocs_copied = NULL;

    keep: ;
    }

  /* Finally, allocate space.  */
  for (p = eh->relocs_copied; p != NULL; p = p->next)
    {
      asection *sreloc = elf_section_data (p->section)->sreloc;
      sreloc->size += p->count * RELOC_SIZE (htab);
    }

  return TRUE;
}