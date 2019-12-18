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
struct ecoff_link_hash_entry {int indx; int /*<<< orphan*/  esym; scalar_t__ small; scalar_t__ written; int /*<<< orphan*/ * abfd; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ _bfd_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
ecoff_link_hash_newfunc (struct bfd_hash_entry *entry,
			 struct bfd_hash_table *table,
			 const char *string)
{
  struct ecoff_link_hash_entry *ret = (struct ecoff_link_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == NULL)
    ret = ((struct ecoff_link_hash_entry *)
	   bfd_hash_allocate (table, sizeof (struct ecoff_link_hash_entry)));
  if (ret == NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  ret = ((struct ecoff_link_hash_entry *)
	 _bfd_link_hash_newfunc ((struct bfd_hash_entry *) ret,
				 table, string));

  if (ret)
    {
      /* Set local fields.  */
      ret->indx = -1;
      ret->abfd = NULL;
      ret->written = 0;
      ret->small = 0;
    }
  memset ((void *) &ret->esym, 0, sizeof ret->esym);

  return (struct bfd_hash_entry *) ret;
}