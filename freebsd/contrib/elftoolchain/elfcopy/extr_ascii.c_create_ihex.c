#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_9__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  e_entry; } ;
struct TYPE_7__ {int sh_flags; scalar_t__ sh_type; scalar_t__ sh_size; int sh_addr; } ;
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
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ihex_write_00 (int,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ihex_write_01 (int) ; 
 int /*<<< orphan*/  ihex_write_04 (int,int) ; 
 int /*<<< orphan*/  ihex_write_05 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
create_ihex(int ifd, int ofd)
{
	Elf *e;
	Elf_Scn *scn;
	Elf_Data *d;
	GElf_Ehdr eh;
	GElf_Shdr sh;
	int elferr;
	uint16_t addr_hi, old_addr_hi;

	if ((e = elf_begin(ifd, ELF_C_READ, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin() failed: %s",
		    elf_errmsg(-1));

	old_addr_hi = 0;
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
			warnx("address space too big for Intel Hex file");
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
		addr_hi = (sh.sh_addr >> 16) & 0xFFFF;
		if (addr_hi > 0 && addr_hi != old_addr_hi) {
			/* Write 04 record if addr_hi is new. */
			old_addr_hi = addr_hi;
			ihex_write_04(ofd, addr_hi);
		}
		ihex_write_00(ofd, sh.sh_addr, d->d_buf, d->d_size);
	}
	elferr = elf_errno();
	if (elferr != 0)
		warnx("elf_nextscn failed: %s", elf_errmsg(elferr));

	if (gelf_getehdr(e, &eh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));
	ihex_write_05(ofd, eh.e_entry);
	ihex_write_01(ofd);
}