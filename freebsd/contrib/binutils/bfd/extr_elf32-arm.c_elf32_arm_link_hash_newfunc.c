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
struct elf32_arm_link_hash_entry {int plt_got_offset; int /*<<< orphan*/ * export_glue; scalar_t__ plt_thumb_refcount; int /*<<< orphan*/  tls_type; int /*<<< orphan*/ * relocs_copied; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOT_UNKNOWN ; 
 scalar_t__ _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct elf32_arm_link_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
elf32_arm_link_hash_newfunc (struct bfd_hash_entry * entry,
                             struct bfd_hash_table * table,
                             const char * string)
{
  struct elf32_arm_link_hash_entry * ret =
    (struct elf32_arm_link_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == (struct elf32_arm_link_hash_entry *) NULL)
    ret = bfd_hash_allocate (table, sizeof (struct elf32_arm_link_hash_entry));
  if (ret == NULL)
    return (struct bfd_hash_entry *) ret;

  /* Call the allocation method of the superclass.  */
  ret = ((struct elf32_arm_link_hash_entry *)
	 _bfd_elf_link_hash_newfunc ((struct bfd_hash_entry *) ret,
				     table, string));
  if (ret != NULL)
    {
      ret->relocs_copied = NULL;
      ret->tls_type = GOT_UNKNOWN;
      ret->plt_thumb_refcount = 0;
      ret->plt_got_offset = -1;
      ret->export_glue = NULL;
    }

  return (struct bfd_hash_entry *) ret;
}