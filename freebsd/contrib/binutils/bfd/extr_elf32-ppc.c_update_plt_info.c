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
struct plt_entry {int addend; TYPE_2__ plt; int /*<<< orphan*/ * sec; struct plt_entry* next; } ;
struct TYPE_3__ {struct plt_entry* plist; } ;
struct elf_link_hash_entry {TYPE_1__ plt; } ;
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct plt_entry* bfd_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfd_boolean
update_plt_info (bfd *abfd, struct elf_link_hash_entry *h,
		 asection *sec, bfd_vma addend)
{
  struct plt_entry *ent;

  if (addend < 32768)
    sec = NULL;
  for (ent = h->plt.plist; ent != NULL; ent = ent->next)
    if (ent->sec == sec && ent->addend == addend)
      break;
  if (ent == NULL)
    {
      bfd_size_type amt = sizeof (*ent);
      ent = bfd_alloc (abfd, amt);
      if (ent == NULL)
	return FALSE;
      ent->next = h->plt.plist;
      ent->sec = sec;
      ent->addend = addend;
      ent->plt.refcount = 0;
      h->plt.plist = ent;
    }
  ent->plt.refcount += 1;
  return TRUE;
}