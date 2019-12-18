#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ refcount; } ;
struct elf_link_hash_entry {int /*<<< orphan*/  pointer_equality_needed; int /*<<< orphan*/  needs_plt; int /*<<< orphan*/  ref_regular_nonweak; int /*<<< orphan*/  ref_regular; int /*<<< orphan*/  ref_dynamic; scalar_t__ dynamic_adjusted; TYPE_2__ root; TYPE_1__ got; } ;
struct elf64_x86_64_link_hash_entry {int /*<<< orphan*/  tls_type; struct elf64_x86_64_dyn_relocs* dyn_relocs; } ;
struct elf64_x86_64_dyn_relocs {scalar_t__ sec; struct elf64_x86_64_dyn_relocs* next; scalar_t__ count; scalar_t__ pc_count; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ELIMINATE_COPY_RELOCS ; 
 int /*<<< orphan*/  GOT_UNKNOWN ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_copy_indirect (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 

__attribute__((used)) static void
elf64_x86_64_copy_indirect_symbol (struct bfd_link_info *info,
				   struct elf_link_hash_entry *dir,
				   struct elf_link_hash_entry *ind)
{
  struct elf64_x86_64_link_hash_entry *edir, *eind;

  edir = (struct elf64_x86_64_link_hash_entry *) dir;
  eind = (struct elf64_x86_64_link_hash_entry *) ind;

  if (eind->dyn_relocs != NULL)
    {
      if (edir->dyn_relocs != NULL)
	{
	  struct elf64_x86_64_dyn_relocs **pp;
	  struct elf64_x86_64_dyn_relocs *p;

	  /* Add reloc counts against the indirect sym to the direct sym
	     list.  Merge any entries against the same section.  */
	  for (pp = &eind->dyn_relocs; (p = *pp) != NULL; )
	    {
	      struct elf64_x86_64_dyn_relocs *q;

	      for (q = edir->dyn_relocs; q != NULL; q = q->next)
		if (q->sec == p->sec)
		  {
		    q->pc_count += p->pc_count;
		    q->count += p->count;
		    *pp = p->next;
		    break;
		  }
	      if (q == NULL)
		pp = &p->next;
	    }
	  *pp = edir->dyn_relocs;
	}

      edir->dyn_relocs = eind->dyn_relocs;
      eind->dyn_relocs = NULL;
    }

  if (ind->root.type == bfd_link_hash_indirect
      && dir->got.refcount <= 0)
    {
      edir->tls_type = eind->tls_type;
      eind->tls_type = GOT_UNKNOWN;
    }

  if (ELIMINATE_COPY_RELOCS
      && ind->root.type != bfd_link_hash_indirect
      && dir->dynamic_adjusted)
    {
      /* If called to transfer flags for a weakdef during processing
	 of elf_adjust_dynamic_symbol, don't copy non_got_ref.
	 We clear it ourselves for ELIMINATE_COPY_RELOCS.  */
      dir->ref_dynamic |= ind->ref_dynamic;
      dir->ref_regular |= ind->ref_regular;
      dir->ref_regular_nonweak |= ind->ref_regular_nonweak;
      dir->needs_plt |= ind->needs_plt;
      dir->pointer_equality_needed |= ind->pointer_equality_needed;
    }
  else
    _bfd_elf_link_hash_copy_indirect (info, dir, ind);
}