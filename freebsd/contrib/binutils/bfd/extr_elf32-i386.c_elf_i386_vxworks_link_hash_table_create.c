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
struct elf_i386_link_hash_table {int is_vxworks; int plt0_pad_byte; } ;
struct bfd_link_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct bfd_link_hash_table* elf_i386_link_hash_table_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf_i386_vxworks_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;
  struct elf_i386_link_hash_table *htab;

  ret = elf_i386_link_hash_table_create (abfd);
  if (ret)
    {
      htab = (struct elf_i386_link_hash_table *) ret;
      htab->is_vxworks = 1;
      htab->plt0_pad_byte = 0x90;
    }

  return ret;
}