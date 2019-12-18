#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct score_got_info {scalar_t__ global_gotno; scalar_t__ assigned_gotno; int /*<<< orphan*/  local_gotno; int /*<<< orphan*/ * global_gotsym; int /*<<< orphan*/  got_entries; struct score_got_info* next; } ;
struct TYPE_8__ {struct score_elf_link_hash_entry* h; } ;
struct score_got_entry {int symndx; TYPE_2__ d; int /*<<< orphan*/ * abfd; } ;
struct TYPE_9__ {int offset; } ;
struct TYPE_12__ {TYPE_3__ got; } ;
struct score_elf_link_hash_entry {TYPE_6__ root; scalar_t__ forced_local; } ;
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_11__ {int /*<<< orphan*/ * dynobj; } ;
struct TYPE_7__ {struct score_got_info* got_info; } ;
struct TYPE_10__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_hide_symbol (struct bfd_link_info*,TYPE_6__*,scalar_t__) ; 
 TYPE_5__* elf_hash_table (struct bfd_link_info*) ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct score_got_entry*) ; 
 int /*<<< orphan*/ * score_elf_got_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* score_elf_section_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_bfd_score_elf_hide_symbol (struct bfd_link_info *info,
			    struct elf_link_hash_entry *entry,
			    bfd_boolean force_local)
{
  bfd *dynobj;
  asection *got;
  struct score_got_info *g;
  struct score_elf_link_hash_entry *h;

  h = (struct score_elf_link_hash_entry *) entry;
  if (h->forced_local)
    return;
  h->forced_local = TRUE;

  dynobj = elf_hash_table (info)->dynobj;
  if (dynobj != NULL && force_local)
    {
      got = score_elf_got_section (dynobj, FALSE);
      if (got == NULL)
	return;
      g = score_elf_section_data (got)->u.got_info;

      if (g->next)
	{
	  struct score_got_entry e;
	  struct score_got_info *gg = g;

	  /* Since we're turning what used to be a global symbol into a
	     local one, bump up the number of local entries of each GOT
	     that had an entry for it.  This will automatically decrease
	     the number of global entries, since global_gotno is actually
	     the upper limit of global entries.  */
	  e.abfd = dynobj;
	  e.symndx = -1;
	  e.d.h = h;

	  for (g = g->next; g != gg; g = g->next)
	    if (htab_find (g->got_entries, &e))
	      {
		BFD_ASSERT (g->global_gotno > 0);
		g->local_gotno++;
		g->global_gotno--;
	      }

	  /* If this was a global symbol forced into the primary GOT, we
	     no longer need an entry for it.  We can't release the entry
	     at this point, but we must at least stop counting it as one
	     of the symbols that required a forced got entry.  */
	  if (h->root.got.offset == 2)
	    {
	      BFD_ASSERT (gg->assigned_gotno > 0);
	      gg->assigned_gotno--;
	    }
	}
      else if (g->global_gotno == 0 && g->global_gotsym == NULL)
	/* If we haven't got through GOT allocation yet, just bump up the
	      number of local entries, as this symbol won't be counted as
	      global.  */
	g->local_gotno++;
      else if (h->root.got.offset == 1)
	{
	  /* If we're past non-multi-GOT allocation and this symbol had
	          been marked for a global got entry, give it a local entry
		  instead.  */
	  BFD_ASSERT (g->global_gotno > 0);
	  g->local_gotno++;
	  g->global_gotno--;
	}
    }

  _bfd_elf_link_hash_hide_symbol (info, &h->root, force_local);
}