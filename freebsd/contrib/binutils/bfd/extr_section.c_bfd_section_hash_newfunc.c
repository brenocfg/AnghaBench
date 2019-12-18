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
struct section_hash_entry {int /*<<< orphan*/  section; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 struct bfd_hash_entry* bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct bfd_hash_entry *
bfd_section_hash_newfunc (struct bfd_hash_entry *entry,
			  struct bfd_hash_table *table,
			  const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = (struct bfd_hash_entry *)
	bfd_hash_allocate (table, sizeof (struct section_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = bfd_hash_newfunc (entry, table, string);
  if (entry != NULL)
    memset (&((struct section_hash_entry *) entry)->section, 0,
	    sizeof (asection));

  return entry;
}