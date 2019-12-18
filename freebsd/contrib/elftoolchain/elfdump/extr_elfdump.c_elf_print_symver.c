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
struct section {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct elfdump {size_t shnum; int /*<<< orphan*/  snl; struct section* sl; } ;

/* Variables and functions */
 scalar_t__ SHT_SUNW_verdef ; 
 scalar_t__ SHT_SUNW_verneed ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_print_verdef (struct elfdump*,struct section*) ; 
 int /*<<< orphan*/  elf_print_verneed (struct elfdump*,struct section*) ; 
 int /*<<< orphan*/  find_name (struct elfdump*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_symver(struct elfdump *ed)
{
	struct section	*s;
	size_t		 i;

	for (i = 0; i < ed->shnum; i++) {
		s = &ed->sl[i];
		if (!STAILQ_EMPTY(&ed->snl) && !find_name(ed, s->name))
			continue;
		if (s->type == SHT_SUNW_verdef)
			elf_print_verdef(ed, s);
		if (s->type == SHT_SUNW_verneed)
			elf_print_verneed(ed, s);
	}
}