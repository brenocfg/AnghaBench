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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct section {int /*<<< orphan*/  off; int /*<<< orphan*/  sz; } ;
struct elfcopy {int flags; int /*<<< orphan*/  eout; TYPE_2__* shstrtab; int /*<<< orphan*/  oem; int /*<<< orphan*/  oed; int /*<<< orphan*/  oec; } ;
struct TYPE_6__ {int /*<<< orphan*/ * os; scalar_t__ off; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_shoff; scalar_t__ e_entry; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_machine; int /*<<< orphan*/ * e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_OSABI ; 
 int /*<<< orphan*/  ELF32_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELFOSABI_NONE ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_T_EHDR ; 
 int /*<<< orphan*/  ELF_T_SHDR ; 
 int /*<<< orphan*/  ET_REL ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int RELOCATABLE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SHN_ABS ; 
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  STT_NOTYPE ; 
 int SYMTAB_EXIST ; 
 int _DATA_BUFSZ ; 
 int _LINE_BUFSZ ; 
 int /*<<< orphan*/  add_to_symtab (struct elfcopy*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_data (struct section*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  create_external_symtab (struct elfcopy*) ; 
 int /*<<< orphan*/  create_symtab_data (struct elfcopy*) ; 
 int dup (int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/ * elf_newscn (int /*<<< orphan*/ ) ; 
 scalar_t__ elf_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finalize_data_section (struct section*) ; 
 int /*<<< orphan*/  finalize_external_symtab (struct elfcopy*) ; 
 int /*<<< orphan*/  free_elf (struct elfcopy*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_fsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gelf_newehdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_update_ehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  init_shstrtab (struct elfcopy*) ; 
 struct section* insert_shtab (struct elfcopy*,int) ; 
 int /*<<< orphan*/  insert_to_sec_list (struct elfcopy*,TYPE_2__*,int) ; 
 struct section* new_data_section (struct elfcopy*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  resync_sections (struct elfcopy*) ; 
 scalar_t__ srec_read (char*,char*,scalar_t__*,int /*<<< orphan*/ *,size_t*) ; 
 int sscanf (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_shdr (struct elfcopy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
create_elf_from_srec(struct elfcopy *ecp, int ifd)
{
	char line[_LINE_BUFSZ], name[_LINE_BUFSZ];
	uint8_t data[_DATA_BUFSZ];
	GElf_Ehdr oeh;
	struct section *s, *shtab;
	FILE *ifp;
	uint64_t addr, entry, off, sec_addr;
	uintmax_t st_value;
	size_t sz;
	int _ifd, first, sec_index, in_symtab, symtab_created;
	char *rlt;
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
	sec_addr = entry = 0;
	while (fgets(line, _LINE_BUFSZ, ifp) != NULL) {
		sz = 0;
		if (line[0] == '\r' || line[0] == '\n')
			continue;
		if (line[0] == '$' && line[1] == '$') {
			ecp->flags |= SYMTAB_EXIST;
			while ((rlt = fgets(line, _LINE_BUFSZ, ifp)) != NULL) {
				if (line[0] == '$' && line[1] == '$')
					break;
			}
			if (rlt == NULL)
				break;
			continue;
		}
		if (line[0] != 'S' || line[1] < '0' || line[1] > '9') {
			warnx("Invalid srec record");
			continue;
		}
		if (srec_read(line, &type, &addr, data, &sz) < 0) {
			warnx("Invalid srec record or mismatched checksum");
			continue;
		}
		switch (type) {
		case '1':
		case '2':
		case '3':
			if (sz == 0)
				break;
			if (first || sec_addr != addr) {
				if (s != NULL)
					finalize_data_section(s);
				s = new_data_section(ecp, sec_index, off,
				    addr);
				if (s == NULL) {
					warnx("new_data_section failed");
					break;
				}
				sec_index++;
				sec_addr = addr;
				first = 0;
			}
			append_data(s, data, sz);
			off += sz;
			sec_addr += sz;
			break;
		case '7':
		case '8':
		case '9':
			entry = addr;
			break;
		default:
			break;
		}
	}
	if (s != NULL)
		finalize_data_section(s);
	if (ferror(ifp))
		warn("fgets failed");

	/* Insert .shstrtab after data sections. */
	if ((ecp->shstrtab->os = elf_newscn(ecp->eout)) == NULL)
		errx(EXIT_FAILURE, "elf_newscn failed: %s",
		    elf_errmsg(-1));
	insert_to_sec_list(ecp, ecp->shstrtab, 1);

	/* Insert section header table here. */
	shtab = insert_shtab(ecp, 1);

	/*
	 * Rescan and create symbol table if we found '$$' section in
	 * the first scan.
	 */
	symtab_created = 0;
	in_symtab = 0;
	if (ecp->flags & SYMTAB_EXIST) {
		if (fseek(ifp, 0, SEEK_SET) < 0) {
			warn("fseek failed");
			ecp->flags &= ~SYMTAB_EXIST;
			goto done;
		}
		while (fgets(line, _LINE_BUFSZ, ifp) != NULL) {
			if (in_symtab) {
				if (line[0] == '$' && line[1] == '$') {
					in_symtab = 0;
					continue;
				}
				if (sscanf(line, "%s $%jx", name,
				    &st_value) != 2) {
					warnx("Invalid symbolsrec record");
					continue;
				}
				if (!symtab_created) {
					create_external_symtab(ecp);
					symtab_created = 1;
				}
				add_to_symtab(ecp, name, st_value, 0, SHN_ABS,
				    ELF32_ST_INFO(STB_GLOBAL, STT_NOTYPE), 0, 1);
			}
			if (line[0] == '$' && line[1] == '$') {
				in_symtab = 1;
				continue;
			}
		}
	}
	if (ferror(ifp))
		warn("fgets failed");
	if (symtab_created) {
		finalize_external_symtab(ecp);
		create_symtab_data(ecp);
		/* Count in .symtab and .strtab section headers.  */
		shtab->sz += gelf_fsize(ecp->eout, ELF_T_SHDR, 2, EV_CURRENT);
	} else
		ecp->flags &= ~SYMTAB_EXIST;

done:
	fclose(ifp);

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