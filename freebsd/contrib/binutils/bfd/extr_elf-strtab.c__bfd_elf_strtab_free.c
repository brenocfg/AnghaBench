#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf_strtab_hash {struct elf_strtab_hash* array; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct elf_strtab_hash*) ; 

void
_bfd_elf_strtab_free (struct elf_strtab_hash *tab)
{
  bfd_hash_table_free (&tab->table);
  free (tab->array);
  free (tab);
}