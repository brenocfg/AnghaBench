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
struct TYPE_18__ {TYPE_10__* section; int /*<<< orphan*/  value; } ;
struct TYPE_19__ {TYPE_11__ def; } ;
struct TYPE_31__ {int /*<<< orphan*/  string; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_12__ u; TYPE_9__ root; } ;
struct TYPE_29__ {TYPE_6__* weakdef; } ;
struct TYPE_24__ {scalar_t__ refcount; void* offset; } ;
struct elf_link_hash_entry {scalar_t__ type; scalar_t__ size; int needs_copy; TYPE_13__ root; scalar_t__ non_got_ref; TYPE_7__ u; TYPE_2__ plt; scalar_t__ needs_plt; int /*<<< orphan*/  ref_dynamic; scalar_t__ def_dynamic; int /*<<< orphan*/  def_regular; scalar_t__ ref_regular; } ;
struct bfd_link_info {scalar_t__ shared; } ;
struct TYPE_23__ {int /*<<< orphan*/ * dynobj; } ;
struct _bfd_sparc_elf_link_hash_table {TYPE_15__* sdynbss; TYPE_14__* srelbss; TYPE_1__ elf; } ;
struct _bfd_sparc_elf_link_hash_entry {struct _bfd_sparc_elf_dyn_relocs* dyn_relocs; } ;
struct _bfd_sparc_elf_dyn_relocs {TYPE_8__* sec; struct _bfd_sparc_elf_dyn_relocs* next; } ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_22__ {int flags; } ;
typedef  TYPE_15__ asection ;
struct TYPE_30__ {TYPE_15__* output_section; } ;
struct TYPE_25__ {int /*<<< orphan*/  value; TYPE_10__* section; } ;
struct TYPE_26__ {TYPE_3__ def; } ;
struct TYPE_27__ {scalar_t__ type; TYPE_4__ u; } ;
struct TYPE_28__ {TYPE_5__ root; } ;
struct TYPE_21__ {int /*<<< orphan*/  size; } ;
struct TYPE_17__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_READONLY ; 
 scalar_t__ SPARC_ELF_RELA_BYTES (struct _bfd_sparc_elf_link_hash_table*) ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STT_NOTYPE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry*,TYPE_15__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_sparc_elf_adjust_dynamic_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *h)
{
  struct _bfd_sparc_elf_link_hash_table *htab;
  struct _bfd_sparc_elf_link_hash_entry * eh;
  struct _bfd_sparc_elf_dyn_relocs *p;
  asection *s;

  htab = _bfd_sparc_elf_hash_table (info);

  /* Make sure we know what is going on here.  */
  BFD_ASSERT (htab->elf.dynobj != NULL
	      && (h->needs_plt
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  /* If this is a function, put it in the procedure linkage table.  We
     will fill in the contents of the procedure linkage table later
     (although we could actually do it here).  The STT_NOTYPE
     condition is a hack specifically for the Oracle libraries
     delivered for Solaris; for some inexplicable reason, they define
     some of their functions as STT_NOTYPE when they really should be
     STT_FUNC.  */
  if (h->type == STT_FUNC
      || h->needs_plt
      || (h->type == STT_NOTYPE
	  && (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak)
	  && (h->root.u.def.section->flags & SEC_CODE) != 0))
    {
      if (h->plt.refcount <= 0
	  || (! info->shared
	      && !h->def_dynamic
	      && !h->ref_dynamic
	      && h->root.type != bfd_link_hash_undefweak
	      && h->root.type != bfd_link_hash_undefined))
	{
	  /* This case can occur if we saw a WPLT30 reloc in an input
	     file, but the symbol was never referred to by a dynamic
	     object, or if all references were garbage collected.  In
	     such a case, we don't actually need to build a procedure
	     linkage table, and we can just do a WDISP30 reloc instead.  */
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	}

      return TRUE;
    }
  else
    h->plt.offset = (bfd_vma) -1;

  /* If this is a weak symbol, and there is a real definition, the
     processor independent code will have arranged for us to see the
     real definition first, and we can just use the same value.  */
  if (h->u.weakdef != NULL)
    {
      BFD_ASSERT (h->u.weakdef->root.type == bfd_link_hash_defined
		  || h->u.weakdef->root.type == bfd_link_hash_defweak);
      h->root.u.def.section = h->u.weakdef->root.u.def.section;
      h->root.u.def.value = h->u.weakdef->root.u.def.value;
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

  eh = (struct _bfd_sparc_elf_link_hash_entry *) h;
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      s = p->sec->output_section;
      if (s != NULL && (s->flags & SEC_READONLY) != 0)
	break;
    }

  /* If we didn't find any dynamic relocs in read-only sections, then
     we'll be keeping the dynamic relocs and avoiding the copy reloc.  */
  if (p == NULL)
    {
      h->non_got_ref = 0;
      return TRUE;
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
     same memory location for the variable.  */

  /* We must generate a R_SPARC_COPY reloc to tell the dynamic linker
     to copy the initial value out of the dynamic object and into the
     runtime process image.  We need to remember the offset into the
     .rel.bss section we are going to use.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      htab->srelbss->size += SPARC_ELF_RELA_BYTES (htab);
      h->needs_copy = 1;
    }

  s = htab->sdynbss;

  return _bfd_elf_adjust_dynamic_copy (h, s);
}