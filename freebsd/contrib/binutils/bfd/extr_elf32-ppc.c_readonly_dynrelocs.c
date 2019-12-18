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
struct ppc_elf_dyn_relocs {TYPE_3__* sec; struct ppc_elf_dyn_relocs* next; } ;
struct TYPE_7__ {scalar_t__ link; } ;
struct TYPE_8__ {TYPE_1__ i; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
struct bfd_link_info {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_11__ {int flags; } ;
typedef  TYPE_5__ asection ;
struct TYPE_12__ {struct ppc_elf_dyn_relocs* dyn_relocs; } ;
struct TYPE_9__ {TYPE_5__* output_section; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_TEXTREL ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_6__* ppc_elf_hash_entry (struct elf_link_hash_entry*) ; 

__attribute__((used)) static bfd_boolean
readonly_dynrelocs (struct elf_link_hash_entry *h, void *info)
{
  struct ppc_elf_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  for (p = ppc_elf_hash_entry (h)->dyn_relocs; p != NULL; p = p->next)
    {
      asection *s = p->sec->output_section;

      if (s != NULL
	  && ((s->flags & (SEC_READONLY | SEC_ALLOC))
	      == (SEC_READONLY | SEC_ALLOC)))
	{
	  ((struct bfd_link_info *) info)->flags |= DF_TEXTREL;

	  /* Not an error, just cut short the traversal.  */
	  return FALSE;
	}
    }
  return TRUE;
}