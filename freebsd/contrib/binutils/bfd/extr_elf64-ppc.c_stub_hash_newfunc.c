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
struct ppc_stub_hash_entry {int /*<<< orphan*/ * id_sec; int /*<<< orphan*/ * h; int /*<<< orphan*/ * target_section; scalar_t__ target_value; scalar_t__ stub_offset; int /*<<< orphan*/ * stub_sec; int /*<<< orphan*/  stub_type; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 struct bfd_hash_entry* bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 int /*<<< orphan*/  ppc_stub_none ; 

__attribute__((used)) static struct bfd_hash_entry *
stub_hash_newfunc (struct bfd_hash_entry *entry,
		   struct bfd_hash_table *table,
		   const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table, sizeof (struct ppc_stub_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = bfd_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      struct ppc_stub_hash_entry *eh;

      /* Initialize the local fields.  */
      eh = (struct ppc_stub_hash_entry *) entry;
      eh->stub_type = ppc_stub_none;
      eh->stub_sec = NULL;
      eh->stub_offset = 0;
      eh->target_value = 0;
      eh->target_section = NULL;
      eh->h = NULL;
      eh->id_sec = NULL;
    }

  return entry;
}