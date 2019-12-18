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
struct section {char const* name; size_t link; int /*<<< orphan*/  info; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  align; int /*<<< orphan*/  entsize; int /*<<< orphan*/  sz; int /*<<< orphan*/  off; int /*<<< orphan*/ * scn; } ;
struct readelf {size_t shnum; struct section* sl; int /*<<< orphan*/  elf; } ;
struct TYPE_3__ {size_t sh_link; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_addr; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_addralign; int /*<<< orphan*/  sh_entsize; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t SHN_UNDEF ; 
 struct section* calloc (size_t,int) ; 
 char const* elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_getshnum (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  elf_getshstrndx (int /*<<< orphan*/ ,size_t*) ; 
 size_t elf_ndxscn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct section*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
load_sections(struct readelf *re)
{
	struct section	*s;
	const char	*name;
	Elf_Scn		*scn;
	GElf_Shdr	 sh;
	size_t		 shstrndx, ndx;
	int		 elferr;

	/* Allocate storage for internal section list. */
	if (!elf_getshnum(re->elf, &re->shnum)) {
		warnx("elf_getshnum failed: %s", elf_errmsg(-1));
		return;
	}
	if (re->sl != NULL)
		free(re->sl);
	if ((re->sl = calloc(re->shnum, sizeof(*re->sl))) == NULL)
		err(EXIT_FAILURE, "calloc failed");

	/* Get the index of .shstrtab section. */
	if (!elf_getshstrndx(re->elf, &shstrndx)) {
		warnx("elf_getshstrndx failed: %s", elf_errmsg(-1));
		return;
	}

	if ((scn = elf_getscn(re->elf, 0)) == NULL)
		return;

	(void) elf_errno();
	do {
		if (gelf_getshdr(scn, &sh) == NULL) {
			warnx("gelf_getshdr failed: %s", elf_errmsg(-1));
			(void) elf_errno();
			continue;
		}
		if ((name = elf_strptr(re->elf, shstrndx, sh.sh_name)) == NULL) {
			(void) elf_errno();
			name = "<no-name>";
		}
		if ((ndx = elf_ndxscn(scn)) == SHN_UNDEF) {
			if ((elferr = elf_errno()) != 0) {
				warnx("elf_ndxscn failed: %s",
				    elf_errmsg(elferr));
				continue;
			}
		}
		if (ndx >= re->shnum) {
			warnx("section index of '%s' out of range", name);
			continue;
		}
		if (sh.sh_link >= re->shnum)
			warnx("section link %llu of '%s' out of range",
			    (unsigned long long)sh.sh_link, name);
		s = &re->sl[ndx];
		s->name = name;
		s->scn = scn;
		s->off = sh.sh_offset;
		s->sz = sh.sh_size;
		s->entsize = sh.sh_entsize;
		s->align = sh.sh_addralign;
		s->type = sh.sh_type;
		s->flags = sh.sh_flags;
		s->addr = sh.sh_addr;
		s->link = sh.sh_link;
		s->info = sh.sh_info;
	} while ((scn = elf_nextscn(re->elf, scn)) != NULL);
	elferr = elf_errno();
	if (elferr != 0)
		warnx("elf_nextscn failed: %s", elf_errmsg(elferr));
}