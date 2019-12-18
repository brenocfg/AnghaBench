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
struct section {char* name; int align; int /*<<< orphan*/  strtab; scalar_t__ vma; int /*<<< orphan*/  type; scalar_t__ loadable; scalar_t__ sz; int /*<<< orphan*/ * is; } ;
struct elfcopy {struct section* shstrtab; int /*<<< orphan*/  ein; } ;
struct TYPE_4__ {size_t sh_size; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SHT_STRTAB ; 
 int /*<<< orphan*/  add_to_shstrtab (struct elfcopy*,char*) ; 
 struct section* calloc (int,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_errno () ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ elf_getshdrstrndx (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  elftc_string_table_create (size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
init_shstrtab(struct elfcopy *ecp)
{
	Elf_Scn *shstrtab;
	GElf_Shdr shdr;
	struct section *s;
	size_t indx, sizehint;

	if (elf_getshdrstrndx(ecp->ein, &indx) == 0) {
		shstrtab = elf_getscn(ecp->ein, indx);
		if (shstrtab == NULL)
			errx(EXIT_FAILURE, "elf_getscn failed: %s",
			    elf_errmsg(-1));
		if (gelf_getshdr(shstrtab, &shdr) != &shdr)
			errx(EXIT_FAILURE, "gelf_getshdr failed: %s",
			    elf_errmsg(-1));
		sizehint = shdr.sh_size;
	} else {
		/* Clear the error from elf_getshdrstrndx(3). */
		(void)elf_errno();
		sizehint = 0;
	}

	if ((ecp->shstrtab = calloc(1, sizeof(*ecp->shstrtab))) == NULL)
		err(EXIT_FAILURE, "calloc failed");
	s = ecp->shstrtab;
	s->name = ".shstrtab";
	s->is = NULL;
	s->sz = 0;
	s->align = 1;
	s->loadable = 0;
	s->type = SHT_STRTAB;
	s->vma = 0;
	s->strtab = elftc_string_table_create(sizehint);

	add_to_shstrtab(ecp, "");
	add_to_shstrtab(ecp, ".symtab");
	add_to_shstrtab(ecp, ".strtab");
	add_to_shstrtab(ecp, ".shstrtab");
}