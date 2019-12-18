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
struct TYPE_3__ {int* e_ident; } ;
struct TYPE_4__ {TYPE_1__ eo_ehdr; } ;
typedef  int /*<<< orphan*/  Dwarf_Endianness ;
typedef  TYPE_2__ Dwarf_Elf_Object ;

/* Variables and functions */
 int /*<<< orphan*/  DW_OBJECT_LSB ; 
 int /*<<< orphan*/  DW_OBJECT_MSB ; 
 size_t EI_DATA ; 
#define  ELFDATA2LSB 130 
#define  ELFDATA2MSB 129 
#define  ELFDATANONE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Dwarf_Endianness
_dwarf_elf_get_byte_order(void *obj)
{
	Dwarf_Elf_Object *e;

	e = obj;
	assert(e != NULL);

	switch (e->eo_ehdr.e_ident[EI_DATA]) {
	case ELFDATA2MSB:
		return (DW_OBJECT_MSB);

	case ELFDATA2LSB:
	case ELFDATANONE:
	default:
		return (DW_OBJECT_LSB);
	}
}