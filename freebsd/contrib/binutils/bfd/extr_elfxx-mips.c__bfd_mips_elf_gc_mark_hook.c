#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;
struct TYPE_10__ {int /*<<< orphan*/  r_info; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;
typedef  TYPE_2__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF_R_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  R_MIPS_GNU_VTENTRY 129 
#define  R_MIPS_GNU_VTINHERIT 128 
 TYPE_1__* _bfd_elf_gc_mark_hook (TYPE_1__*,struct bfd_link_info*,TYPE_2__*,struct elf_link_hash_entry*,int /*<<< orphan*/ *) ; 

asection *
_bfd_mips_elf_gc_mark_hook (asection *sec,
			    struct bfd_link_info *info,
			    Elf_Internal_Rela *rel,
			    struct elf_link_hash_entry *h,
			    Elf_Internal_Sym *sym)
{
  /* ??? Do mips16 stub sections need to be handled special?  */

  if (h != NULL)
    switch (ELF_R_TYPE (sec->owner, rel->r_info))
      {
      case R_MIPS_GNU_VTINHERIT:
      case R_MIPS_GNU_VTENTRY:
	return NULL;
      }

  return _bfd_elf_gc_mark_hook (sec, info, rel, h, sym);
}