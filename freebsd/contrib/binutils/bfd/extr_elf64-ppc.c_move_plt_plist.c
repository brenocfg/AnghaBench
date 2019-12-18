#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct plt_entry* plist; } ;
struct TYPE_6__ {TYPE_2__ plt; } ;
struct ppc_link_hash_entry {TYPE_3__ elf; } ;
struct TYPE_4__ {scalar_t__ refcount; } ;
struct plt_entry {scalar_t__ addend; struct plt_entry* next; TYPE_1__ plt; } ;

/* Variables and functions */

__attribute__((used)) static void
move_plt_plist (struct ppc_link_hash_entry *from,
		struct ppc_link_hash_entry *to)
{
  if (from->elf.plt.plist != NULL)
    {
      if (to->elf.plt.plist != NULL)
	{
	  struct plt_entry **entp;
	  struct plt_entry *ent;

	  for (entp = &from->elf.plt.plist; (ent = *entp) != NULL; )
	    {
	      struct plt_entry *dent;

	      for (dent = to->elf.plt.plist; dent != NULL; dent = dent->next)
		if (dent->addend == ent->addend)
		  {
		    dent->plt.refcount += ent->plt.refcount;
		    *entp = ent->next;
		    break;
		  }
	      if (dent == NULL)
		entp = &ent->next;
	    }
	  *entp = to->elf.plt.plist;
	}

      to->elf.plt.plist = from->elf.plt.plist;
      from->elf.plt.plist = NULL;
    }
}