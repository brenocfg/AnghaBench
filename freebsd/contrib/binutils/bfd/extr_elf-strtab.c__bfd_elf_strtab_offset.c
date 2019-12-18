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
struct TYPE_2__ {size_t index; } ;
struct elf_strtab_hash_entry {scalar_t__ refcount; TYPE_1__ u; } ;
struct elf_strtab_hash {size_t size; int sec_size; struct elf_strtab_hash_entry** array; } ;
typedef  size_t bfd_size_type ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 

bfd_size_type
_bfd_elf_strtab_offset (struct elf_strtab_hash *tab, bfd_size_type idx)
{
  struct elf_strtab_hash_entry *entry;

  if (idx == 0)
    return 0;
  BFD_ASSERT (idx < tab->size);
  BFD_ASSERT (tab->sec_size);
  entry = tab->array[idx];
  BFD_ASSERT (entry->refcount > 0);
  entry->refcount--;
  return tab->array[idx]->u.index;
}