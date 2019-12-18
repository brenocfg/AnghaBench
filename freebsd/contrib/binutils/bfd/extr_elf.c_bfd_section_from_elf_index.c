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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/ * bfd_section; } ;

/* Variables and functions */
 TYPE_1__** elf_elfsections (int /*<<< orphan*/ *) ; 
 unsigned int elf_numsections (int /*<<< orphan*/ *) ; 

asection *
bfd_section_from_elf_index (bfd *abfd, unsigned int index)
{
  if (index >= elf_numsections (abfd))
    return NULL;
  return elf_elfsections (abfd)[index]->bfd_section;
}