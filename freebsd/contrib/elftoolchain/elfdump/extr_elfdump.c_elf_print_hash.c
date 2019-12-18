#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct section {scalar_t__ type; int entsize; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ e_machine; } ;
struct elfdump {size_t shnum; TYPE_1__ ehdr; int /*<<< orphan*/  snl; struct section* sl; } ;

/* Variables and functions */
 scalar_t__ EM_ALPHA ; 
 scalar_t__ SHT_GNU_HASH ; 
 scalar_t__ SHT_HASH ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_print_gnu_hash (struct elfdump*,struct section*) ; 
 int /*<<< orphan*/  elf_print_svr4_hash (struct elfdump*,struct section*) ; 
 int /*<<< orphan*/  elf_print_svr4_hash64 (struct elfdump*,struct section*) ; 
 scalar_t__ find_name (struct elfdump*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_hash(struct elfdump *ed)
{
	struct section	*s;
	size_t		 i;

	for (i = 0; i < ed->shnum; i++) {
		s = &ed->sl[i];
		if ((s->type == SHT_HASH || s->type == SHT_GNU_HASH) &&
		    (STAILQ_EMPTY(&ed->snl) || find_name(ed, s->name))) {
			if (s->type == SHT_GNU_HASH)
				elf_print_gnu_hash(ed, s);
			else if (ed->ehdr.e_machine == EM_ALPHA &&
			    s->entsize == 8)
				elf_print_svr4_hash64(ed, s);
			else
				elf_print_svr4_hash(ed, s);
		}
	}
}