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
typedef  scalar_t__ uchar_t ;
struct TYPE_3__ {scalar_t__ st_shndx; scalar_t__ st_name; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_ABS ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STT_OBJECT ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
ignore_symbol(GElf_Sym *sym, const char *name)
{
	uchar_t type = GELF_ST_TYPE(sym->st_info);

	/*
	 * As an optimization, we do not output function or data object
	 * records for undefined or anonymous symbols.
	 */
	if (sym->st_shndx == SHN_UNDEF || sym->st_name == 0)
		return (1);

	/*
	 * _START_ and _END_ are added to the symbol table by the
	 * linker, and will never have associated type information.
	 */
	if (strcmp(name, "_START_") == 0 || strcmp(name, "_END_") == 0)
		return (1);

	/*
	 * Do not output records for absolute-valued object symbols
	 * that have value zero.  The compiler insists on generating
	 * things like this for __fsr_init_value settings, etc.
	 */
	if (type == STT_OBJECT && sym->st_shndx == SHN_ABS &&
	    sym->st_value == 0)
		return (1);
	return (0);
}