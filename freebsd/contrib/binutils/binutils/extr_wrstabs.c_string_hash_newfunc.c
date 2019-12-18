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
struct string_hash_entry {int index; scalar_t__ size; int /*<<< orphan*/ * next; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 scalar_t__ bfd_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 

__attribute__((used)) static struct bfd_hash_entry *
string_hash_newfunc (struct bfd_hash_entry *entry,
		     struct bfd_hash_table *table, const char *string)
{
  struct string_hash_entry *ret = (struct string_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == (struct string_hash_entry *) NULL)
    ret = ((struct string_hash_entry *)
	   bfd_hash_allocate (table, sizeof (struct string_hash_entry)));
  if (ret == (struct string_hash_entry *) NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  ret = ((struct string_hash_entry *)
	 bfd_hash_newfunc ((struct bfd_hash_entry *) ret, table, string));

  if (ret)
    {
      /* Initialize the local fields.  */
      ret->next = NULL;
      ret->index = -1;
      ret->size = 0;
    }

  return (struct bfd_hash_entry *) ret;
}