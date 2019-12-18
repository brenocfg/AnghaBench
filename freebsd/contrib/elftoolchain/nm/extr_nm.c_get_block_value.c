#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int bl_len; scalar_t__ bl_data; } ;
struct TYPE_6__ {scalar_t__* e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  TYPE_2__ Dwarf_Block ;

/* Variables and functions */
 scalar_t__ DW_DLV_OK ; 
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 int /*<<< orphan*/  be32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_get_elf (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_1__* gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
get_block_value(Dwarf_Debug dbg, Dwarf_Block *block)
{
	Elf *elf;
	GElf_Ehdr eh;
	Dwarf_Error de;

	if (dwarf_get_elf(dbg, &elf, &de) != DW_DLV_OK) {
		warnx("dwarf_get_elf failed: %s", dwarf_errmsg(de));
		return (0);
	}

	if (gelf_getehdr(elf, &eh) != &eh) {
		warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
		return (0);
	}

	if (block->bl_len == 5) {
		if (eh.e_ident[EI_DATA] == ELFDATA2LSB)
			return (le32dec((uint8_t *) block->bl_data + 1));
		else
			return (be32dec((uint8_t *) block->bl_data + 1));
	} else if (block->bl_len == 9) {
		if (eh.e_ident[EI_DATA] == ELFDATA2LSB)
			return (le64dec((uint8_t *) block->bl_data + 1));
		else
			return (be64dec((uint8_t *) block->bl_data + 1));
	}

	return (0);
}