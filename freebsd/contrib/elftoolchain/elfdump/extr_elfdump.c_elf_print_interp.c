#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elfdump {int /*<<< orphan*/  elf; int /*<<< orphan*/  snl; } ;
struct TYPE_4__ {scalar_t__ p_type; size_t p_offset; } ;
typedef  TYPE_1__ GElf_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  PRT (char*,...) ; 
 scalar_t__ PT_INTERP ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_getphnum (int /*<<< orphan*/ ,size_t*) ; 
 char* elf_rawfile (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * find_name (struct elfdump*,char*) ; 
 TYPE_1__* gelf_getphdr (int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_interp(struct elfdump *ed)
{
	const char *s;
	GElf_Phdr phdr;
	size_t filesize, i, phnum;

	if (!STAILQ_EMPTY(&ed->snl) && find_name(ed, "PT_INTERP") == NULL)
		return;

	if ((s = elf_rawfile(ed->elf, &filesize)) == NULL) {
		warnx("elf_rawfile failed: %s", elf_errmsg(-1));
		return;
	}
	if (!elf_getphnum(ed->elf, &phnum)) {
		warnx("elf_getphnum failed: %s", elf_errmsg(-1));
		return;
	}
	for (i = 0; i < phnum; i++) {
		if (gelf_getphdr(ed->elf, i, &phdr) != &phdr) {
			warnx("elf_getphdr failed: %s", elf_errmsg(-1));
			continue;
		}
		if (phdr.p_type == PT_INTERP) {
			if (phdr.p_offset >= filesize) {
				warnx("invalid phdr offset");
				continue;
			}
			PRT("\ninterp:\n");
			PRT("\t%s\n", s + phdr.p_offset);
		}
	}
}