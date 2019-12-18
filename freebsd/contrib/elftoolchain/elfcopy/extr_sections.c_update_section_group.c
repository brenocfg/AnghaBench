#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct section {size_t* buf; int sz; int nocopy; int /*<<< orphan*/  is; } ;
struct elfcopy {scalar_t__* secndx; int /*<<< orphan*/  ein; } ;
struct TYPE_6__ {size_t* d_buf; } ;
struct TYPE_5__ {int sh_size; int sh_entsize; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t GRP_COMDAT ; 
 size_t SHN_UNDEF ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_2__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_getshnum (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t* malloc (int) ; 

__attribute__((used)) static void
update_section_group(struct elfcopy *ecp, struct section *s)
{
	GElf_Shdr	 ish;
	Elf_Data	*id;
	uint32_t	*ws, *wd;
	uint64_t	 n;
	size_t		 ishnum;
	int		 i, j;

	if (!elf_getshnum(ecp->ein, &ishnum))
		errx(EXIT_FAILURE, "elf_getshnum failed: %s",
		    elf_errmsg(-1));

	if (gelf_getshdr(s->is, &ish) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));

	if ((id = elf_getdata(s->is, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_getdata() failed: %s",
		    elf_errmsg(-1));

	if (ish.sh_size == 0)
		return;

	if (ish.sh_entsize == 0)
		ish.sh_entsize = 4;

	ws = id->d_buf;

	/* We only support COMDAT section. */
#ifndef GRP_COMDAT
#define	GRP_COMDAT 0x1
#endif
	if ((*ws & GRP_COMDAT) == 0)
		return;

	if ((s->buf = malloc(ish.sh_size)) == NULL)
		err(EXIT_FAILURE, "malloc failed");

	s->sz = ish.sh_size;

	wd = s->buf;

	/* Copy the flag word as-is. */
	*wd = *ws;

	/* Update the section indices. */
	n = ish.sh_size / ish.sh_entsize;
	for(i = 1, j = 1; (uint64_t)i < n; i++) {
		if (ws[i] != SHN_UNDEF && ws[i] < ishnum &&
		    ecp->secndx[ws[i]] != 0)
			wd[j++] = ecp->secndx[ws[i]];
		else
			s->sz -= 4;
	}

	s->nocopy = 1;
}