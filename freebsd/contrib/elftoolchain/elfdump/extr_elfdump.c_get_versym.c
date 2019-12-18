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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct section {scalar_t__ type; scalar_t__ link; scalar_t__ sz; int /*<<< orphan*/  scn; } ;
struct elfdump {size_t shnum; struct section* sl; } ;
struct TYPE_3__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
typedef  TYPE_1__ Elf_Data ;

/* Variables and functions */
 scalar_t__ SHT_SUNW_versym ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ent_count (struct section*,int*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_versym(struct elfdump *ed, int i, uint16_t **vs, int *nvs)
{
	struct section	*s;
	Elf_Data	*data;
	size_t		 j;
	int		 elferr;

	s = NULL;
	for (j = 0; j < ed->shnum; j++) {
		s = &ed->sl[j];
		if (s->type == SHT_SUNW_versym && s->link == (uint32_t)i)
			break;
	}
	if (j >= ed->shnum) {
		*vs = NULL;
		return;
	}
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		*vs = NULL;
		return;
	}

	*vs = data->d_buf;
	assert(data->d_size == s->sz);
	if (!get_ent_count(s, nvs))
		*nvs = 0;
}