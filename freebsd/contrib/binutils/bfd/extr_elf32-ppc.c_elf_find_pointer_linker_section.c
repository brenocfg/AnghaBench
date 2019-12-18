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
typedef  int /*<<< orphan*/  elf_linker_section_t ;
struct TYPE_4__ {scalar_t__ addend; int /*<<< orphan*/ * lsect; struct TYPE_4__* next; } ;
typedef  TYPE_1__ elf_linker_section_pointers_t ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */

__attribute__((used)) static elf_linker_section_pointers_t *
elf_find_pointer_linker_section
  (elf_linker_section_pointers_t *linker_pointers,
   bfd_vma addend,
   elf_linker_section_t *lsect)
{
  for ( ; linker_pointers != NULL; linker_pointers = linker_pointers->next)
    if (lsect == linker_pointers->lsect && addend == linker_pointers->addend)
      return linker_pointers;

  return NULL;
}