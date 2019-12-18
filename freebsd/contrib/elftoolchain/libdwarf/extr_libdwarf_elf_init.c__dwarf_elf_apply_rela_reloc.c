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
struct TYPE_6__ {scalar_t__ r_offset; scalar_t__ r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_5__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ GElf_Rela ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int ELFDATA2MSB ; 
 size_t GELF_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GELF_R_TYPE (int /*<<< orphan*/ ) ; 
 int _dwarf_get_reloc_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dwarf_write_lsb (void*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  _dwarf_write_msb (void*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/ * gelf_getrela (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getsym (int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 

__attribute__((used)) static void
_dwarf_elf_apply_rela_reloc(Dwarf_Debug dbg, void *buf, uint64_t bufsize,
    Elf_Data *rel_data, Elf_Data *symtab_data, int endian)
{
	Dwarf_Unsigned type;
	GElf_Rela rela;
	GElf_Sym sym;
	size_t symndx;
	uint64_t offset;
	int size, j;

	j = 0;
	while (gelf_getrela(rel_data, j++, &rela) != NULL) {
		symndx = GELF_R_SYM(rela.r_info);
		type = GELF_R_TYPE(rela.r_info);

		if (gelf_getsym(symtab_data, symndx, &sym) == NULL)
			continue;

		offset = rela.r_offset;
		size = _dwarf_get_reloc_size(dbg, type);
		if (size == 0)
			continue; /* Unknown or non-absolute relocation. */
		if (offset + size >= bufsize)
			continue;

		if (endian == ELFDATA2MSB)
			_dwarf_write_msb(buf, &offset,
			    sym.st_value + rela.r_addend, size);
		else
			_dwarf_write_lsb(buf, &offset,
			    sym.st_value + rela.r_addend, size);
	}
}