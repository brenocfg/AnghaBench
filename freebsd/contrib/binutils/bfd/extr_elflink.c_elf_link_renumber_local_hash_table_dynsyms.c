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
struct TYPE_4__ {scalar_t__ link; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  forced_local; TYPE_3__ root; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_warning ; 

__attribute__((used)) static bfd_boolean
elf_link_renumber_local_hash_table_dynsyms (struct elf_link_hash_entry *h,
					    void *data)
{
  size_t *count = data;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if (!h->forced_local)
    return TRUE;

  if (h->dynindx != -1)
    h->dynindx = ++(*count);

  return TRUE;
}