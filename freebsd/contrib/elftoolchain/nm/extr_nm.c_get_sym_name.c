#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int st_shndx; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_SECTION ; 
 char* elf_strptr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
get_sym_name(Elf *elf, const GElf_Sym *sym, size_t ndx, const char **sec_table,
    int sec_table_size)
{
	const char *sym_name;

	sym_name = NULL;

	/* Show section name as symbol name for STT_SECTION symbols. */
	if (GELF_ST_TYPE(sym->st_info) == STT_SECTION) {
		if (sec_table != NULL && sym->st_shndx < sec_table_size)
			sym_name = sec_table[sym->st_shndx];
	} else
		sym_name = elf_strptr(elf, ndx, sym->st_name);

	if (sym_name == NULL)
		sym_name = "(null)";

	return (sym_name);
}