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
struct ppc_link_hash_table {int /*<<< orphan*/  elf; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  elf_link_hash_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfd_link_info*) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  undo_symbol_twiddle ; 

void
ppc64_elf_restore_symbols (struct bfd_link_info *info)
{
  struct ppc_link_hash_table *htab = ppc_hash_table (info);
  elf_link_hash_traverse (&htab->elf, undo_symbol_twiddle, info);
}