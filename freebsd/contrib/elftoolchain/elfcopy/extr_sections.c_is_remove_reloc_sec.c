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
typedef  int /*<<< orphan*/  uint32_t ;
struct elfcopy {int /*<<< orphan*/  ein; } ;
struct TYPE_3__ {int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_getshstrndx (int /*<<< orphan*/ ,size_t*) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ is_remove_section (struct elfcopy*,char const*) ; 

int
is_remove_reloc_sec(struct elfcopy *ecp, uint32_t sh_info)
{
	const char	*name;
	GElf_Shdr	 ish;
	Elf_Scn		*is;
	size_t		 indx;
	int		 elferr;

	if (elf_getshstrndx(ecp->ein, &indx) == 0)
		errx(EXIT_FAILURE, "elf_getshstrndx failed: %s",
		    elf_errmsg(-1));

	is = elf_getscn(ecp->ein, sh_info);
	if (is != NULL) {
		if (gelf_getshdr(is, &ish) == NULL)
			errx(EXIT_FAILURE, "gelf_getshdr failed: %s",
			    elf_errmsg(-1));
		if ((name = elf_strptr(ecp->ein, indx, ish.sh_name)) ==
		    NULL)
			errx(EXIT_FAILURE, "elf_strptr failed: %s",
			    elf_errmsg(-1));
		if (is_remove_section(ecp, name))
			return (1);
		else
			return (0);
	}
	elferr = elf_errno();
	if (elferr != 0)
		errx(EXIT_FAILURE, "elf_nextscn failed: %s",
		    elf_errmsg(elferr));

	/* Remove reloc section if we can't find the target section. */
	return (1);
}