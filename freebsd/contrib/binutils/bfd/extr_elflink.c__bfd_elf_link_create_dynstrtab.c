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
struct elf_link_hash_table {int /*<<< orphan*/ * dynstr; int /*<<< orphan*/ * dynobj; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _bfd_elf_strtab_init () ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
_bfd_elf_link_create_dynstrtab (bfd *abfd, struct bfd_link_info *info)
{
  struct elf_link_hash_table *hash_table;

  hash_table = elf_hash_table (info);
  if (hash_table->dynobj == NULL)
    hash_table->dynobj = abfd;

  if (hash_table->dynstr == NULL)
    {
      hash_table->dynstr = _bfd_elf_strtab_init ();
      if (hash_table->dynstr == NULL)
	return FALSE;
    }
  return TRUE;
}