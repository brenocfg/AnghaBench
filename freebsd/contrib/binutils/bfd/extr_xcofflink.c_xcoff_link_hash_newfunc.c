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
struct TYPE_2__ {int toc_indx; } ;
struct xcoff_link_hash_entry {int indx; int ldindx; int /*<<< orphan*/  smclas; scalar_t__ flags; int /*<<< orphan*/ * ldsym; int /*<<< orphan*/ * descriptor; TYPE_1__ u; int /*<<< orphan*/ * toc_section; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMC_UA ; 
 scalar_t__ _bfd_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct xcoff_link_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
xcoff_link_hash_newfunc (struct bfd_hash_entry *entry,
			 struct bfd_hash_table *table,
			 const char *string)
{
  struct xcoff_link_hash_entry *ret = (struct xcoff_link_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == NULL)
    ret = bfd_hash_allocate (table, sizeof (* ret));
  if (ret == NULL)
    return NULL;

  /* Call the allocation method of the superclass.  */
  ret = ((struct xcoff_link_hash_entry *)
	 _bfd_link_hash_newfunc ((struct bfd_hash_entry *) ret,
				 table, string));
  if (ret != NULL)
    {
      /* Set local fields.  */
      ret->indx = -1;
      ret->toc_section = NULL;
      ret->u.toc_indx = -1;
      ret->descriptor = NULL;
      ret->ldsym = NULL;
      ret->ldindx = -1;
      ret->flags = 0;
      ret->smclas = XMC_UA;
    }

  return (struct bfd_hash_entry *) ret;
}