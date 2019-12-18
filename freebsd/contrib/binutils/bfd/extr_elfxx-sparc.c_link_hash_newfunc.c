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
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
struct _bfd_sparc_elf_link_hash_entry {int /*<<< orphan*/  tls_type; int /*<<< orphan*/ * dyn_relocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOT_UNKNOWN ; 
 struct bfd_hash_entry* _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
link_hash_newfunc (struct bfd_hash_entry *entry,
		   struct bfd_hash_table *table, const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table,
				 sizeof (struct _bfd_sparc_elf_link_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = _bfd_elf_link_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      struct _bfd_sparc_elf_link_hash_entry *eh;

      eh = (struct _bfd_sparc_elf_link_hash_entry *) entry;
      eh->dyn_relocs = NULL;
      eh->tls_type = GOT_UNKNOWN;
    }

  return entry;
}