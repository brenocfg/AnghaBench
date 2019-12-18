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
struct mips_elf_link_hash_entry {scalar_t__ tls_type; void* no_fn_stub; void* readonly_reloc; scalar_t__ possibly_dynamic_relocs; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct elf_link_hash_entry {TYPE_1__ root; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_copy_indirect (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 

void
_bfd_mips_elf_copy_indirect_symbol (struct bfd_link_info *info,
				    struct elf_link_hash_entry *dir,
				    struct elf_link_hash_entry *ind)
{
  struct mips_elf_link_hash_entry *dirmips, *indmips;

  _bfd_elf_link_hash_copy_indirect (info, dir, ind);

  if (ind->root.type != bfd_link_hash_indirect)
    return;

  dirmips = (struct mips_elf_link_hash_entry *) dir;
  indmips = (struct mips_elf_link_hash_entry *) ind;
  dirmips->possibly_dynamic_relocs += indmips->possibly_dynamic_relocs;
  if (indmips->readonly_reloc)
    dirmips->readonly_reloc = TRUE;
  if (indmips->no_fn_stub)
    dirmips->no_fn_stub = TRUE;

  if (dirmips->tls_type == 0)
    dirmips->tls_type = indmips->tls_type;
}