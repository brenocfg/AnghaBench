#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char const* uintmax_t ;
typedef  char const* uint16_t ;
struct section {char const* name; scalar_t__ sz; int /*<<< orphan*/  link; int /*<<< orphan*/  scn; } ;
struct TYPE_8__ {int /*<<< orphan*/  e_machine; } ;
struct elfdump {int flags; scalar_t__ ec; TYPE_1__ ehdr; struct section* sl; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_10__ {scalar_t__ d_size; } ;
struct TYPE_9__ {size_t st_other; scalar_t__ st_shndx; int /*<<< orphan*/  st_info; scalar_t__ st_size; scalar_t__ st_value; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_2__ GElf_Sym ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 scalar_t__ ELFCLASS32 ; 
 int /*<<< orphan*/  GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT (char*,...) ; 
 int SOLARIS_FMT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* gelf_getsym (TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 char* get_string (struct elfdump*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_versym (struct elfdump*,int,char const***,int*) ; 
 char const* sh_name (struct elfdump*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  st_bindings (int /*<<< orphan*/ ) ; 
 char const* st_bindings_S (int /*<<< orphan*/ ) ; 
 char const** st_others ; 
 int /*<<< orphan*/  st_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* st_type_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_symtab(struct elfdump *ed, int i)
{
	struct section	*s;
	const char	*name;
	uint16_t	*vs;
	char		 idx[13];
	Elf_Data	*data;
	GElf_Sym	 sym;
	int		 len, j, elferr, nvs;

	s = &ed->sl[i];
	if (ed->flags & SOLARIS_FMT)
		PRT("\nSymbol Table Section:  %s\n", s->name);
	else
		PRT("\nsymbol table (%s):\n", s->name);
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		return;
	}
	vs = NULL;
	nvs = 0;
	assert(data->d_size == s->sz);
	if (!get_ent_count(s, &len))
		return;
	if (ed->flags & SOLARIS_FMT) {
		if (ed->ec == ELFCLASS32)
			PRT("     index    value       ");
		else
			PRT("     index        value           ");
		PRT("size     type bind oth ver shndx       name\n");
		get_versym(ed, i, &vs, &nvs);
		if (vs != NULL && nvs != len) {
			warnx("#symbol not equal to #versym");
			vs = NULL;
		}
	}
	for (j = 0; j < len; j++) {
		if (gelf_getsym(data, j, &sym) != &sym) {
			warnx("gelf_getsym failed: %s", elf_errmsg(-1));
			continue;
		}
		name = get_string(ed, s->link, sym.st_name);
		if (ed->flags & SOLARIS_FMT) {
			snprintf(idx, sizeof(idx), "[%d]", j);
			if (ed->ec == ELFCLASS32)
				PRT("%10s  ", idx);
			else
				PRT("%10s      ", idx);
			PRT("0x%8.8jx ", (uintmax_t)sym.st_value);
			if (ed->ec == ELFCLASS32)
				PRT("0x%8.8jx  ", (uintmax_t)sym.st_size);
			else
				PRT("0x%12.12jx  ", (uintmax_t)sym.st_size);
			PRT("%s ", st_type_S(GELF_ST_TYPE(sym.st_info)));
			PRT("%s  ", st_bindings_S(GELF_ST_BIND(sym.st_info)));
			PRT("%c  ", st_others[sym.st_other]);
			PRT("%3u ", (vs == NULL ? 0 : vs[j]));
			PRT("%-11.11s ", sh_name(ed, sym.st_shndx));
			PRT("%s\n", name);
		} else {
			PRT("\nentry: %d\n", j);
			PRT("\tst_name: %s\n", name);
			PRT("\tst_value: %#jx\n", (uintmax_t)sym.st_value);
			PRT("\tst_size: %ju\n", (uintmax_t)sym.st_size);
			PRT("\tst_info: %s %s\n",
			    st_type(ed->ehdr.e_machine,
			    GELF_ST_TYPE(sym.st_info)),
			    st_bindings(GELF_ST_BIND(sym.st_info)));
			PRT("\tst_shndx: %ju\n", (uintmax_t)sym.st_shndx);
		}
	}
}