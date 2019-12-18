#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {struct elf_link_hash_entry* weakdef; } ;
struct TYPE_21__ {scalar_t__ link; } ;
struct TYPE_19__ {TYPE_12__* section; } ;
struct TYPE_22__ {TYPE_3__ i; TYPE_1__ def; } ;
struct TYPE_23__ {scalar_t__ type; TYPE_4__ u; } ;
struct elf_link_hash_entry {int ref_regular; int ref_regular_nonweak; int def_regular; int dynindx; int def_dynamic; TYPE_2__ u; TYPE_5__ root; int /*<<< orphan*/  other; scalar_t__ needs_plt; scalar_t__ ref_dynamic; scalar_t__ non_elf; } ;
struct elf_info_failed {int failed; TYPE_6__* info; } ;
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_copy_indirect_symbol ) (TYPE_6__*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ;int /*<<< orphan*/  (* elf_backend_hide_symbol ) (TYPE_6__*,struct elf_link_hash_entry*,int) ;int /*<<< orphan*/  (* elf_backend_fixup_symbol ) (TYPE_6__*,struct elf_link_hash_entry*) ;} ;
typedef  int bfd_boolean ;
struct TYPE_24__ {int /*<<< orphan*/  hash; scalar_t__ shared; } ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {TYPE_13__* owner; } ;
struct TYPE_16__ {scalar_t__ dynobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int DYNAMIC ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ STV_HIDDEN ; 
 scalar_t__ STV_INTERNAL ; 
 scalar_t__ SYMBOLIC_BIND (TYPE_6__*,struct elf_link_hash_entry*) ; 
 int TRUE ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (TYPE_6__*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_get_flavour (TYPE_13__*) ; 
 scalar_t__ bfd_is_abs_section (TYPE_12__*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_10__* elf_hash_table (TYPE_6__*) ; 
 struct elf_backend_data* get_elf_backend_data (scalar_t__) ; 
 scalar_t__ is_elf_hash_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,struct elf_link_hash_entry*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,struct elf_link_hash_entry*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 

bfd_boolean
_bfd_elf_fix_symbol_flags (struct elf_link_hash_entry *h,
			   struct elf_info_failed *eif)
{
  const struct elf_backend_data *bed = NULL;

  /* If this symbol was mentioned in a non-ELF file, try to set
     DEF_REGULAR and REF_REGULAR correctly.  This is the only way to
     permit a non-ELF file to correctly refer to a symbol defined in
     an ELF dynamic object.  */
  if (h->non_elf)
    {
      while (h->root.type == bfd_link_hash_indirect)
	h = (struct elf_link_hash_entry *) h->root.u.i.link;

      if (h->root.type != bfd_link_hash_defined
	  && h->root.type != bfd_link_hash_defweak)
	{
	  h->ref_regular = 1;
	  h->ref_regular_nonweak = 1;
	}
      else
	{
	  if (h->root.u.def.section->owner != NULL
	      && (bfd_get_flavour (h->root.u.def.section->owner)
		  == bfd_target_elf_flavour))
	    {
	      h->ref_regular = 1;
	      h->ref_regular_nonweak = 1;
	    }
	  else
	    h->def_regular = 1;
	}

      if (h->dynindx == -1
	  && (h->def_dynamic
	      || h->ref_dynamic))
	{
	  if (! bfd_elf_link_record_dynamic_symbol (eif->info, h))
	    {
	      eif->failed = TRUE;
	      return FALSE;
	    }
	}
    }
  else
    {
      /* Unfortunately, NON_ELF is only correct if the symbol
	 was first seen in a non-ELF file.  Fortunately, if the symbol
	 was first seen in an ELF file, we're probably OK unless the
	 symbol was defined in a non-ELF file.  Catch that case here.
	 FIXME: We're still in trouble if the symbol was first seen in
	 a dynamic object, and then later in a non-ELF regular object.  */
      if ((h->root.type == bfd_link_hash_defined
	   || h->root.type == bfd_link_hash_defweak)
	  && !h->def_regular
	  && (h->root.u.def.section->owner != NULL
	      ? (bfd_get_flavour (h->root.u.def.section->owner)
		 != bfd_target_elf_flavour)
	      : (bfd_is_abs_section (h->root.u.def.section)
		 && !h->def_dynamic)))
	h->def_regular = 1;
    }

  /* Backend specific symbol fixup.  */
  if (elf_hash_table (eif->info)->dynobj)
    {
      bed = get_elf_backend_data (elf_hash_table (eif->info)->dynobj);
      if (bed->elf_backend_fixup_symbol
	  && !(*bed->elf_backend_fixup_symbol) (eif->info, h))
	return FALSE;
    }

  /* If this is a final link, and the symbol was defined as a common
     symbol in a regular object file, and there was no definition in
     any dynamic object, then the linker will have allocated space for
     the symbol in a common section but the DEF_REGULAR
     flag will not have been set.  */
  if (h->root.type == bfd_link_hash_defined
      && !h->def_regular
      && h->ref_regular
      && !h->def_dynamic
      && (h->root.u.def.section->owner->flags & DYNAMIC) == 0)
    h->def_regular = 1;

  /* If -Bsymbolic was used (which means to bind references to global
     symbols to the definition within the shared object), and this
     symbol was defined in a regular object, then it actually doesn't
     need a PLT entry.  Likewise, if the symbol has non-default
     visibility.  If the symbol has hidden or internal visibility, we
     will force it local.  */
  if (h->needs_plt
      && eif->info->shared
      && is_elf_hash_table (eif->info->hash)
      && (SYMBOLIC_BIND (eif->info, h)
	  || ELF_ST_VISIBILITY (h->other) != STV_DEFAULT)
      && h->def_regular)
    {
      bfd_boolean force_local;

      force_local = (ELF_ST_VISIBILITY (h->other) == STV_INTERNAL
		     || ELF_ST_VISIBILITY (h->other) == STV_HIDDEN);
      (*bed->elf_backend_hide_symbol) (eif->info, h, force_local);
    }

  /* If a weak undefined symbol has non-default visibility, we also
     hide it from the dynamic linker.  */
  if (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
      && h->root.type == bfd_link_hash_undefweak)
    {
      const struct elf_backend_data *bed;
      bed = get_elf_backend_data (elf_hash_table (eif->info)->dynobj);
      (*bed->elf_backend_hide_symbol) (eif->info, h, TRUE);
    }

  /* If this is a weak defined symbol in a dynamic object, and we know
     the real definition in the dynamic object, copy interesting flags
     over to the real definition.  */
  if (h->u.weakdef != NULL)
    {
      struct elf_link_hash_entry *weakdef;

      weakdef = h->u.weakdef;
      if (h->root.type == bfd_link_hash_indirect)
	h = (struct elf_link_hash_entry *) h->root.u.i.link;

      BFD_ASSERT (h->root.type == bfd_link_hash_defined
		  || h->root.type == bfd_link_hash_defweak);
      BFD_ASSERT (weakdef->root.type == bfd_link_hash_defined
		  || weakdef->root.type == bfd_link_hash_defweak);
      BFD_ASSERT (weakdef->def_dynamic);

      /* If the real definition is defined by a regular object file,
	 don't do anything special.  See the longer description in
	 _bfd_elf_adjust_dynamic_symbol, below.  */
      if (weakdef->def_regular)
	h->u.weakdef = NULL;
      else
	(*bed->elf_backend_copy_indirect_symbol) (eif->info, weakdef,
						  h);
    }

  return TRUE;
}