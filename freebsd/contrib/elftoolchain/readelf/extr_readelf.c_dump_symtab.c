#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct section {scalar_t__ link; char* name; scalar_t__ type; int /*<<< orphan*/  scn; } ;
struct TYPE_9__ {int /*<<< orphan*/ * e_ident; int /*<<< orphan*/  e_machine; } ;
struct readelf {scalar_t__ shnum; int* vs; size_t ver_sz; TYPE_2__* ver; int /*<<< orphan*/  elf; TYPE_1__ ehdr; struct section* sl; } ;
struct TYPE_12__ {scalar_t__ d_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; scalar_t__ st_size; scalar_t__ st_value; } ;
struct TYPE_10__ {char* name; scalar_t__ type; } ;
typedef  TYPE_3__ GElf_Sym ;
typedef  TYPE_4__ Elf_Data ;

/* Variables and functions */
 size_t EI_OSABI ; 
 int /*<<< orphan*/  GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_DYNSYM ; 
 int VERSYM_HIDDEN ; 
 size_t VERSYM_VERSION ; 
 size_t elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_4__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* gelf_getsym (TYPE_4__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* st_bind (int /*<<< orphan*/ ) ; 
 char* st_shndx (int /*<<< orphan*/ ) ; 
 char* st_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* st_vis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,size_t) ; 

__attribute__((used)) static void
dump_symtab(struct readelf *re, int i)
{
	struct section *s;
	Elf_Data *d;
	GElf_Sym sym;
	const char *name;
	uint32_t stab;
	int elferr, j, len;
	uint16_t vs;

	s = &re->sl[i];
	if (s->link >= re->shnum)
		return;
	stab = s->link;
	(void) elf_errno();
	if ((d = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		return;
	}
	if (d->d_size <= 0)
		return;
	if (!get_ent_count(s, &len))
		return;
	printf("Symbol table (%s)", s->name);
	printf(" contains %d entries:\n", len);
	printf("%7s%9s%14s%5s%8s%6s%9s%5s\n", "Num:", "Value", "Size", "Type",
	    "Bind", "Vis", "Ndx", "Name");

	for (j = 0; j < len; j++) {
		if (gelf_getsym(d, j, &sym) != &sym) {
			warnx("gelf_getsym failed: %s", elf_errmsg(-1));
			continue;
		}
		printf("%6d:", j);
		printf(" %16.16jx", (uintmax_t) sym.st_value);
		printf(" %5ju", (uintmax_t) sym.st_size);
		printf(" %-7s", st_type(re->ehdr.e_machine,
		    re->ehdr.e_ident[EI_OSABI], GELF_ST_TYPE(sym.st_info)));
		printf(" %-6s", st_bind(GELF_ST_BIND(sym.st_info)));
		printf(" %-8s", st_vis(GELF_ST_VISIBILITY(sym.st_other)));
		printf(" %3s", st_shndx(sym.st_shndx));
		if ((name = elf_strptr(re->elf, stab, sym.st_name)) != NULL)
			printf(" %s", name);
		/* Append symbol version string for SHT_DYNSYM symbol table. */
		if (s->type == SHT_DYNSYM && re->ver != NULL &&
		    re->vs != NULL && re->vs[j] > 1) {
			vs = re->vs[j] & VERSYM_VERSION;
			if (vs >= re->ver_sz || re->ver[vs].name == NULL) {
				warnx("invalid versym version index %u", vs);
				break;
			}
			if (re->vs[j] & VERSYM_HIDDEN || re->ver[vs].type == 0)
				printf("@%s (%d)", re->ver[vs].name, vs);
			else
				printf("@@%s (%d)", re->ver[vs].name, vs);
		}
		putchar('\n');
	}

}