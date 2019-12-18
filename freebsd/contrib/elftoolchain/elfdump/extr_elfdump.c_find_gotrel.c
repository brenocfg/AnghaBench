#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct section {scalar_t__ type; scalar_t__ sz; scalar_t__ addr; int entsize; int /*<<< orphan*/  link; int /*<<< orphan*/  scn; } ;
struct TYPE_10__ {scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_8__ {TYPE_4__ rel; int /*<<< orphan*/  rela; } ;
struct rel_entry {scalar_t__ type; TYPE_1__ u_r; int /*<<< orphan*/  symn; } ;
struct elfdump {size_t shnum; struct section* sl; } ;
struct TYPE_9__ {scalar_t__ d_size; } ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  GELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_2__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* gelf_getrel (TYPE_2__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/ * gelf_getrela (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  get_symbol_name (struct elfdump*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rel_entry*,struct rel_entry*,int) ; 
 int /*<<< orphan*/  memset (struct rel_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_gotrel(struct elfdump *ed, struct section *gs, struct rel_entry *got)
{
	struct section		*s;
	struct rel_entry	 r;
	Elf_Data		*data;
	size_t			 i;
	int			 elferr, j, k, len;

	for(i = 0; i < ed->shnum; i++) {
		s = &ed->sl[i];
		if (s->type != SHT_REL && s->type != SHT_RELA)
			continue;
		(void) elf_errno();
		if ((data = elf_getdata(s->scn, NULL)) == NULL) {
			elferr = elf_errno();
			if (elferr != 0)
				warnx("elf_getdata failed: %s",
				    elf_errmsg(elferr));
			return;
		}
		memset(&r, 0, sizeof(struct rel_entry));
		r.type = s->type;
		assert(data->d_size == s->sz);
		if (!get_ent_count(s, &len))
			return;
		for (j = 0; j < len; j++) {
			if (s->type == SHT_REL) {
				if (gelf_getrel(data, j, &r.u_r.rel) !=
				    &r.u_r.rel) {
					warnx("gelf_getrel failed: %s",
					    elf_errmsg(-1));
					continue;
				}
			} else {
				if (gelf_getrela(data, j, &r.u_r.rela) !=
				    &r.u_r.rela) {
					warnx("gelf_getrel failed: %s",
					    elf_errmsg(-1));
					continue;
				}
			}
			if (r.u_r.rel.r_offset >= gs->addr &&
			    r.u_r.rel.r_offset < gs->addr + gs->sz) {
				r.symn = get_symbol_name(ed, s->link,
				    GELF_R_SYM(r.u_r.rel.r_info));
				k = (r.u_r.rel.r_offset - gs->addr) /
				    gs->entsize;
				memcpy(&got[k], &r, sizeof(struct rel_entry));
			}
		}
	}
}