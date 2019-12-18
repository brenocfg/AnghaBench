#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct section {scalar_t__ type; int /*<<< orphan*/  scn; } ;
struct readelf {size_t shnum; struct section* sl; } ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/  dump_rel (struct readelf*,struct section*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_rela (struct readelf*,struct section*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_reloc(struct readelf *re)
{
	struct section *s;
	Elf_Data *d;
	int i, elferr;

	for (i = 0; (size_t)i < re->shnum; i++) {
		s = &re->sl[i];
		if (s->type == SHT_REL || s->type == SHT_RELA) {
			(void) elf_errno();
			if ((d = elf_getdata(s->scn, NULL)) == NULL) {
				elferr = elf_errno();
				if (elferr != 0)
					warnx("elf_getdata failed: %s",
					    elf_errmsg(elferr));
				continue;
			}
			if (s->type == SHT_REL)
				dump_rel(re, s, d);
			else
				dump_rela(re, s, d);
		}
	}
}