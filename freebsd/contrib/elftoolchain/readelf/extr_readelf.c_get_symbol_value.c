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
typedef  int /*<<< orphan*/  uint64_t ;
struct section {scalar_t__ type; int /*<<< orphan*/  scn; } ;
struct readelf {struct section* sl; } ;
struct TYPE_4__ {int /*<<< orphan*/  st_value; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 scalar_t__ SHT_DYNSYM ; 
 scalar_t__ SHT_SYMTAB ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* gelf_getsym (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
get_symbol_value(struct readelf *re, int symtab, int i)
{
	struct section	*s;
	GElf_Sym	 sym;
	Elf_Data	*data;
	int		 elferr;

	s = &re->sl[symtab];
	if (s->type != SHT_SYMTAB && s->type != SHT_DYNSYM)
		return (0);
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		return (0);
	}
	if (gelf_getsym(data, i, &sym) != &sym)
		return (0);

	return (sym.st_value);
}