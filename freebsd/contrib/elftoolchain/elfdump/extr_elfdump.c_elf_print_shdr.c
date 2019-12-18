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
typedef  size_t uintmax_t ;
struct section {size_t name; scalar_t__ flags; size_t link; size_t info; scalar_t__ entsize; scalar_t__ align; scalar_t__ sz; scalar_t__ off; scalar_t__ addr; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  e_machine; } ;
struct elfdump {int flags; size_t shnum; TYPE_1__ ehdr; struct section* sl; int /*<<< orphan*/  snl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT (char*,...) ; 
 int SOLARIS_FMT ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 size_t sh_flags (scalar_t__) ; 
 size_t sh_types (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_print_shdr(struct elfdump *ed)
{
	struct section *s;
	size_t i;

	if (!STAILQ_EMPTY(&ed->snl))
		return;

	if ((ed->flags & SOLARIS_FMT) == 0)
		PRT("\nsection header:\n");
	for (i = 0; i < ed->shnum; i++) {
		s = &ed->sl[i];
		if (ed->flags & SOLARIS_FMT) {
			if (i == 0)
				continue;
			PRT("\nSection Header[%zu]:", i);
			PRT("  sh_name: %s\n", s->name);
			PRT("    sh_addr:      %#-14jx", (uintmax_t)s->addr);
			if (s->flags != 0)
				PRT("  sh_flags:   [ %s ]\n", sh_flags(s->flags));
			else
				PRT("  sh_flags:   0\n");
			PRT("    sh_size:      %#-14jx", (uintmax_t)s->sz);
			PRT("  sh_type:    [ %s ]\n",
			    sh_types(ed->ehdr.e_machine, s->type));
			PRT("    sh_offset:    %#-14jx", (uintmax_t)s->off);
			PRT("  sh_entsize: %#jx\n", (uintmax_t)s->entsize);
			PRT("    sh_link:      %-14u", s->link);
			PRT("  sh_info:    %u\n", s->info);
			PRT("    sh_addralign: %#jx\n", (uintmax_t)s->align);
		} else {
			PRT("\n");
			PRT("entry: %ju\n", (uintmax_t)i);
			PRT("\tsh_name: %s\n", s->name);
			PRT("\tsh_type: %s\n",
			    sh_types(ed->ehdr.e_machine, s->type));
			PRT("\tsh_flags: %s\n", sh_flags(s->flags));
			PRT("\tsh_addr: %#jx\n", (uintmax_t)s->addr);
			PRT("\tsh_offset: %ju\n", (uintmax_t)s->off);
			PRT("\tsh_size: %ju\n", (uintmax_t)s->sz);
			PRT("\tsh_link: %u\n", s->link);
			PRT("\tsh_info: %u\n", s->info);
			PRT("\tsh_addralign: %ju\n", (uintmax_t)s->align);
			PRT("\tsh_entsize: %ju\n", (uintmax_t)s->entsize);
		}
	}
}