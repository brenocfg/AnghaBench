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
struct score_got_info {int /*<<< orphan*/  got_entries; } ;
struct TYPE_3__ {struct score_elf_link_hash_entry* h; } ;
struct score_got_entry {int symndx; int gotidx; TYPE_1__ d; int /*<<< orphan*/ * abfd; } ;
struct score_elf_link_hash_entry {int dummy; } ;
struct TYPE_4__ {int offset; } ;
struct elf_link_hash_entry {int dynindx; TYPE_2__ got; int /*<<< orphan*/  other; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INSERT ; 
 int MINUS_ONE ; 
#define  STV_HIDDEN 129 
#define  STV_INTERNAL 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_score_elf_hide_symbol (struct bfd_link_info*,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 
 struct score_got_entry* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ ,struct score_got_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct score_got_entry*,struct score_got_entry*,int) ; 

__attribute__((used)) static bfd_boolean
score_elf_record_global_got_symbol (struct elf_link_hash_entry *h,
	 			    bfd *abfd,
                                    struct bfd_link_info *info,
				    struct score_got_info *g)
{
  struct score_got_entry entry, **loc;

  /* A global symbol in the GOT must also be in the dynamic symbol table.  */
  if (h->dynindx == -1)
    {
      switch (ELF_ST_VISIBILITY (h->other))
	{
	case STV_INTERNAL:
	case STV_HIDDEN:
	  _bfd_score_elf_hide_symbol (info, h, TRUE);
	  break;
	}
      if (!bfd_elf_link_record_dynamic_symbol (info, h))
	return FALSE;
    }

  entry.abfd = abfd;
  entry.symndx = -1;
  entry.d.h = (struct score_elf_link_hash_entry *)h;

  loc = (struct score_got_entry **)htab_find_slot (g->got_entries, &entry, INSERT);

  /* If we've already marked this entry as needing GOT space, we don't
     need to do it again.  */
  if (*loc)
    return TRUE;

  *loc = bfd_alloc (abfd, sizeof entry);
  if (! *loc)
    return FALSE;

  entry.gotidx = -1;

  memcpy (*loc, &entry, sizeof (entry));

  if (h->got.offset != MINUS_ONE)
    return TRUE;

  /* By setting this to a value other than -1, we are indicating that
     there needs to be a GOT entry for H.  Avoid using zero, as the
     generic ELF copy_indirect_symbol tests for <= 0.  */
  h->got.offset = 1;

  return TRUE;
}