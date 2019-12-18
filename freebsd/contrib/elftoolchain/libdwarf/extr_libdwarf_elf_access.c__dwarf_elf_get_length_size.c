#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ e_machine; } ;
struct TYPE_4__ {TYPE_1__ eo_ehdr; int /*<<< orphan*/  eo_elf; } ;
typedef  int Dwarf_Small ;
typedef  TYPE_2__ Dwarf_Elf_Object ;

/* Variables and functions */
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ EM_MIPS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_getclass (int /*<<< orphan*/ ) ; 

Dwarf_Small
_dwarf_elf_get_length_size(void *obj)
{
	Dwarf_Elf_Object *e;

	e = obj;
	assert(e != NULL);

	if (gelf_getclass(e->eo_elf) == ELFCLASS32)
		return (4);
	else if (e->eo_ehdr.e_machine == EM_MIPS)
		return (8);
	else
		return (4);
}