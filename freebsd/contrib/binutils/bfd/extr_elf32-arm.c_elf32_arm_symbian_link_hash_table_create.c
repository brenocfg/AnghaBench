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
struct TYPE_2__ {int is_relocatable_executable; } ;
struct elf32_arm_link_hash_table {int plt_entry_size; int symbian_p; int use_blx; TYPE_1__ root; scalar_t__ plt_header_size; } ;
struct bfd_link_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int NUM_ELEM (int /*<<< orphan*/ ) ; 
 struct bfd_link_hash_table* elf32_arm_link_hash_table_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf32_arm_symbian_plt_entry ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf32_arm_symbian_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;

  ret = elf32_arm_link_hash_table_create (abfd);
  if (ret)
    {
      struct elf32_arm_link_hash_table *htab
	= (struct elf32_arm_link_hash_table *)ret;
      /* There is no PLT header for Symbian OS.  */
      htab->plt_header_size = 0;
      /* The PLT entries are each three instructions.  */
      htab->plt_entry_size = 4 * NUM_ELEM (elf32_arm_symbian_plt_entry);
      htab->symbian_p = 1;
      /* Symbian uses armv5t or above, so use_blx is always true.  */
      htab->use_blx = 1;
      htab->root.is_relocatable_executable = 1;
    }
  return ret;
}