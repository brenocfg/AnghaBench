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
typedef  scalar_t__ uint64_t ;
struct section {scalar_t__ type; scalar_t__ addr; int /*<<< orphan*/  scn; } ;
struct readelf {int options; size_t shnum; struct section* sl; } ;
struct TYPE_10__ {scalar_t__ d_size; } ;
struct TYPE_8__ {scalar_t__ d_val; } ;
struct TYPE_9__ {scalar_t__ d_tag; TYPE_1__ d_un; } ;
typedef  TYPE_2__ GElf_Dyn ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 scalar_t__ DT_SYMTAB ; 
 int RE_DD ; 
 scalar_t__ SHT_DYNAMIC ; 
 scalar_t__ SHT_DYNSYM ; 
 scalar_t__ SHT_SYMTAB ; 
 int /*<<< orphan*/  dump_symtab (struct readelf*,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* gelf_getdyn (TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_symtabs(struct readelf *re)
{
	GElf_Dyn dyn;
	Elf_Data *d;
	struct section *s;
	uint64_t dyn_off;
	int elferr, i, len;

	/*
	 * If -D is specified, only dump the symbol table specified by
	 * the DT_SYMTAB entry in the .dynamic section.
	 */
	dyn_off = 0;
	if (re->options & RE_DD) {
		s = NULL;
		for (i = 0; (size_t)i < re->shnum; i++)
			if (re->sl[i].type == SHT_DYNAMIC) {
				s = &re->sl[i];
				break;
			}
		if (s == NULL)
			return;
		(void) elf_errno();
		if ((d = elf_getdata(s->scn, NULL)) == NULL) {
			elferr = elf_errno();
			if (elferr != 0)
				warnx("elf_getdata failed: %s", elf_errmsg(-1));
			return;
		}
		if (d->d_size <= 0)
			return;
		if (!get_ent_count(s, &len))
			return;

		for (i = 0; i < len; i++) {
			if (gelf_getdyn(d, i, &dyn) != &dyn) {
				warnx("gelf_getdyn failed: %s", elf_errmsg(-1));
				continue;
			}
			if (dyn.d_tag == DT_SYMTAB) {
				dyn_off = dyn.d_un.d_val;
				break;
			}
		}
	}

	/* Find and dump symbol tables. */
	for (i = 0; (size_t)i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->type == SHT_SYMTAB || s->type == SHT_DYNSYM) {
			if (re->options & RE_DD) {
				if (dyn_off == s->addr) {
					dump_symtab(re, i);
					break;
				}
			} else
				dump_symtab(re, i);
		}
	}
}