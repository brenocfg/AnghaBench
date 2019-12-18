#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct section {scalar_t__ sz; int /*<<< orphan*/  link; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_7__ {TYPE_3__ rel; } ;
struct rel_entry {TYPE_1__ u_r; int /*<<< orphan*/  symn; int /*<<< orphan*/  type; } ;
struct elfdump {int flags; } ;
struct TYPE_8__ {scalar_t__ d_size; } ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  GELF_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT (char*,...) ; 
 int /*<<< orphan*/  SHT_REL ; 
 int SOLARIS_FMT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_print_rel_entry (struct elfdump*,struct section*,int,struct rel_entry*) ; 
 TYPE_3__* gelf_getrel (TYPE_2__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  get_symbol_name (struct elfdump*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_rel(struct elfdump *ed, struct section *s, Elf_Data *data)
{
	struct rel_entry	r;
	int			j, len;

	if (ed->flags & SOLARIS_FMT) {
		PRT("\nRelocation Section:  %s\n", s->name);
		PRT("        type                          offset     "
		    "section        with respect to\n");
	} else
		PRT("\nrelocation (%s):\n", s->name);
	r.type = SHT_REL;
	assert(data->d_size == s->sz);
	if (!get_ent_count(s, &len))
		return;
	for (j = 0; j < len; j++) {
		if (gelf_getrel(data, j, &r.u_r.rel) != &r.u_r.rel) {
			warnx("gelf_getrel failed: %s", elf_errmsg(-1));
			continue;
		}
		r.symn = get_symbol_name(ed, s->link,
		    GELF_R_SYM(r.u_r.rel.r_info));
		elf_print_rel_entry(ed, s, j, &r);
	}
}