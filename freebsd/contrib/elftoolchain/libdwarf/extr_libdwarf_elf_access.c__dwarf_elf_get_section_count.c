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
struct TYPE_2__ {int /*<<< orphan*/  eo_seccnt; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__ Dwarf_Elf_Object ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Dwarf_Unsigned
_dwarf_elf_get_section_count(void *obj)
{
	Dwarf_Elf_Object *e;

	e = obj;
	assert(e != NULL);

	return (e->eo_seccnt);
}