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
struct elf_strtab_hash {size_t size; TYPE_1__** array; } ;
typedef  size_t bfd_size_type ;
struct TYPE_2__ {scalar_t__ refcount; } ;

/* Variables and functions */

void
_bfd_elf_strtab_clear_all_refs (struct elf_strtab_hash *tab)
{
  bfd_size_type idx;

  for (idx = 1; idx < tab->size; ++idx)
    tab->array[idx]->refcount = 0;
}