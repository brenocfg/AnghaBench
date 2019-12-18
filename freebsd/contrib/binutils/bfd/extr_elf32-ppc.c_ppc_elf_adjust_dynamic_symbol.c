#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/ * dynobj; } ;
struct ppc_elf_link_hash_table {TYPE_15__* relbss; TYPE_15__* relsbss; TYPE_15__* dynbss; TYPE_15__* dynsbss; TYPE_1__ elf; } ;
struct ppc_elf_dyn_relocs {TYPE_9__* sec; struct ppc_elf_dyn_relocs* next; } ;
struct TYPE_26__ {scalar_t__ refcount; } ;
struct plt_entry {TYPE_2__ plt; struct plt_entry* next; } ;
struct TYPE_20__ {TYPE_11__* section; int /*<<< orphan*/  value; } ;
struct TYPE_21__ {TYPE_12__ def; } ;
struct TYPE_18__ {char* string; } ;
struct TYPE_22__ {scalar_t__ type; TYPE_13__ u; TYPE_10__ root; } ;
struct TYPE_32__ {TYPE_7__* weakdef; } ;
struct TYPE_27__ {struct plt_entry* plist; } ;
struct elf_link_hash_entry {scalar_t__ type; scalar_t__ size; int needs_copy; TYPE_14__ root; scalar_t__ non_got_ref; TYPE_8__ u; TYPE_3__ plt; scalar_t__ needs_plt; int /*<<< orphan*/  other; int /*<<< orphan*/  def_regular; scalar_t__ ref_regular; scalar_t__ def_dynamic; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_23__ {int flags; int size; } ;
typedef  TYPE_15__ asection ;
struct TYPE_33__ {TYPE_15__* output_section; } ;
struct TYPE_28__ {int /*<<< orphan*/  value; TYPE_11__* section; } ;
struct TYPE_29__ {TYPE_4__ def; } ;
struct TYPE_30__ {scalar_t__ type; TYPE_5__ u; } ;
struct TYPE_31__ {scalar_t__ non_got_ref; TYPE_6__ root; } ;
struct TYPE_24__ {scalar_t__ has_sda_refs; struct ppc_elf_dyn_relocs* dyn_relocs; } ;
struct TYPE_19__ {int flags; } ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ ELIMINATE_COPY_RELOCS ; 
 int SEC_ALLOC ; 
 int SEC_READONLY ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry*,TYPE_15__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_16__* ppc_elf_hash_entry (struct elf_link_hash_entry*) ; 
 struct ppc_elf_link_hash_table* ppc_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bfd_boolean
ppc_elf_adjust_dynamic_symbol (struct bfd_link_info *info,
			       struct elf_link_hash_entry *h)
{
  struct ppc_elf_link_hash_table *htab;
  asection *s;

#ifdef DEBUG
  fprintf (stderr, "ppc_elf_adjust_dynamic_symbol called for %s\n",
	   h->root.root.string);
#endif

  /* Make sure we know what is going on here.  */
  htab = ppc_elf_hash_table (info);
  BFD_ASSERT (htab->elf.dynobj != NULL
	      && (h->needs_plt
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  /* Deal with function syms.  */
  if (h->type == STT_FUNC
      || h->needs_plt)
    {
      /* Clear procedure linkage table information for any symbol that
	 won't need a .plt entry.  */
      struct plt_entry *ent;
      for (ent = h->plt.plist; ent != NULL; ent = ent->next)
	if (ent->plt.refcount > 0)
	  break;
      if (ent == NULL
	  || SYMBOL_CALLS_LOCAL (info, h)
	  || (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
	      && h->root.type == bfd_link_hash_undefweak))
	{
	  /* A PLT entry is not required/allowed when:

	     1. We are not using ld.so; because then the PLT entry
	     can't be set up, so we can't use one.  In this case,
	     ppc_elf_adjust_dynamic_symbol won't even be called.

	     2. GC has rendered the entry unused.

	     3. We know for certain that a call to this symbol
	     will go to this object, or will remain undefined.  */
	  h->plt.plist = NULL;
	  h->needs_plt = 0;
	}
      return TRUE;
    }
  else
    h->plt.plist = NULL;

  /* If this is a weak symbol, and there is a real definition, the
     processor independent code will have arranged for us to see the
     real definition first, and we can just use the same value.  */
  if (h->u.weakdef != NULL)
    {
      BFD_ASSERT (h->u.weakdef->root.type == bfd_link_hash_defined
		  || h->u.weakdef->root.type == bfd_link_hash_defweak);
      h->root.u.def.section = h->u.weakdef->root.u.def.section;
      h->root.u.def.value = h->u.weakdef->root.u.def.value;
      if (ELIMINATE_COPY_RELOCS)
	h->non_got_ref = h->u.weakdef->non_got_ref;
      return TRUE;
    }

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.  */

  /* If we are creating a shared library, we must presume that the
     only references to the symbol are via the global offset table.
     For such cases we need not do anything here; the relocations will
     be handled correctly by relocate_section.  */
  if (info->shared)
    return TRUE;

  /* If there are no references to this symbol that do not use the
     GOT, we don't need to generate a copy reloc.  */
  if (!h->non_got_ref)
    return TRUE;

   /* If we didn't find any dynamic relocs in read-only sections, then we'll
      be keeping the dynamic relocs and avoiding the copy reloc.  We can't
      do this if there are any small data relocations.  */
  if (ELIMINATE_COPY_RELOCS
      && !ppc_elf_hash_entry (h)->has_sda_refs)
    {
      struct ppc_elf_dyn_relocs *p;
      for (p = ppc_elf_hash_entry (h)->dyn_relocs; p != NULL; p = p->next)
	{
	  s = p->sec->output_section;
	  if (s != NULL && (s->flags & SEC_READONLY) != 0)
	    break;
	}

      if (p == NULL)
	{
	  h->non_got_ref = 0;
	  return TRUE;
	}
    }

  if (h->size == 0)
    {
      (*_bfd_error_handler) (_("dynamic variable `%s' is zero size"),
			     h->root.root.string);
      return TRUE;
    }

  /* We must allocate the symbol in our .dynbss section, which will
     become part of the .bss section of the executable.  There will be
     an entry for this symbol in the .dynsym section.  The dynamic
     object will contain position independent code, so all references
     from the dynamic object to this symbol will go through the global
     offset table.  The dynamic linker will use the .dynsym entry to
     determine the address it must put in the global offset table, so
     both the dynamic object and the regular object will refer to the
     same memory location for the variable.

     Of course, if the symbol is referenced using SDAREL relocs, we
     must instead allocate it in .sbss.  */

  if (ppc_elf_hash_entry (h)->has_sda_refs)
    s = htab->dynsbss;
  else
    s = htab->dynbss;
  BFD_ASSERT (s != NULL);

  /* We must generate a R_PPC_COPY reloc to tell the dynamic linker to
     copy the initial value out of the dynamic object and into the
     runtime process image.  We need to remember the offset into the
     .rela.bss section we are going to use.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      asection *srel;

      if (ppc_elf_hash_entry (h)->has_sda_refs)
	srel = htab->relsbss;
      else
	srel = htab->relbss;
      BFD_ASSERT (srel != NULL);
      srel->size += sizeof (Elf32_External_Rela);
      h->needs_copy = 1;
    }

  return _bfd_elf_adjust_dynamic_copy (h, s);
}