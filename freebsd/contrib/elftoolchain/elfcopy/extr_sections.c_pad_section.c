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
struct section {scalar_t__ pad_sz; scalar_t__ sz; int /*<<< orphan*/  os; int /*<<< orphan*/ * pad; } ;
struct elfcopy {int /*<<< orphan*/  fill; } ;
struct TYPE_7__ {int d_align; scalar_t__ d_off; scalar_t__ d_size; int /*<<< orphan*/  d_version; int /*<<< orphan*/  d_type; int /*<<< orphan*/ * d_buf; } ;
struct TYPE_6__ {scalar_t__ sh_size; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_T_BYTE ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 TYPE_2__* elf_newdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gelf_update_shdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
pad_section(struct elfcopy *ecp, struct section *s)
{
	GElf_Shdr	 osh;
	Elf_Data	*od;

	if (s == NULL || s->pad_sz == 0)
		return;

	if ((s->pad = malloc(s->pad_sz)) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	memset(s->pad, ecp->fill, s->pad_sz);

	/* Create a new Elf_Data to contain the padding bytes. */
	if ((od = elf_newdata(s->os)) == NULL)
		errx(EXIT_FAILURE, "elf_newdata() failed: %s",
		    elf_errmsg(-1));
	od->d_align = 1;
	od->d_off = s->sz;
	od->d_buf = s->pad;
	od->d_type = ELF_T_BYTE;
	od->d_size = s->pad_sz;
	od->d_version = EV_CURRENT;

	/* Update section header. */
	if (gelf_getshdr(s->os, &osh) == NULL)
		errx(EXIT_FAILURE, "gelf_getshdr() failed: %s",
		    elf_errmsg(-1));
	osh.sh_size = s->sz + s->pad_sz;
	if (!gelf_update_shdr(s->os, &osh))
		errx(EXIT_FAILURE, "elf_update_shdr failed: %s",
		    elf_errmsg(-1));
}