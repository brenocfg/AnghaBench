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
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
struct TYPE_2__ {int ifd; } ;
struct alpha_elf_link_hash_entry {int /*<<< orphan*/ * reloc_entries; int /*<<< orphan*/ * got_entries; scalar_t__ flags; TYPE_1__ esym; } ;
typedef  int /*<<< orphan*/  EXTR ;

/* Variables and functions */
 scalar_t__ _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 scalar_t__ bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
elf64_alpha_link_hash_newfunc (struct bfd_hash_entry *entry,
			       struct bfd_hash_table *table,
			       const char *string)
{
  struct alpha_elf_link_hash_entry *ret =
    (struct alpha_elf_link_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == (struct alpha_elf_link_hash_entry *) NULL)
    ret = ((struct alpha_elf_link_hash_entry *)
	   bfd_hash_allocate (table,
			      sizeof (struct alpha_elf_link_hash_entry)));
  if (ret == (struct alpha_elf_link_hash_entry *) NULL)
    return (struct bfd_hash_entry *) ret;

  /* Call the allocation method of the superclass.  */
  ret = ((struct alpha_elf_link_hash_entry *)
	 _bfd_elf_link_hash_newfunc ((struct bfd_hash_entry *) ret,
				     table, string));
  if (ret != (struct alpha_elf_link_hash_entry *) NULL)
    {
      /* Set local fields.  */
      memset (&ret->esym, 0, sizeof (EXTR));
      /* We use -2 as a marker to indicate that the information has
	 not been set.  -1 means there is no associated ifd.  */
      ret->esym.ifd = -2;
      ret->flags = 0;
      ret->got_entries = NULL;
      ret->reloc_entries = NULL;
    }

  return (struct bfd_hash_entry *) ret;
}