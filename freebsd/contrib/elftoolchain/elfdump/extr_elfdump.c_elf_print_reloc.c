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
struct section {scalar_t__ type; int /*<<< orphan*/  scn; int /*<<< orphan*/  name; } ;
struct elfdump {size_t shnum; int /*<<< orphan*/  snl; struct section* sl; } ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_print_rel (struct elfdump*,struct section*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_print_rela (struct elfdump*,struct section*,int /*<<< orphan*/ *) ; 
 scalar_t__ find_name (struct elfdump*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_reloc(struct elfdump *ed)
{
	struct section	*s;
	Elf_Data	*data;
	size_t		 i;
	int		 elferr;

	for (i = 0; i < ed->shnum; i++) {
		s = &ed->sl[i];
		if ((s->type == SHT_REL || s->type == SHT_RELA) &&
		    (STAILQ_EMPTY(&ed->snl) || find_name(ed, s->name))) {
			(void) elf_errno();
			if ((data = elf_getdata(s->scn, NULL)) == NULL) {
				elferr = elf_errno();
				if (elferr != 0)
					warnx("elf_getdata failed: %s",
					    elf_errmsg(elferr));
				continue;
			}
			if (s->type == SHT_REL)
				elf_print_rel(ed, s, data);
			else
				elf_print_rela(ed, s, data);
		}
	}
}