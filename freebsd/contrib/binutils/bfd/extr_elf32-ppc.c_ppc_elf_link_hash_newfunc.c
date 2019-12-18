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
struct ppc_elf_link_hash_entry {int dummy; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ tls_mask; int /*<<< orphan*/ * dyn_relocs; int /*<<< orphan*/ * linker_section_pointer; } ;

/* Variables and functions */
 struct bfd_hash_entry* _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 TYPE_1__* ppc_elf_hash_entry (struct bfd_hash_entry*) ; 

__attribute__((used)) static struct bfd_hash_entry *
ppc_elf_link_hash_newfunc (struct bfd_hash_entry *entry,
			   struct bfd_hash_table *table,
			   const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table,
				 sizeof (struct ppc_elf_link_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = _bfd_elf_link_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      ppc_elf_hash_entry (entry)->linker_section_pointer = NULL;
      ppc_elf_hash_entry (entry)->dyn_relocs = NULL;
      ppc_elf_hash_entry (entry)->tls_mask = 0;
    }

  return entry;
}