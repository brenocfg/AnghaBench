#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct plt_entry {int addend; int /*<<< orphan*/ * sec; struct plt_entry* next; } ;
struct TYPE_2__ {struct plt_entry* plist; } ;
struct elf_link_hash_entry {TYPE_1__ plt; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */

__attribute__((used)) static struct plt_entry *
find_plt_ent (struct elf_link_hash_entry *h, asection *sec, bfd_vma addend)
{
  struct plt_entry *ent;

  if (addend < 32768)
    sec = NULL;
  for (ent = h->plt.plist; ent != NULL; ent = ent->next)
    if (ent->sec == sec && ent->addend == addend)
      break;
  return ent;
}