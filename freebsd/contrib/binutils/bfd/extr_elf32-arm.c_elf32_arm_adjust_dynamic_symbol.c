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
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_9__* section; int /*<<< orphan*/  value; } ;
struct TYPE_18__ {TYPE_10__ def; } ;
struct TYPE_29__ {int /*<<< orphan*/  string; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_11__ u; TYPE_8__ root; } ;
struct TYPE_27__ {TYPE_5__* weakdef; } ;
struct TYPE_22__ {scalar_t__ refcount; void* offset; } ;
struct elf_link_hash_entry {scalar_t__ type; scalar_t__ size; int needs_copy; TYPE_12__ root; int /*<<< orphan*/  non_got_ref; TYPE_6__ u; TYPE_1__ plt; scalar_t__ needs_plt; int /*<<< orphan*/  other; int /*<<< orphan*/  def_regular; scalar_t__ ref_regular; scalar_t__ def_dynamic; } ;
struct TYPE_28__ {scalar_t__ is_relocatable_executable; } ;
struct elf32_arm_link_hash_table {TYPE_7__ root; } ;
struct elf32_arm_link_hash_entry {scalar_t__ plt_thumb_refcount; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_20__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_13__ asection ;
struct TYPE_30__ {int flags; } ;
struct TYPE_23__ {int /*<<< orphan*/  value; TYPE_9__* section; } ;
struct TYPE_24__ {TYPE_2__ def; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_3__ u; } ;
struct TYPE_26__ {TYPE_4__ root; } ;
struct TYPE_21__ {int /*<<< orphan*/ * dynobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 char* RELOC_SECTION (struct elf32_arm_link_hash_table*,char*) ; 
 scalar_t__ RELOC_SIZE (struct elf32_arm_link_hash_table*) ; 
 int SEC_ALLOC ; 
 scalar_t__ STT_ARM_TFUNC ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry*,TYPE_13__*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 TYPE_14__* elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_adjust_dynamic_symbol (struct bfd_link_info * info,
				 struct elf_link_hash_entry * h)
{
  bfd * dynobj;
  asection * s;
  struct elf32_arm_link_hash_entry * eh;
  struct elf32_arm_link_hash_table *globals;

  globals = elf32_arm_hash_table (info);
  dynobj = elf_hash_table (info)->dynobj;

  /* Make sure we know what is going on here.  */
  BFD_ASSERT (dynobj != NULL
	      && (h->needs_plt
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  eh = (struct elf32_arm_link_hash_entry *) h;

  /* If this is a function, put it in the procedure linkage table.  We
     will fill in the contents of the procedure linkage table later,
     when we know the address of the .got section.  */
  if (h->type == STT_FUNC || h->type == STT_ARM_TFUNC
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
	     linkage table, and we can just do a PC24 reloc instead.  */
	  h->plt.offset = (bfd_vma) -1;
	  eh->plt_thumb_refcount = 0;
	  h->needs_plt = 0;
	}

      return TRUE;
    }
  else
    {
      /* It's possible that we incorrectly decided a .plt reloc was
	 needed for an R_ARM_PC24 or similar reloc to a non-function sym
	 in check_relocs.  We can't decide accurately between function
	 and non-function syms in check-relocs; Objects loaded later in
	 the link may change h->type.  So fix it now.  */
      h->plt.offset = (bfd_vma) -1;
      eh->plt_thumb_refcount = 0;
    }

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

  /* If there are no non-GOT references, we do not need a copy
     relocation.  */
  if (!h->non_got_ref)
    return TRUE;

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.  */

  /* If we are creating a shared library, we must presume that the
     only references to the symbol are via the global offset table.
     For such cases we need not do anything here; the relocations will
     be handled correctly by relocate_section.  Relocatable executables
     can reference data in shared objects directly, so we don't need to
     do anything here.  */
  if (info->shared || globals->root.is_relocatable_executable)
    return TRUE;

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
  s = bfd_get_section_by_name (dynobj, ".dynbss");
  BFD_ASSERT (s != NULL);

  /* We must generate a R_ARM_COPY reloc to tell the dynamic linker to
     copy the initial value out of the dynamic object and into the
     runtime process image.  We need to remember the offset into the
     .rel(a).bss section we are going to use.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      asection *srel;

      srel = bfd_get_section_by_name (dynobj, RELOC_SECTION (globals, ".bss"));
      BFD_ASSERT (srel != NULL);
      srel->size += RELOC_SIZE (globals);
      h->needs_copy = 1;
    }

  return _bfd_elf_adjust_dynamic_copy (h, s);
}