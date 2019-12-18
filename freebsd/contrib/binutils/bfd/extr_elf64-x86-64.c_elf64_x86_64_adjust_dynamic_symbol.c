#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_9__* section; int /*<<< orphan*/  value; } ;
struct TYPE_17__ {TYPE_10__ def; } ;
struct TYPE_28__ {int /*<<< orphan*/  string; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_11__ u; TYPE_8__ root; } ;
struct TYPE_26__ {TYPE_5__* weakdef; } ;
struct TYPE_21__ {scalar_t__ refcount; void* offset; } ;
struct elf_link_hash_entry {scalar_t__ type; scalar_t__ size; int needs_copy; TYPE_12__ root; scalar_t__ non_got_ref; TYPE_6__ u; TYPE_1__ plt; scalar_t__ needs_plt; int /*<<< orphan*/  other; } ;
struct elf64_x86_64_link_hash_table {TYPE_14__* sdynbss; TYPE_13__* srelbss; } ;
struct elf64_x86_64_link_hash_entry {struct elf64_x86_64_dyn_relocs* dyn_relocs; } ;
struct elf64_x86_64_dyn_relocs {TYPE_7__* sec; struct elf64_x86_64_dyn_relocs* next; } ;
struct bfd_link_info {scalar_t__ nocopyreloc; scalar_t__ shared; } ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_20__ {int flags; } ;
typedef  TYPE_14__ asection ;
struct TYPE_29__ {int flags; } ;
struct TYPE_27__ {TYPE_14__* output_section; } ;
struct TYPE_22__ {int /*<<< orphan*/  value; TYPE_9__* section; } ;
struct TYPE_23__ {TYPE_2__ def; } ;
struct TYPE_24__ {scalar_t__ type; TYPE_3__ u; } ;
struct TYPE_25__ {scalar_t__ non_got_ref; TYPE_4__ root; } ;
struct TYPE_19__ {int size; } ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;

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
 int /*<<< orphan*/  _bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry*,TYPE_14__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 struct elf64_x86_64_link_hash_table* elf64_x86_64_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_adjust_dynamic_symbol (struct bfd_link_info *info,
				    struct elf_link_hash_entry *h)
{
  struct elf64_x86_64_link_hash_table *htab;
  asection *s;

  /* If this is a function, put it in the procedure linkage table.  We
     will fill in the contents of the procedure linkage table later,
     when we know the address of the .got section.  */
  if (h->type == STT_FUNC
      || h->needs_plt)
    {
      if (h->plt.refcount <= 0
	  || SYMBOL_CALLS_LOCAL (info, h)
	  || (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
	      && h->root.type == bfd_link_hash_undefweak))
	{
	  /* This case can occur if we saw a PLT32 reloc in an input
	     file, but the symbol was never referred to by a dynamic
	     object, or if all references were garbage collected.  In
	     such a case, we don't actually need to build a procedure
	     linkage table, and we can just do a PC32 reloc instead.  */
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	}

      return TRUE;
    }
  else
    /* It's possible that we incorrectly decided a .plt reloc was
       needed for an R_X86_64_PC32 reloc to a non-function sym in
       check_relocs.  We can't decide accurately between function and
       non-function syms in check-relocs;  Objects loaded later in
       the link may change h->type.  So fix it now.  */
    h->plt.offset = (bfd_vma) -1;

  /* If this is a weak symbol, and there is a real definition, the
     processor independent code will have arranged for us to see the
     real definition first, and we can just use the same value.	 */
  if (h->u.weakdef != NULL)
    {
      BFD_ASSERT (h->u.weakdef->root.type == bfd_link_hash_defined
		  || h->u.weakdef->root.type == bfd_link_hash_defweak);
      h->root.u.def.section = h->u.weakdef->root.u.def.section;
      h->root.u.def.value = h->u.weakdef->root.u.def.value;
      if (ELIMINATE_COPY_RELOCS || info->nocopyreloc)
	h->non_got_ref = h->u.weakdef->non_got_ref;
      return TRUE;
    }

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.	 */

  /* If we are creating a shared library, we must presume that the
     only references to the symbol are via the global offset table.
     For such cases we need not do anything here; the relocations will
     be handled correctly by relocate_section.	*/
  if (info->shared)
    return TRUE;

  /* If there are no references to this symbol that do not use the
     GOT, we don't need to generate a copy reloc.  */
  if (!h->non_got_ref)
    return TRUE;

  /* If -z nocopyreloc was given, we won't generate them either.  */
  if (info->nocopyreloc)
    {
      h->non_got_ref = 0;
      return TRUE;
    }

  if (ELIMINATE_COPY_RELOCS)
    {
      struct elf64_x86_64_link_hash_entry * eh;
      struct elf64_x86_64_dyn_relocs *p;

      eh = (struct elf64_x86_64_link_hash_entry *) h;
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
    }

  if (h->size == 0)
    {
      (*_bfd_error_handler) (_("dynamic variable `%s' is zero size"),
			     h->root.root.string);
      return TRUE;
    }

  /* We must allocate the symbol in our .dynbss section, which will
     become part of the .bss section of the executable.	 There will be
     an entry for this symbol in the .dynsym section.  The dynamic
     object will contain position independent code, so all references
     from the dynamic object to this symbol will go through the global
     offset table.  The dynamic linker will use the .dynsym entry to
     determine the address it must put in the global offset table, so
     both the dynamic object and the regular object will refer to the
     same memory location for the variable.  */

  htab = elf64_x86_64_hash_table (info);

  /* We must generate a R_X86_64_COPY reloc to tell the dynamic linker
     to copy the initial value out of the dynamic object and into the
     runtime process image.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      htab->srelbss->size += sizeof (Elf64_External_Rela);
      h->needs_copy = 1;
    }

  s = htab->sdynbss;

  return _bfd_elf_adjust_dynamic_copy (h, s);
}