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
struct elfcopy {int /*<<< orphan*/ * v_grp; int /*<<< orphan*/  ein; } ;
struct TYPE_4__ {scalar_t__ sh_type; size_t sh_info; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ SHT_GROUP ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 scalar_t__ elf_getshstrndx (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ is_remove_section (struct elfcopy*,char const*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
mark_section_group_symbols(struct elfcopy *ecp, size_t sc)
{
	const char	*name;
	Elf_Scn		*s;
	GElf_Shdr	 sh;
	size_t		 indx;
	int		 elferr;

	ecp->v_grp = calloc((sc + 7) / 8, 1);
	if (ecp->v_grp == NULL)
		err(EXIT_FAILURE, "calloc failed");

	if (elf_getshstrndx(ecp->ein, &indx) == 0)
		errx(EXIT_FAILURE, "elf_getshstrndx failed: %s",
		    elf_errmsg(-1));

	s = NULL;
	while ((s = elf_nextscn(ecp->ein, s)) != NULL) {
		if (gelf_getshdr(s, &sh) != &sh)
			errx(EXIT_FAILURE, "elf_getshdr failed: %s",
			    elf_errmsg(-1));

		if (sh.sh_type != SHT_GROUP)
			continue;

		if ((name = elf_strptr(ecp->ein, indx, sh.sh_name)) == NULL)
			errx(EXIT_FAILURE, "elf_strptr failed: %s",
			    elf_errmsg(-1));
		if (is_remove_section(ecp, name))
			continue;

		if (sh.sh_info > 0 && sh.sh_info < sc)
			BIT_SET(ecp->v_grp, sh.sh_info);
		else if (sh.sh_info != 0)
			warnx("invalid symbox index");
	}
	elferr = elf_errno();
	if (elferr != 0)
		errx(EXIT_FAILURE, "elf_nextscn failed: %s",
		    elf_errmsg(elferr));
}