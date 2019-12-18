#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Internal_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_elf32_swap_reloc_in (int /*<<< orphan*/ ,void const*,TYPE_1__*) ; 
 int /*<<< orphan*/  reldyn_sorting_bfd ; 

__attribute__((used)) static int
score_elf_sort_dynamic_relocs (const void *arg1, const void *arg2)
{
  Elf_Internal_Rela int_reloc1;
  Elf_Internal_Rela int_reloc2;

  bfd_elf32_swap_reloc_in (reldyn_sorting_bfd, arg1, &int_reloc1);
  bfd_elf32_swap_reloc_in (reldyn_sorting_bfd, arg2, &int_reloc2);

  return (ELF32_R_SYM (int_reloc1.r_info) - ELF32_R_SYM (int_reloc2.r_info));
}