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
struct TYPE_2__ {int /*<<< orphan*/ * suffix; } ;
struct sec_merge_hash_entry {int /*<<< orphan*/ * next; int /*<<< orphan*/ * secinfo; scalar_t__ alignment; TYPE_1__ u; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 struct bfd_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 struct bfd_hash_entry* bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 

__attribute__((used)) static struct bfd_hash_entry *
sec_merge_hash_newfunc (struct bfd_hash_entry *entry,
			struct bfd_hash_table *table, const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    entry = bfd_hash_allocate (table, sizeof (struct sec_merge_hash_entry));
  if (entry == NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  entry = bfd_hash_newfunc (entry, table, string);

  if (entry != NULL)
    {
      /* Initialize the local fields.  */
      struct sec_merge_hash_entry *ret = (struct sec_merge_hash_entry *) entry;

      ret->u.suffix = NULL;
      ret->alignment = 0;
      ret->secinfo = NULL;
      ret->next = NULL;
    }

  return entry;
}