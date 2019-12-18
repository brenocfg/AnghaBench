#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct ppc_link_hash_table {int /*<<< orphan*/  elf; } ;
struct TYPE_30__ {TYPE_10__* section; int /*<<< orphan*/  value; } ;
struct TYPE_31__ {TYPE_1__ def; } ;
struct TYPE_32__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_33__ {TYPE_3__ root; } ;
struct ppc_link_hash_entry {TYPE_4__ elf; struct ppc_link_hash_entry* oh; scalar_t__ is_func_descriptor; } ;
struct TYPE_36__ {TYPE_6__* p; } ;
struct TYPE_34__ {TYPE_10__* section; } ;
struct TYPE_37__ {TYPE_7__ c; TYPE_5__ def; } ;
struct TYPE_38__ {TYPE_8__ u; int /*<<< orphan*/  type; } ;
struct elf_link_hash_entry {TYPE_9__ root; } ;
struct bfd_sym_chain {int /*<<< orphan*/  name; struct bfd_sym_chain* next; } ;
struct bfd_link_info {struct bfd_sym_chain* gc_sym_list; } ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_27__ {int /*<<< orphan*/  gc_mark; int /*<<< orphan*/  owner; } ;
typedef  TYPE_10__ asection ;
struct TYPE_35__ {TYPE_10__* section; } ;
struct TYPE_29__ {int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_28__ {int st_value; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_11__ Elf_Internal_Sym ;
typedef  TYPE_12__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
#define  R_PPC64_GNU_VTENTRY 132 
#define  R_PPC64_GNU_VTINHERIT 131 
 int /*<<< orphan*/  _bfd_elf_gc_mark (struct bfd_link_info*,TYPE_10__*,TYPE_10__* (*) (TYPE_10__*,struct bfd_link_info*,TYPE_12__*,struct elf_link_hash_entry*,TYPE_11__*)) ; 
#define  bfd_link_hash_common 130 
#define  bfd_link_hash_defined 129 
#define  bfd_link_hash_defweak 128 
 TYPE_10__* bfd_section_from_elf_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_link_hash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__** get_opd_info (TYPE_10__*) ; 
 scalar_t__ opd_entry_value (TYPE_10__*,int /*<<< orphan*/ ,TYPE_10__**,int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static asection *
ppc64_elf_gc_mark_hook (asection *sec,
			struct bfd_link_info *info,
			Elf_Internal_Rela *rel,
			struct elf_link_hash_entry *h,
			Elf_Internal_Sym *sym)
{
  asection *rsec;

  /* First mark all our entry sym sections.  */
  if (info->gc_sym_list != NULL)
    {
      struct ppc_link_hash_table *htab = ppc_hash_table (info);
      struct bfd_sym_chain *sym = info->gc_sym_list;

      info->gc_sym_list = NULL;
      for (; sym != NULL; sym = sym->next)
	{
	  struct ppc_link_hash_entry *eh;

	  eh = (struct ppc_link_hash_entry *)
	    elf_link_hash_lookup (&htab->elf, sym->name, FALSE, FALSE, FALSE);
	  if (eh == NULL)
	    continue;
	  if (eh->elf.root.type != bfd_link_hash_defined
	      && eh->elf.root.type != bfd_link_hash_defweak)
	    continue;

	  if (eh->is_func_descriptor
	      && (eh->oh->elf.root.type == bfd_link_hash_defined
		  || eh->oh->elf.root.type == bfd_link_hash_defweak))
	    rsec = eh->oh->elf.root.u.def.section;
	  else if (get_opd_info (eh->elf.root.u.def.section) != NULL
		   && opd_entry_value (eh->elf.root.u.def.section,
				       eh->elf.root.u.def.value,
				       &rsec, NULL) != (bfd_vma) -1)
	    ;
	  else
	    continue;

	  if (!rsec->gc_mark)
	    _bfd_elf_gc_mark (info, rsec, ppc64_elf_gc_mark_hook);

	  rsec = eh->elf.root.u.def.section;
	  if (!rsec->gc_mark)
	    _bfd_elf_gc_mark (info, rsec, ppc64_elf_gc_mark_hook);
	}
    }

  /* Syms return NULL if we're marking .opd, so we avoid marking all
     function sections, as all functions are referenced in .opd.  */
  rsec = NULL;
  if (get_opd_info (sec) != NULL)
    return rsec;

  if (h != NULL)
    {
      enum elf_ppc64_reloc_type r_type;
      struct ppc_link_hash_entry *eh;

      r_type = ELF64_R_TYPE (rel->r_info);
      switch (r_type)
	{
	case R_PPC64_GNU_VTINHERIT:
	case R_PPC64_GNU_VTENTRY:
	  break;

	default:
	  switch (h->root.type)
	    {
	    case bfd_link_hash_defined:
	    case bfd_link_hash_defweak:
	      eh = (struct ppc_link_hash_entry *) h;
	      if (eh->oh != NULL
		  && eh->oh->is_func_descriptor
		  && (eh->oh->elf.root.type == bfd_link_hash_defined
		      || eh->oh->elf.root.type == bfd_link_hash_defweak))
		eh = eh->oh;

	      /* Function descriptor syms cause the associated
		 function code sym section to be marked.  */
	      if (eh->is_func_descriptor
		  && (eh->oh->elf.root.type == bfd_link_hash_defined
		      || eh->oh->elf.root.type == bfd_link_hash_defweak))
		{
		  /* They also mark their opd section.  */
		  if (!eh->elf.root.u.def.section->gc_mark)
		    _bfd_elf_gc_mark (info, eh->elf.root.u.def.section,
				      ppc64_elf_gc_mark_hook);

		  rsec = eh->oh->elf.root.u.def.section;
		}
	      else if (get_opd_info (eh->elf.root.u.def.section) != NULL
		       && opd_entry_value (eh->elf.root.u.def.section,
					   eh->elf.root.u.def.value,
					   &rsec, NULL) != (bfd_vma) -1)
		{
		  if (!eh->elf.root.u.def.section->gc_mark)
		    _bfd_elf_gc_mark (info, eh->elf.root.u.def.section,
				      ppc64_elf_gc_mark_hook);
		}
	      else
		rsec = h->root.u.def.section;
	      break;

	    case bfd_link_hash_common:
	      rsec = h->root.u.c.p->section;
	      break;

	    default:
	      break;
	    }
	}
    }
  else
    {
      asection **opd_sym_section;

      rsec = bfd_section_from_elf_index (sec->owner, sym->st_shndx);
      opd_sym_section = get_opd_info (rsec);
      if (opd_sym_section != NULL)
	{
	  if (!rsec->gc_mark)
	    _bfd_elf_gc_mark (info, rsec, ppc64_elf_gc_mark_hook);

	  rsec = opd_sym_section[(sym->st_value + rel->r_addend) / 8];
	}
    }

  return rsec;
}