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
struct score_elf_link_hash_entry {void* no_fn_stub; void* readonly_reloc; scalar_t__ possibly_dynamic_relocs; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct elf_link_hash_entry {TYPE_1__ root; } ;
struct bfd_link_info {int dummy; } ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_copy_indirect (struct bfd_link_info*,struct elf_link_hash_entry*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 

__attribute__((used)) static void
_bfd_score_elf_copy_indirect_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *dir,
				     struct elf_link_hash_entry *ind)
{
  struct score_elf_link_hash_entry *dirscore, *indscore;

  _bfd_elf_link_hash_copy_indirect (info, dir, ind);

  if (ind->root.type != bfd_link_hash_indirect)
    return;

  dirscore = (struct score_elf_link_hash_entry *) dir;
  indscore = (struct score_elf_link_hash_entry *) ind;
  dirscore->possibly_dynamic_relocs += indscore->possibly_dynamic_relocs;

  if (indscore->readonly_reloc)
    dirscore->readonly_reloc = TRUE;

  if (indscore->no_fn_stub)
    dirscore->no_fn_stub = TRUE;
}