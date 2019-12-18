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
struct mips_elf_link_hash_table {int is_vxworks; } ;
struct bfd_link_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct bfd_link_hash_table* _bfd_mips_elf_link_hash_table_create (int /*<<< orphan*/ *) ; 

struct bfd_link_hash_table *
_bfd_mips_vxworks_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;

  ret = _bfd_mips_elf_link_hash_table_create (abfd);
  if (ret)
    {
      struct mips_elf_link_hash_table *htab;

      htab = (struct mips_elf_link_hash_table *) ret;
      htab->is_vxworks = 1;
    }
  return ret;
}