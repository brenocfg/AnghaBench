#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct elfcopy {int flags; int srec_len; int /*<<< orphan*/  otgt; } ;
struct TYPE_10__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  e_entry; } ;
struct TYPE_8__ {scalar_t__ sh_type; int sh_flags; scalar_t__ sh_size; int sh_addr; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_3__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int SHF_ALLOC ; 
 scalar_t__ SHT_NOBITS ; 
 scalar_t__ SHT_SYMTAB ; 
 int SREC_FORCE_LEN ; 
 int SREC_FORCE_S3 ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  srec_write_S0 (int,char const*) ; 
 int /*<<< orphan*/  srec_write_Sd (int,char,int,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  srec_write_Se (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  srec_write_symtab (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
create_srec(struct elfcopy *ecp, int ifd, int ofd, const char *ofn)
{
	Elf *e;
	Elf_Scn *scn;
	Elf_Data *d;
	GElf_Ehdr eh;
	GElf_Shdr sh;
	uint64_t max_addr;
	size_t rlen;
	int elferr, addr_sz;
	char dr;

	if ((e = elf_begin(ifd, ELF_C_READ, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin() failed: %s",
		    elf_errmsg(-1));

	/* Output a symbol table for `symbolsrec' target. */
	if (!strncmp(ecp->otgt, "symbolsrec", strlen("symbolsrec"))) {
		scn = NULL;
		while ((scn = elf_nextscn(e, scn)) != NULL) {
			if (gelf_getshdr(scn, &sh) == NULL) {
				warnx("gelf_getshdr failed: %s",
				    elf_errmsg(-1));
				(void) elf_errno();
				continue;
			}
			if (sh.sh_type != SHT_SYMTAB)
				continue;
			srec_write_symtab(ofd, ofn, e, scn, &sh);
			break;
		}
	}

	if (ecp->flags & SREC_FORCE_S3)
		dr = '3';
	else {
		/*
		 * Find maximum address size in the first iteration.
		 */
		max_addr = 0;
		scn = NULL;
		while ((scn = elf_nextscn(e, scn)) != NULL) {
			if (gelf_getshdr(scn, &sh) == NULL) {
				warnx("gelf_getshdr failed: %s",
				    elf_errmsg(-1));
				(void) elf_errno();
				continue;
			}
			if ((sh.sh_flags & SHF_ALLOC) == 0 ||
			    sh.sh_type == SHT_NOBITS ||
			    sh.sh_size == 0)
				continue;
			if ((uint64_t) sh.sh_addr > max_addr)
				max_addr = sh.sh_addr;
		}
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_nextscn failed: %s", elf_errmsg(elferr));

		if (max_addr <= 0xFFFF)
			dr = '1';
		else if (max_addr <= 0xFFFFFF)
			dr = '2';
		else
			dr = '3';
	}

	if (ecp->flags & SREC_FORCE_LEN) {
		addr_sz = dr - '0' + 1;
		if (ecp->srec_len < 1)
			rlen = 1;
		else if (ecp->srec_len + addr_sz + 1 > 255)
			rlen = 255 - (addr_sz + 1);
		else
			rlen = ecp->srec_len;
	} else
		rlen = 16;

	/* Generate S0 record which contains the output filename. */
	srec_write_S0(ofd, ofn);

	/* Generate S{1,2,3} data records for section data. */
	scn = NULL;
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		if (gelf_getshdr(scn, &sh) == NULL) {
			warnx("gelf_getshdr failed: %s", elf_errmsg(-1));
			(void) elf_errno();
			continue;
		}
		if ((sh.sh_flags & SHF_ALLOC) == 0 ||
		    sh.sh_type == SHT_NOBITS ||
		    sh.sh_size == 0)
			continue;
		if (sh.sh_addr > 0xFFFFFFFF) {
			warnx("address space too big for S-Record file");
			continue;
		}
		(void) elf_errno();
		if ((d = elf_getdata(scn, NULL)) == NULL) {
			elferr = elf_errno();
			if (elferr != 0)
				warnx("elf_getdata failed: %s", elf_errmsg(-1));
			continue;
		}
		if (d->d_buf == NULL || d->d_size == 0)
			continue;
		srec_write_Sd(ofd, dr, sh.sh_addr, d->d_buf, d->d_size, rlen);
	}
	elferr = elf_errno();
	if (elferr != 0)
		warnx("elf_nextscn failed: %s", elf_errmsg(elferr));

	/* Generate S{7,8,9} end of block record. */
	if (gelf_getehdr(e, &eh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));
	srec_write_Se(ofd, eh.e_entry, ecp->flags & SREC_FORCE_S3);
}