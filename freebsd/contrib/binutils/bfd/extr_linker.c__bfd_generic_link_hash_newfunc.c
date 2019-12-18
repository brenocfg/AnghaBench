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
struct generic_link_hash_entry {int /*<<< orphan*/ * sym; int /*<<< orphan*/  written; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct bfd_hash_entry* _bfd_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 

struct bfd_hash_entry *
_bfd_generic_link_hash_newfunc (struct bfd_hash_entry *entry,
				struct bfd_hash_table *table,
				const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry =
	bfd_hash_allocate (table, sizeof (struct generic_link_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = _bfd_link_hash_newfunc (entry, table, string);
  if (entry)
    {
      struct generic_link_hash_entry *ret;

      /* Set local fields.  */
      ret = (struct generic_link_hash_entry *) entry;
      ret->written = FALSE;
      ret->sym = NULL;
    }

  return entry;
}