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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct section {int /*<<< orphan*/  off; } ;
struct elfcopy {int /*<<< orphan*/  eout; TYPE_2__* shstrtab; int /*<<< orphan*/  flags; int /*<<< orphan*/  oem; int /*<<< orphan*/  oed; int /*<<< orphan*/  oec; } ;
struct TYPE_6__ {int /*<<< orphan*/ * os; scalar_t__ off; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_shoff; scalar_t__ e_entry; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_machine; int /*<<< orphan*/ * e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_OSABI ; 
 int /*<<< orphan*/  ELFOSABI_NONE ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_T_EHDR ; 
 int /*<<< orphan*/  ET_REL ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  RELOCATABLE ; 
 int _DATA_BUFSZ ; 
 int _LINE_BUFSZ ; 
 int /*<<< orphan*/  append_data (struct section*,int /*<<< orphan*/ *,size_t) ; 
 int dup (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/ * elf_newscn (int /*<<< orphan*/ ) ; 
 scalar_t__ elf_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finalize_data_section (struct section*) ; 
 int /*<<< orphan*/  free_elf (struct elfcopy*) ; 
 scalar_t__ gelf_fsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gelf_newehdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_update_ehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ihex_read (char*,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  init_shstrtab (struct elfcopy*) ; 
 struct section* insert_shtab (struct elfcopy*,int) ; 
 int /*<<< orphan*/  insert_to_sec_list (struct elfcopy*,TYPE_2__*,int) ; 
 struct section* new_data_section (struct elfcopy*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  resync_sections (struct elfcopy*) ; 
 int /*<<< orphan*/  update_shdr (struct elfcopy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
create_elf_from_ihex(struct elfcopy *ecp, int ifd)
{
	char line[_LINE_BUFSZ];
	uint8_t data[_DATA_BUFSZ];
	GElf_Ehdr oeh;
	struct section *s, *shtab;
	FILE *ifp;
	uint64_t addr, addr_base, entry, num, off, rec_addr, sec_addr;
	size_t sz;
	int _ifd, first, sec_index;
	char type;

	if ((_ifd = dup(ifd)) < 0)
		err(EXIT_FAILURE, "dup failed");
	if ((ifp = fdopen(_ifd, "r")) == NULL)
		err(EXIT_FAILURE, "fdopen failed");

	/* Create EHDR for output .o file. */
	if (gelf_newehdr(ecp->eout, ecp->oec) == NULL)
		errx(EXIT_FAILURE, "gelf_newehdr failed: %s",
		    elf_errmsg(-1));
	if (gelf_getehdr(ecp->eout, &oeh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));

	/* Initialise e_ident fields. */
	oeh.e_ident[EI_CLASS] = ecp->oec;
	oeh.e_ident[EI_DATA] = ecp->oed;
	/*
	 * TODO: Set OSABI according to the OS platform where elfcopy(1)
	 * was build. (probably)
	 */
	oeh.e_ident[EI_OSABI] = ELFOSABI_NONE;
	oeh.e_machine = ecp->oem;
	oeh.e_type = ET_REL;
	oeh.e_entry = 0;

	ecp->flags |= RELOCATABLE;

	/* Create .shstrtab section */
	init_shstrtab(ecp);
	ecp->shstrtab->off = 0;

	/* Data sections are inserted after EHDR. */
	off = gelf_fsize(ecp->eout, ELF_T_EHDR, 1, EV_CURRENT);
	if (off == 0)
		errx(EXIT_FAILURE, "gelf_fsize() failed: %s", elf_errmsg(-1));

	/* Create data sections. */
	s = NULL;
	first = 1;
	sec_index = 1;
	addr_base = rec_addr = sec_addr = entry = 0;
	while (fgets(line, _LINE_BUFSZ, ifp) != NULL) {
		if (line[0] == '\r' || line[0] == '\n')
			continue;
		if (line[0] != ':') {
			warnx("Invalid ihex record");
			continue;
		}
		if (ihex_read(line, &type, &addr, &num, data, &sz) < 0) {
			warnx("Invalid ihex record or mismatched checksum");
			continue;
		}
		switch (type) {
		case '0':
			/* Data record. */
			if (sz == 0)
				break;
			rec_addr = addr_base + addr;
			if (first || sec_addr != rec_addr) {
				if (s != NULL)
					finalize_data_section(s);
				s = new_data_section(ecp, sec_index, off,
				    rec_addr);
				if (s == NULL) {
					warnx("new_data_section failed");
					break;
				}
				sec_index++;
				sec_addr = rec_addr;
				first = 0;
			}
			append_data(s, data, sz);
			off += sz;
			sec_addr += sz;
			break;
		case '1':
			/* End of file record. */
			goto done;
		case '2':
			/* Extended segment address record. */
			addr_base = addr << 4;
			break;
		case '3':
			/* Start segment address record (CS:IP). Ignored. */
			break;
		case '4':
			/* Extended linear address record. */
			addr_base = num << 16;
			break;
		case '5':
			/* Start linear address record. */
			entry = num;
			break;
		default:
			break;
		}
	}
done:
	if (s != NULL)
		finalize_data_section(s);
	if (ferror(ifp))
		warn("fgets failed");
	fclose(ifp);

	/* Insert .shstrtab after data sections. */
	if ((ecp->shstrtab->os = elf_newscn(ecp->eout)) == NULL)
		errx(EXIT_FAILURE, "elf_newscn failed: %s",
		    elf_errmsg(-1));
	insert_to_sec_list(ecp, ecp->shstrtab, 1);

	/* Insert section header table here. */
	shtab = insert_shtab(ecp, 1);

	/* Set entry point. */
	oeh.e_entry = entry;

	/*
	 * Write the underlying ehdr. Note that it should be called
	 * before elf_setshstrndx() since it will overwrite e->e_shstrndx.
	 */
	if (gelf_update_ehdr(ecp->eout, &oeh) == 0)
		errx(EXIT_FAILURE, "gelf_update_ehdr() failed: %s",
		    elf_errmsg(-1));

	/* Update sh_name pointer for each section header entry. */
	update_shdr(ecp, 0);

	/* Renew oeh to get the updated e_shstrndx. */
	if (gelf_getehdr(ecp->eout, &oeh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));

	/* Resync section offsets. */
	resync_sections(ecp);

	/* Store SHDR offset in EHDR. */
	oeh.e_shoff = shtab->off;

	/* Update ehdr since we modified e_shoff. */
	if (gelf_update_ehdr(ecp->eout, &oeh) == 0)
		errx(EXIT_FAILURE, "gelf_update_ehdr() failed: %s",
		    elf_errmsg(-1));

	/* Write out the output elf object. */
	if (elf_update(ecp->eout, ELF_C_WRITE) < 0)
		errx(EXIT_FAILURE, "elf_update() failed: %s",
		    elf_errmsg(-1));

	/* Release allocated resource. */
	free_elf(ecp);
}