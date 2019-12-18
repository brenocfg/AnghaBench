#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int /*<<< orphan*/  r_info; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Sym ;
typedef  TYPE_1__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_390_GNU_VTENTRY 129 
#define  R_390_GNU_VTINHERIT 128 
 int /*<<< orphan*/ * _bfd_elf_gc_mark_hook (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_1__*,struct elf_link_hash_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static asection *
elf_s390_gc_mark_hook (asection *sec,
		       struct bfd_link_info *info,
		       Elf_Internal_Rela *rel,
		       struct elf_link_hash_entry *h,
		       Elf_Internal_Sym *sym)
{
  if (h != NULL)
    switch (ELF64_R_TYPE (rel->r_info))
      {
      case R_390_GNU_VTINHERIT:
      case R_390_GNU_VTENTRY:
	return NULL;
      }

  return _bfd_elf_gc_mark_hook (sec, info, rel, h, sym);
}