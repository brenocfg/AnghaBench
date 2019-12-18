#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct mips_elf_link_hash_table {scalar_t__ function_stub_size; } ;
struct mips_elf_link_hash_entry {scalar_t__ possibly_dynamic_relocs; int /*<<< orphan*/  no_fn_stub; scalar_t__ readonly_reloc; } ;
struct TYPE_23__ {TYPE_8__* weakdef; } ;
struct TYPE_16__ {int /*<<< orphan*/  value; TYPE_10__* section; } ;
struct TYPE_17__ {TYPE_2__ def; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_3__ u; } ;
struct TYPE_15__ {int /*<<< orphan*/  offset; } ;
struct elf_link_hash_entry {scalar_t__ type; TYPE_9__ u; TYPE_4__ root; scalar_t__ needs_plt; TYPE_1__ plt; int /*<<< orphan*/  def_regular; scalar_t__ ref_regular; scalar_t__ def_dynamic; } ;
struct bfd_link_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  relocatable; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_10__ asection ;
struct TYPE_19__ {int /*<<< orphan*/  value; TYPE_10__* section; } ;
struct TYPE_20__ {TYPE_5__ def; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_6__ u; } ;
struct TYPE_22__ {TYPE_7__ root; } ;
struct TYPE_14__ {int /*<<< orphan*/  dynamic_sections_created; int /*<<< orphan*/ * dynobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  DF_TEXTREL ; 
 int /*<<< orphan*/  MIPS_ELF_STUB_SECTION_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ STT_FUNC ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_10__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 TYPE_11__* elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  mips_elf_allocate_dynamic_relocations (int /*<<< orphan*/ *,struct bfd_link_info*,scalar_t__) ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 

bfd_boolean
_bfd_mips_elf_adjust_dynamic_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *h)
{
  bfd *dynobj;
  struct mips_elf_link_hash_entry *hmips;
  asection *s;
  struct mips_elf_link_hash_table *htab;

  htab = mips_elf_hash_table (info);
  dynobj = elf_hash_table (info)->dynobj;

  /* Make sure we know what is going on here.  */
  BFD_ASSERT (dynobj != NULL
	      && (h->needs_plt
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  /* If this symbol is defined in a dynamic object, we need to copy
     any R_MIPS_32 or R_MIPS_REL32 relocs against it into the output
     file.  */
  hmips = (struct mips_elf_link_hash_entry *) h;
  if (! info->relocatable
      && hmips->possibly_dynamic_relocs != 0
      && (h->root.type == bfd_link_hash_defweak
	  || !h->def_regular))
    {
      mips_elf_allocate_dynamic_relocations
	(dynobj, info, hmips->possibly_dynamic_relocs);
      if (hmips->readonly_reloc)
	/* We tell the dynamic linker that there are relocations
	   against the text segment.  */
	info->flags |= DF_TEXTREL;
    }

  /* For a function, create a stub, if allowed.  */
  if (! hmips->no_fn_stub
      && h->needs_plt)
    {
      if (! elf_hash_table (info)->dynamic_sections_created)
	return TRUE;

      /* If this symbol is not defined in a regular file, then set
	 the symbol to the stub location.  This is required to make
	 function pointers compare as equal between the normal
	 executable and the shared library.  */
      if (!h->def_regular)
	{
	  /* We need .stub section.  */
	  s = bfd_get_section_by_name (dynobj,
				       MIPS_ELF_STUB_SECTION_NAME (dynobj));
	  BFD_ASSERT (s != NULL);

	  h->root.u.def.section = s;
	  h->root.u.def.value = s->size;

	  /* XXX Write this stub address somewhere.  */
	  h->plt.offset = s->size;

	  /* Make room for this stub code.  */
	  s->size += htab->function_stub_size;

	  /* The last half word of the stub will be filled with the index
	     of this symbol in .dynsym section.  */
	  return TRUE;
	}
    }
  else if ((h->type == STT_FUNC)
	   && !h->needs_plt)
    {
      /* This will set the entry for this symbol in the GOT to 0, and
         the dynamic linker will take care of this.  */
      h->root.u.def.value = 0;
      return TRUE;
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

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.  */

  return TRUE;
}