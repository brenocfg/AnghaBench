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
struct ppc_elf_link_hash_table {int is_vxworks; int /*<<< orphan*/  plt_initial_entry_size; void* plt_slot_size; void* plt_entry_size; int /*<<< orphan*/  plt_type; } ;
struct bfd_link_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  PLT_VXWORKS ; 
 void* VXWORKS_PLT_ENTRY_SIZE ; 
 int /*<<< orphan*/  VXWORKS_PLT_INITIAL_ENTRY_SIZE ; 
 struct bfd_link_hash_table* ppc_elf_link_hash_table_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bfd_link_hash_table *
ppc_elf_vxworks_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;

  ret = ppc_elf_link_hash_table_create (abfd);
  if (ret)
    {
      struct ppc_elf_link_hash_table *htab
        = (struct ppc_elf_link_hash_table *)ret;
      htab->is_vxworks = 1;
      htab->plt_type = PLT_VXWORKS;
      htab->plt_entry_size = VXWORKS_PLT_ENTRY_SIZE;
      htab->plt_slot_size = VXWORKS_PLT_ENTRY_SIZE;
      htab->plt_initial_entry_size = VXWORKS_PLT_INITIAL_ENTRY_SIZE;
    }
  return ret;
}