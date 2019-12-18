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
struct TYPE_4__ {scalar_t__ refcount; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct elf_link_hash_entry {TYPE_2__ got; TYPE_1__ root; } ;
struct bfd_link_info {int dummy; } ;
struct _bfd_sparc_elf_link_hash_entry {int /*<<< orphan*/  tls_type; struct _bfd_sparc_elf_dyn_relocs* dyn_relocs; } ;
struct _bfd_sparc_elf_dyn_relocs {scalar_t__ sec; struct _bfd_sparc_elf_dyn_relocs* next; scalar_t__ count; scalar_t__ pc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOT_UNKNOWN ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_copy_indirect (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 

void
_bfd_sparc_elf_copy_indirect_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *dir,
				     struct elf_link_hash_entry *ind)
{
  struct _bfd_sparc_elf_link_hash_entry *edir, *eind;

  edir = (struct _bfd_sparc_elf_link_hash_entry *) dir;
  eind = (struct _bfd_sparc_elf_link_hash_entry *) ind;

  if (eind->dyn_relocs != NULL)
    {
      if (edir->dyn_relocs != NULL)
	{
	  struct _bfd_sparc_elf_dyn_relocs **pp;
	  struct _bfd_sparc_elf_dyn_relocs *p;

	  /* Add reloc counts against the indirect sym to the direct sym
	     list.  Merge any entries against the same section.  */
	  for (pp = &eind->dyn_relocs; (p = *pp) != NULL; )
	    {
	      struct _bfd_sparc_elf_dyn_relocs *q;

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
  _bfd_elf_link_hash_copy_indirect (info, dir, ind);
}