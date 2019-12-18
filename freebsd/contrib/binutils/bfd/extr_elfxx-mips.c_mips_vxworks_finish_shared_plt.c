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
struct mips_elf_link_hash_table {TYPE_1__* splt; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {scalar_t__ contents; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/ * mips_vxworks_shared_plt0_entry ; 

__attribute__((used)) static void
mips_vxworks_finish_shared_plt (bfd *output_bfd, struct bfd_link_info *info)
{
  unsigned int i;
  struct mips_elf_link_hash_table *htab;

  htab = mips_elf_hash_table (info);

  /* We just need to copy the entry byte-by-byte.  */
  for (i = 0; i < ARRAY_SIZE (mips_vxworks_shared_plt0_entry); i++)
    bfd_put_32 (output_bfd, mips_vxworks_shared_plt0_entry[i],
		htab->splt->contents + i * 4);
}