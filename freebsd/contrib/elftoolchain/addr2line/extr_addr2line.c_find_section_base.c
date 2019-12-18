#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ e_type; } ;
struct TYPE_6__ {scalar_t__ sh_size; scalar_t__ sh_addr; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ ET_REL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/  elf_getshstrndx (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 TYPE_2__* gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ section_base ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static void
find_section_base(const char *exe, Elf *e, const char *section)
{
	Dwarf_Addr off;
	Elf_Scn *scn;
	GElf_Ehdr eh;
	GElf_Shdr sh;
	size_t shstrndx;
	int elferr;
	const char *name;

	if (gelf_getehdr(e, &eh) != &eh) {
		warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
		return;
	}

	if (!elf_getshstrndx(e, &shstrndx)) {
		warnx("elf_getshstrndx failed: %s", elf_errmsg(-1));
		return;
	}

	(void) elf_errno();
	off = 0;
	scn = NULL;
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		if (gelf_getshdr(scn, &sh) == NULL) {
			warnx("gelf_getshdr failed: %s", elf_errmsg(-1));
			continue;
		}
		if ((name = elf_strptr(e, shstrndx, sh.sh_name)) == NULL)
			goto next;
		if (!strcmp(section, name)) {
			if (eh.e_type == ET_EXEC || eh.e_type == ET_DYN) {
				/*
				 * For executables, section base is the virtual
				 * address of the specified section.
				 */
				section_base = sh.sh_addr;
			} else if (eh.e_type == ET_REL) {
				/*
				 * For relocatables, section base is the
				 * relative offset of the specified section
				 * to the start of the first section.
				 */
				section_base = off;
			} else
				warnx("unknown e_type %u", eh.e_type);
			return;
		}
	next:
		off += sh.sh_size;
	}
	elferr = elf_errno();
	if (elferr != 0)
		warnx("elf_nextscn failed: %s", elf_errmsg(elferr));

	errx(EXIT_FAILURE, "%s: cannot find section %s", exe, section);
}