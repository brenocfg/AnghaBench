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
struct elf_info {TYPE_1__* symtab_stop; TYPE_1__* symtab_start; } ;
struct TYPE_4__ {scalar_t__ st_shndx; scalar_t__ st_value; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ SHN_LORESERVE ; 
 int /*<<< orphan*/  is_valid_name (struct elf_info*,TYPE_1__*) ; 
 char* sec_name (struct elf_info*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static Elf_Sym *find_elf_symbol2(struct elf_info *elf, Elf_Addr addr,
				 const char *sec)
{
	Elf_Sym *sym;
	Elf_Sym *near = NULL;
	Elf_Addr distance = ~0;

	for (sym = elf->symtab_start; sym < elf->symtab_stop; sym++) {
		const char *symsec;

		if (sym->st_shndx >= SHN_LORESERVE)
			continue;
		symsec = sec_name(elf, sym->st_shndx);
		if (strcmp(symsec, sec) != 0)
			continue;
		if (!is_valid_name(elf, sym))
			continue;
		if (sym->st_value <= addr) {
			if ((addr - sym->st_value) < distance) {
				distance = addr - sym->st_value;
				near = sym;
			} else if ((addr - sym->st_value) == distance) {
				near = sym;
			}
		}
	}
	return near;
}