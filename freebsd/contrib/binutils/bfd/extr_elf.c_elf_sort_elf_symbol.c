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
struct TYPE_2__ {int st_shndx; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */

__attribute__((used)) static int
elf_sort_elf_symbol (const void *arg1, const void *arg2)
{
  const Elf_Internal_Sym *s1 = *(const Elf_Internal_Sym **) arg1;
  const Elf_Internal_Sym *s2 = *(const Elf_Internal_Sym **) arg2;

  return s1->st_shndx - s2->st_shndx;
}