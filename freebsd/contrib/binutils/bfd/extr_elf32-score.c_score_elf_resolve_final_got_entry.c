#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct score_elf_link_hash_entry* h; } ;
struct score_got_entry {int symndx; TYPE_5__ d; int /*<<< orphan*/ * abfd; } ;
struct TYPE_6__ {scalar_t__ link; } ;
struct TYPE_7__ {TYPE_1__ i; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ root; } ;
struct score_elf_link_hash_entry {TYPE_4__ root; } ;
typedef  int /*<<< orphan*/ * htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  htab_clear_slot (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  htab_find (int /*<<< orphan*/ *,struct score_got_entry*) ; 
 void** htab_find_slot (int /*<<< orphan*/ *,struct score_got_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
score_elf_resolve_final_got_entry (void **entryp, void *p)
{
  struct score_got_entry *entry = (struct score_got_entry *)*entryp;
  htab_t got_entries = *(htab_t *)p;

  if (entry->abfd != NULL && entry->symndx == -1)
    {
      struct score_elf_link_hash_entry *h = entry->d.h;

      while (h->root.root.type == bfd_link_hash_indirect
	     || h->root.root.type == bfd_link_hash_warning)
	h = (struct score_elf_link_hash_entry *) h->root.root.u.i.link;

      if (entry->d.h == h)
	return 1;

      entry->d.h = h;

      /* If we can't find this entry with the new bfd hash, re-insert
	 it, and get the traversal restarted.  */
      if (! htab_find (got_entries, entry))
	{
	  htab_clear_slot (got_entries, entryp);
	  entryp = htab_find_slot (got_entries, entry, INSERT);
	  if (! *entryp)
	    *entryp = entry;
	  /* Abort the traversal, since the whole table may have
	     moved, and leave it up to the parent to restart the
	     process.  */
	  *(htab_t *)p = NULL;
	  return 0;
	}
      /* We might want to decrement the global_gotno count, but it's
	 either too early or too late for that at this point.  */
    }

  return 1;
}