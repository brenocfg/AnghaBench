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
struct score_elf_link_hash_entry {void* forced_local; void* no_fn_stub; void* readonly_reloc; scalar_t__ possibly_dynamic_relocs; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct score_elf_link_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
score_elf_link_hash_newfunc (struct bfd_hash_entry *entry,
			     struct bfd_hash_table *table,
			     const char *string)
{
  struct score_elf_link_hash_entry *ret = (struct score_elf_link_hash_entry *)entry;

  /* Allocate the structure if it has not already been allocated by a subclass.  */
  if (ret == NULL)
    ret = bfd_hash_allocate (table, sizeof (struct score_elf_link_hash_entry));
  if (ret == NULL)
    return (struct bfd_hash_entry *)ret;

  /* Call the allocation method of the superclass.  */
  ret = ((struct score_elf_link_hash_entry *)
         _bfd_elf_link_hash_newfunc ((struct bfd_hash_entry *)ret, table, string));

  if (ret != NULL)
    {
      ret->possibly_dynamic_relocs = 0;
      ret->readonly_reloc = FALSE;
      ret->no_fn_stub = FALSE;
      ret->forced_local = FALSE;
    }

  return (struct bfd_hash_entry *)ret;
}