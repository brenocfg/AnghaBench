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
struct section {scalar_t__ type; char const* name; scalar_t__ link; int /*<<< orphan*/  scn; } ;
struct readelf {scalar_t__ shnum; int /*<<< orphan*/  elf; struct section* sl; } ;
struct TYPE_4__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_DYNSYM ; 
 scalar_t__ SHT_SYMTAB ; 
 scalar_t__ STT_SECTION ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getsym (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
get_symbol_name(struct readelf *re, int symtab, int i)
{
	struct section	*s;
	const char	*name;
	GElf_Sym	 sym;
	Elf_Data	*data;
	int		 elferr;

	s = &re->sl[symtab];
	if (s->type != SHT_SYMTAB && s->type != SHT_DYNSYM)
		return ("");
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		return ("");
	}
	if (gelf_getsym(data, i, &sym) != &sym)
		return ("");
	/* Return section name for STT_SECTION symbol. */
	if (GELF_ST_TYPE(sym.st_info) == STT_SECTION) {
		if (sym.st_shndx < re->shnum &&
		    re->sl[sym.st_shndx].name != NULL)
			return (re->sl[sym.st_shndx].name);
		return ("");
	}
	if (s->link >= re->shnum ||
	    (name = elf_strptr(re->elf, s->link, sym.st_name)) == NULL)
		return ("");

	return (name);
}