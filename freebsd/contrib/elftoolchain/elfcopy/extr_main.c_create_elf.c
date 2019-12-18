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
struct section {int /*<<< orphan*/  off; } ;
struct elfcopy {int flags; scalar_t__ iec; scalar_t__ oec; scalar_t__ oed; int abi; scalar_t__ strip; scalar_t__ ophnum; scalar_t__ change_addr; scalar_t__ change_start; int /*<<< orphan*/  eout; int /*<<< orphan*/  set_start; int /*<<< orphan*/  v_symop; int /*<<< orphan*/ * prefix_sym; int /*<<< orphan*/ * secndx; int /*<<< orphan*/  ein; } ;
struct TYPE_4__ {scalar_t__* e_ident; scalar_t__ e_type; scalar_t__ e_phoff; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_shoff; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_flags; } ;
typedef  TYPE_1__ GElf_Ehdr ;

/* Variables and functions */
 int DISCARD_LLABEL ; 
 int DISCARD_LOCAL ; 
 int DYNAMIC ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_OSABI ; 
 scalar_t__ ELFCLASSNONE ; 
 scalar_t__ ELFDATANONE ; 
 int ELFOSABI_FREEBSD ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_T_EHDR ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ ET_REL ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int EXECUTABLE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LOCALIZE_HIDDEN ; 
 int RELOCATABLE ; 
 int SET_START ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ STRIP_DEBUG ; 
 scalar_t__ STRIP_UNNEEDED ; 
 int SYMTAB_EXIST ; 
 int SYMTAB_INTACT ; 
 int WEAKEN_ALL ; 
 int /*<<< orphan*/  adjust_addr (struct elfcopy*) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  copy_content (struct elfcopy*) ; 
 int /*<<< orphan*/  copy_phdr (struct elfcopy*) ; 
 int /*<<< orphan*/  create_scn (struct elfcopy*) ; 
 int /*<<< orphan*/  create_symtab (struct elfcopy*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_getshnum (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ elf_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_elf (struct elfcopy*) ; 
 scalar_t__ gelf_fsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_getclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gelf_newehdr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gelf_update_ehdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct section* insert_shtab (struct elfcopy*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  resync_sections (struct elfcopy*) ; 
 int /*<<< orphan*/  setup_phdr (struct elfcopy*) ; 
 int /*<<< orphan*/  update_shdr (struct elfcopy*,int) ; 

void
create_elf(struct elfcopy *ecp)
{
	struct section	*shtab;
	GElf_Ehdr	 ieh;
	GElf_Ehdr	 oeh;
	size_t		 ishnum;

	ecp->flags |= SYMTAB_INTACT;
	ecp->flags &= ~SYMTAB_EXIST;

	/* Create EHDR. */
	if (gelf_getehdr(ecp->ein, &ieh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));
	if ((ecp->iec = gelf_getclass(ecp->ein)) == ELFCLASSNONE)
		errx(EXIT_FAILURE, "getclass() failed: %s",
		    elf_errmsg(-1));

	if (ecp->oec == ELFCLASSNONE)
		ecp->oec = ecp->iec;
	if (ecp->oed == ELFDATANONE)
		ecp->oed = ieh.e_ident[EI_DATA];

	if (gelf_newehdr(ecp->eout, ecp->oec) == NULL)
		errx(EXIT_FAILURE, "gelf_newehdr failed: %s",
		    elf_errmsg(-1));
	if (gelf_getehdr(ecp->eout, &oeh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));

	memcpy(oeh.e_ident, ieh.e_ident, sizeof(ieh.e_ident));
	oeh.e_ident[EI_CLASS] = ecp->oec;
	oeh.e_ident[EI_DATA]  = ecp->oed;
	if (ecp->abi != -1)
		oeh.e_ident[EI_OSABI] = ecp->abi;
	oeh.e_flags	      = ieh.e_flags;
	oeh.e_machine	      = ieh.e_machine;
	oeh.e_type	      = ieh.e_type;
	oeh.e_entry	      = ieh.e_entry;
	oeh.e_version	      = ieh.e_version;

	ecp->flags &= ~(EXECUTABLE | DYNAMIC | RELOCATABLE);
	if (ieh.e_type == ET_EXEC)
		ecp->flags |= EXECUTABLE;
	else if (ieh.e_type == ET_DYN)
		ecp->flags |= DYNAMIC;
	else if (ieh.e_type == ET_REL)
		ecp->flags |= RELOCATABLE;
	else
		errx(EXIT_FAILURE, "unsupported e_type");

	if (!elf_getshnum(ecp->ein, &ishnum))
		errx(EXIT_FAILURE, "elf_getshnum failed: %s",
		    elf_errmsg(-1));
	if (ishnum > 0 && (ecp->secndx = calloc(ishnum,
	    sizeof(*ecp->secndx))) == NULL)
		err(EXIT_FAILURE, "calloc failed");

	/* Read input object program header. */
	setup_phdr(ecp);

	/*
	 * Scan of input sections: we iterate through sections from input
	 * object, skip sections need to be stripped, allot Elf_Scn and
	 * create internal section structure for sections we want.
	 * (i.e., determine output sections)
	 */
	create_scn(ecp);

	/* Apply section address changes, if any. */
	adjust_addr(ecp);

	/*
	 * Determine if the symbol table needs to be changed based on
	 * command line options.
	 */
	if (ecp->strip == STRIP_DEBUG ||
	    ecp->strip == STRIP_UNNEEDED ||
	    ecp->flags & WEAKEN_ALL ||
	    ecp->flags & LOCALIZE_HIDDEN ||
	    ecp->flags & DISCARD_LOCAL ||
	    ecp->flags & DISCARD_LLABEL ||
	    ecp->prefix_sym != NULL ||
	    !STAILQ_EMPTY(&ecp->v_symop))
		ecp->flags &= ~SYMTAB_INTACT;

	/*
	 * Create symbol table. Symbols are filtered or stripped according to
	 * command line args specified by user, and later updated for the new
	 * layout of sections in the output object.
	 */
	if ((ecp->flags & SYMTAB_EXIST) != 0)
		create_symtab(ecp);

	/*
	 * Write the underlying ehdr. Note that it should be called
	 * before elf_setshstrndx() since it will overwrite e->e_shstrndx.
	 */
	if (gelf_update_ehdr(ecp->eout, &oeh) == 0)
		errx(EXIT_FAILURE, "gelf_update_ehdr() failed: %s",
		    elf_errmsg(-1));

	/*
	 * First processing of output sections: at this stage we copy the
	 * content of each section from input to output object.  Section
	 * content will be modified and printed (mcs) if need. Also content of
	 * relocation section probably will be filtered and updated according
	 * to symbol table changes.
	 */
	copy_content(ecp);

	/*
	 * Second processing of output sections: Update section headers.
	 * At this stage we set name string index, update st_link and st_info
	 * for output sections.
	 */
	update_shdr(ecp, 1);

	/* Renew oeh to get the updated e_shstrndx. */
	if (gelf_getehdr(ecp->eout, &oeh) == NULL)
		errx(EXIT_FAILURE, "gelf_getehdr() failed: %s",
		    elf_errmsg(-1));

	/*
	 * Insert SHDR table into the internal section list as a "pseudo"
	 * section, so later it will get sorted and resynced just as "normal"
	 * sections.
	 *
	 * Under FreeBSD, Binutils objcopy always put the section header
	 * at the end of all the sections. We want to do the same here.
	 *
	 * However, note that the behaviour is still different with Binutils:
	 * elfcopy checks the FreeBSD OSABI tag to tell whether it needs to
	 * move the section headers, while Binutils is probably configured
	 * this way when it's compiled on FreeBSD.
	 */
	if (oeh.e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		shtab = insert_shtab(ecp, 1);
	else
		shtab = insert_shtab(ecp, 0);

	/*
	 * Resync section offsets in the output object. This is needed
	 * because probably sections are modified or new sections are added,
	 * as a result overlap/gap might appears.
	 */
	resync_sections(ecp);

	/* Store SHDR offset in EHDR. */
	oeh.e_shoff = shtab->off;

	/* Put program header table immediately after the Elf header. */
	if (ecp->ophnum > 0) {
		oeh.e_phoff = gelf_fsize(ecp->eout, ELF_T_EHDR, 1, EV_CURRENT);
		if (oeh.e_phoff == 0)
			errx(EXIT_FAILURE, "gelf_fsize() failed: %s",
			    elf_errmsg(-1));
	}

	/*
	 * Update ELF object entry point if requested.
	 */
	if (ecp->change_addr != 0)
		oeh.e_entry += ecp->change_addr;
	if (ecp->flags & SET_START)
		oeh.e_entry = ecp->set_start;
	if (ecp->change_start != 0)
		oeh.e_entry += ecp->change_start;

	/*
	 * Update ehdr again before we call elf_update(), since we
	 * modified e_shoff and e_phoff.
	 */
	if (gelf_update_ehdr(ecp->eout, &oeh) == 0)
		errx(EXIT_FAILURE, "gelf_update_ehdr() failed: %s",
		    elf_errmsg(-1));

	if (ecp->ophnum > 0)
		copy_phdr(ecp);

	/* Write out the output elf object. */
	if (elf_update(ecp->eout, ELF_C_WRITE) < 0)
		errx(EXIT_FAILURE, "elf_update() failed: %s",
		    elf_errmsg(-1));

	/* Release allocated resource. */
	free_elf(ecp);
}