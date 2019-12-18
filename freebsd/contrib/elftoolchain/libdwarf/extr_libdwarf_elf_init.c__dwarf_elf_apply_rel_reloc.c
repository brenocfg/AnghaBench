#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_5__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ GElf_Rel ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int ELFDATA2MSB ; 
 size_t GELF_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int _dwarf_get_reloc_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_read_lsb (void*,scalar_t__*,int) ; 
 scalar_t__ _dwarf_read_msb (void*,scalar_t__*,int) ; 
 int /*<<< orphan*/  _dwarf_write_lsb (void*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  _dwarf_write_msb (void*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/ * gelf_getrel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getsym (int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 

__attribute__((used)) static void
_dwarf_elf_apply_rel_reloc(Dwarf_Debug dbg, void *buf, uint64_t bufsize,
    Elf_Data *rel_data, Elf_Data *symtab_data, int endian)
{
	Dwarf_Unsigned type;
	GElf_Rel rel;
	GElf_Sym sym;
	size_t symndx;
	uint64_t offset;
	uint64_t addend;
	int size, j;

	j = 0;
	while (gelf_getrel(rel_data, j++, &rel) != NULL) {
		symndx = GELF_R_SYM(rel.r_info);
		type = GELF_R_TYPE(rel.r_info);

		if (gelf_getsym(symtab_data, symndx, &sym) == NULL)
			continue;

		size = _dwarf_get_reloc_size(dbg, type);
		if (size == 0)
			continue; /* Unknown or non-absolute relocation. */

		offset = rel.r_offset;
		if (offset + size >= bufsize)
			continue;

		if (endian == ELFDATA2MSB)
			addend = _dwarf_read_msb(buf, &offset, size);
		else
			addend = _dwarf_read_lsb(buf, &offset, size);

		offset = rel.r_offset;
		if (endian == ELFDATA2MSB)
			_dwarf_write_msb(buf, &offset, sym.st_value + addend,
			    size);
		else
			_dwarf_write_lsb(buf, &offset, sym.st_value + addend,
			    size);
	}
}