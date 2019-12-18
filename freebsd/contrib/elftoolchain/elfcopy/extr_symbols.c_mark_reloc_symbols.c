#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct elfcopy {int /*<<< orphan*/ * v_rel; TYPE_1__* symtab; int /*<<< orphan*/  ein; } ;
struct TYPE_20__ {int d_size; } ;
struct TYPE_19__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_18__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_17__ {scalar_t__ sh_type; scalar_t__ sh_link; size_t sh_size; int sh_entsize; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_name; } ;
struct TYPE_16__ {int /*<<< orphan*/  is; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  TYPE_3__ GElf_Rela ;
typedef  TYPE_4__ GElf_Rel ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_5__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t GELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_5__* elf_getdata (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ elf_getshstrndx (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ elf_ndxscn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* gelf_getrel (TYPE_5__*,int,TYPE_4__*) ; 
 TYPE_3__* gelf_getrela (TYPE_5__*,int,TYPE_3__*) ; 
 TYPE_2__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ is_remove_reloc_sec (struct elfcopy*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_remove_section (struct elfcopy*,char const*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
mark_reloc_symbols(struct elfcopy *ecp, size_t sc)
{
	const char	*name;
	Elf_Data	*d;
	Elf_Scn		*s;
	GElf_Rel	 r;
	GElf_Rela	 ra;
	GElf_Shdr	 sh;
	size_t		 n, indx;
	int		 elferr, i, len;

	ecp->v_rel = calloc((sc + 7) / 8, 1);
	if (ecp->v_rel == NULL)
		err(EXIT_FAILURE, "calloc failed");

	if (elf_getshstrndx(ecp->ein, &indx) == 0)
		errx(EXIT_FAILURE, "elf_getshstrndx failed: %s",
		    elf_errmsg(-1));

	s = NULL;
	while ((s = elf_nextscn(ecp->ein, s)) != NULL) {
		if (gelf_getshdr(s, &sh) != &sh)
			errx(EXIT_FAILURE, "elf_getshdr failed: %s",
			    elf_errmsg(-1));

		if (sh.sh_type != SHT_REL && sh.sh_type != SHT_RELA)
			continue;

		/*
		 * Skip if this reloc section won't appear in the
		 * output object.
		 */
		if ((name = elf_strptr(ecp->ein, indx, sh.sh_name)) == NULL)
			errx(EXIT_FAILURE, "elf_strptr failed: %s",
			    elf_errmsg(-1));
		if (is_remove_section(ecp, name) ||
		    is_remove_reloc_sec(ecp, sh.sh_info))
			continue;

		/* Skip if it's not for .symtab */
		if (sh.sh_link != elf_ndxscn(ecp->symtab->is))
			continue;

		d = NULL;
		n = 0;
		while (n < sh.sh_size && (d = elf_getdata(s, d)) != NULL) {
			len = d->d_size / sh.sh_entsize;
			for (i = 0; i < len; i++) {
				if (sh.sh_type == SHT_REL) {
					if (gelf_getrel(d, i, &r) != &r)
						errx(EXIT_FAILURE,
						    "elf_getrel failed: %s",
						     elf_errmsg(-1));
					n = GELF_R_SYM(r.r_info);
				} else {
					if (gelf_getrela(d, i, &ra) != &ra)
						errx(EXIT_FAILURE,
						    "elf_getrela failed: %s",
						     elf_errmsg(-1));
					n = GELF_R_SYM(ra.r_info);
				}
				if (n > 0 && n < sc)
					BIT_SET(ecp->v_rel, n);
				else if (n != 0)
					warnx("invalid symbox index");
			}
		}
		elferr = elf_errno();
		if (elferr != 0)
			errx(EXIT_FAILURE, "elf_getdata failed: %s",
			    elf_errmsg(elferr));
	}
	elferr = elf_errno();
	if (elferr != 0)
		errx(EXIT_FAILURE, "elf_nextscn failed: %s",
		    elf_errmsg(elferr));
}