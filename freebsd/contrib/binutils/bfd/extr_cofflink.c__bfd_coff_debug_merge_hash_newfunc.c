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
struct coff_debug_merge_hash_entry {int /*<<< orphan*/ * types; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 scalar_t__ bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 

struct bfd_hash_entry *
_bfd_coff_debug_merge_hash_newfunc (struct bfd_hash_entry *entry,
				    struct bfd_hash_table *table,
				    const char *string)
{
  struct coff_debug_merge_hash_entry *ret =
    (struct coff_debug_merge_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == (struct coff_debug_merge_hash_entry *) NULL)
    ret = ((struct coff_debug_merge_hash_entry *)
	   bfd_hash_allocate (table,
			      sizeof (struct coff_debug_merge_hash_entry)));
  if (ret == (struct coff_debug_merge_hash_entry *) NULL)
    return (struct bfd_hash_entry *) ret;

  /* Call the allocation method of the superclass.  */
  ret = ((struct coff_debug_merge_hash_entry *)
	 bfd_hash_newfunc ((struct bfd_hash_entry *) ret, table, string));
  if (ret != (struct coff_debug_merge_hash_entry *) NULL)
    {
      /* Set local fields.  */
      ret->types = NULL;
    }

  return (struct bfd_hash_entry *) ret;
}