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
struct bfd_hash_entry {int dummy; } ;
struct cref_hash_entry {struct bfd_hash_entry root; int /*<<< orphan*/ * refs; int /*<<< orphan*/ * demangled; } ;
struct bfd_hash_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 scalar_t__ bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 int /*<<< orphan*/  cref_symcount ; 

__attribute__((used)) static struct bfd_hash_entry *
cref_hash_newfunc (struct bfd_hash_entry *entry,
		   struct bfd_hash_table *table,
		   const char *string)
{
  struct cref_hash_entry *ret = (struct cref_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == NULL)
    ret = ((struct cref_hash_entry *)
	   bfd_hash_allocate (table, sizeof (struct cref_hash_entry)));
  if (ret == NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  ret = ((struct cref_hash_entry *)
	 bfd_hash_newfunc ((struct bfd_hash_entry *) ret, table, string));
  if (ret != NULL)
    {
      /* Set local fields.  */
      ret->demangled = NULL;
      ret->refs = NULL;

      /* Keep a count of the number of entries created in the hash
	 table.  */
      ++cref_symcount;
    }

  return &ret->root;
}