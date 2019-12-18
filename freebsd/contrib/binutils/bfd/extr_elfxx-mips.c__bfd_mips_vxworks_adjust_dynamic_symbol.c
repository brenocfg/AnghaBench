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
struct mips_elf_link_hash_table {scalar_t__ plt_header_size; scalar_t__ plt_entry_size; int /*<<< orphan*/  sdynbss; TYPE_14__* srelbss; TYPE_4__* srelplt2; TYPE_3__* srelplt; TYPE_2__* sgotplt; TYPE_10__* splt; } ;
struct mips_elf_link_hash_entry {scalar_t__ is_relocation_target; scalar_t__ is_branch_target; } ;
struct TYPE_17__ {scalar_t__ value; TYPE_10__* section; } ;
struct TYPE_18__ {TYPE_11__ def; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_12__ u; } ;
struct TYPE_30__ {TYPE_8__* weakdef; } ;
struct TYPE_22__ {scalar_t__ offset; } ;
struct elf_link_hash_entry {int needs_plt; int needs_copy; scalar_t__ type; TYPE_13__ root; TYPE_9__ u; int /*<<< orphan*/  def_regular; scalar_t__ ref_regular; scalar_t__ def_dynamic; TYPE_1__ plt; int /*<<< orphan*/  other; int /*<<< orphan*/  forced_local; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_26__ {scalar_t__ value; TYPE_10__* section; } ;
struct TYPE_27__ {TYPE_5__ def; } ;
struct TYPE_28__ {scalar_t__ type; TYPE_6__ u; } ;
struct TYPE_29__ {TYPE_7__ root; } ;
struct TYPE_25__ {int size; } ;
struct TYPE_24__ {int size; } ;
struct TYPE_23__ {int size; } ;
struct TYPE_21__ {int /*<<< orphan*/ * dynobj; } ;
struct TYPE_20__ {int size; } ;
struct TYPE_16__ {scalar_t__ size; int flags; } ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int SEC_ALLOC ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STV_DEFAULT ; 
 scalar_t__ SYMBOL_CALLS_LOCAL (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 TYPE_15__* elf_hash_table (struct bfd_link_info*) ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 

bfd_boolean
_bfd_mips_vxworks_adjust_dynamic_symbol (struct bfd_link_info *info,
					 struct elf_link_hash_entry *h)
{
  bfd *dynobj;
  struct mips_elf_link_hash_entry *hmips;
  struct mips_elf_link_hash_table *htab;

  htab = mips_elf_hash_table (info);
  dynobj = elf_hash_table (info)->dynobj;
  hmips = (struct mips_elf_link_hash_entry *) h;

  /* Make sure we know what is going on here.  */
  BFD_ASSERT (dynobj != NULL
	      && (h->needs_plt
		  || h->needs_copy
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  /* If the symbol is defined by a dynamic object, we need a PLT stub if
     either (a) we want to branch to the symbol or (b) we're linking an
     executable that needs a canonical function address.  In the latter
     case, the canonical address will be the address of the executable's
     load stub.  */
  if ((hmips->is_branch_target
       || (!info->shared
	   && h->type == STT_FUNC
	   && hmips->is_relocation_target))
      && h->def_dynamic
      && h->ref_regular
      && !h->def_regular
      && !h->forced_local)
    h->needs_plt = 1;

  /* Locally-binding symbols do not need a PLT stub; we can refer to
     the functions directly.  */
  else if (h->needs_plt
	   && (SYMBOL_CALLS_LOCAL (info, h)
	       || (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
		   && h->root.type == bfd_link_hash_undefweak)))
    {
      h->needs_plt = 0;
      return TRUE;
    }

  if (h->needs_plt)
    {
      /* If this is the first symbol to need a PLT entry, allocate room
	 for the header, and for the header's .rela.plt.unloaded entries.  */
      if (htab->splt->size == 0)
	{
	  htab->splt->size += htab->plt_header_size;
	  if (!info->shared)
	    htab->srelplt2->size += 2 * sizeof (Elf32_External_Rela);
	}

      /* Assign the next .plt entry to this symbol.  */
      h->plt.offset = htab->splt->size;
      htab->splt->size += htab->plt_entry_size;

      /* If the output file has no definition of the symbol, set the
	 symbol's value to the address of the stub.  For executables,
	 point at the PLT load stub rather than the lazy resolution stub;
	 this stub will become the canonical function address.  */
      if (!h->def_regular)
	{
	  h->root.u.def.section = htab->splt;
	  h->root.u.def.value = h->plt.offset;
	  if (!info->shared)
	    h->root.u.def.value += 8;
	}

      /* Make room for the .got.plt entry and the R_JUMP_SLOT relocation.  */
      htab->sgotplt->size += 4;
      htab->srelplt->size += sizeof (Elf32_External_Rela);

      /* Make room for the .rela.plt.unloaded relocations.  */
      if (!info->shared)
	htab->srelplt2->size += 3 * sizeof (Elf32_External_Rela);

      return TRUE;
    }

  /* If a function symbol is defined by a dynamic object, and we do not
     need a PLT stub for it, the symbol's value should be zero.  */
  if (h->type == STT_FUNC
      && h->def_dynamic
      && h->ref_regular
      && !h->def_regular)
    {
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
  if (info->shared)
    return TRUE;

  /* We must allocate the symbol in our .dynbss section, which will
     become part of the .bss section of the executable.  There will be
     an entry for this symbol in the .dynsym section.  The dynamic
     object will contain position independent code, so all references
     from the dynamic object to this symbol will go through the global
     offset table.  The dynamic linker will use the .dynsym entry to
     determine the address it must put in the global offset table, so
     both the dynamic object and the regular object will refer to the
     same memory location for the variable.  */

  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      htab->srelbss->size += sizeof (Elf32_External_Rela);
      h->needs_copy = 1;
    }

  return _bfd_elf_adjust_dynamic_copy (h, htab->sdynbss);
}