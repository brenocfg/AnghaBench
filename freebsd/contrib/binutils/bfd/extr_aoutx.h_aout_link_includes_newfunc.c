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
struct aout_link_includes_entry {int /*<<< orphan*/ * totals; } ;

/* Variables and functions */
 struct aout_link_includes_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 scalar_t__ bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 

__attribute__((used)) static struct bfd_hash_entry *
aout_link_includes_newfunc (struct bfd_hash_entry *entry,
			    struct bfd_hash_table *table,
			    const char *string)
{
  struct aout_link_includes_entry *ret =
    (struct aout_link_includes_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == NULL)
    ret = bfd_hash_allocate (table, sizeof (* ret));
  if (ret == NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  ret = ((struct aout_link_includes_entry *)
	 bfd_hash_newfunc ((struct bfd_hash_entry *) ret, table, string));
  if (ret)
    {
      /* Set local fields.  */
      ret->totals = NULL;
    }

  return (struct bfd_hash_entry *) ret;
}