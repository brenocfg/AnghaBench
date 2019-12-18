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
struct ppc_branch_hash_entry {scalar_t__ iter; scalar_t__ offset; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 struct bfd_hash_entry* bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 

__attribute__((used)) static struct bfd_hash_entry *
branch_hash_newfunc (struct bfd_hash_entry *entry,
		     struct bfd_hash_table *table,
		     const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table, sizeof (struct ppc_branch_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = bfd_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      struct ppc_branch_hash_entry *eh;

      /* Initialize the local fields.  */
      eh = (struct ppc_branch_hash_entry *) entry;
      eh->offset = 0;
      eh->iter = 0;
    }

  return entry;
}