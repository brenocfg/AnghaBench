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
typedef  scalar_t__ uint64_t ;
struct section {int align; int pseudo; int loadable; char const* name; scalar_t__ type; int flags; int /*<<< orphan*/ * os; scalar_t__ off; int /*<<< orphan*/  vma; scalar_t__ sz; int /*<<< orphan*/ * is; } ;
struct elfcopy {int ophnum; scalar_t__ strip; int flags; struct section* strtab; struct section* symtab; scalar_t__* secndx; int /*<<< orphan*/  eout; int /*<<< orphan*/ * debuglink; struct section* shstrtab; int /*<<< orphan*/  ein; } ;
struct TYPE_3__ {scalar_t__ sh_type; scalar_t__ sh_info; int sh_addralign; int sh_flags; scalar_t__ sh_offset; int /*<<< orphan*/  sh_addr; scalar_t__ sh_size; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_T_EHDR ; 
 int /*<<< orphan*/  ELF_T_PHDR ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int RELOCATABLE ; 
 int SEC_ADD ; 
 int SF_ALLOC ; 
 int SF_LOAD ; 
 int SHF_ALLOC ; 
 int SHF_GROUP ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ SHT_GROUP ; 
 scalar_t__ SHT_NOBITS ; 
 scalar_t__ SHT_NOTE ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 scalar_t__ STRIP_ALL ; 
 scalar_t__ STRIP_NONDEBUG ; 
 int SYMTAB_EXIST ; 
 int SYMTAB_INTACT ; 
 int /*<<< orphan*/  add_gnu_debuglink (struct elfcopy*) ; 
 void* add_to_inseg_list (struct elfcopy*,struct section*) ; 
 struct section* calloc (int,int) ; 
 int /*<<< orphan*/  check_section_rename (struct elfcopy*,struct section*) ; 
 int /*<<< orphan*/  copy_shdr (struct elfcopy*,struct section*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 scalar_t__ elf_getshstrndx (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ elf_ndxscn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_newscn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_fsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int get_section_flags (struct elfcopy*,char const*) ; 
 int /*<<< orphan*/  init_shstrtab (struct elfcopy*) ; 
 int /*<<< orphan*/  insert_sections (struct elfcopy*) ; 
 int /*<<< orphan*/  insert_to_sec_list (struct elfcopy*,struct section*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_remove_reloc_sec (struct elfcopy*,scalar_t__) ; 
 scalar_t__ is_remove_section (struct elfcopy*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
create_scn(struct elfcopy *ecp)
{
	struct section	*s;
	const char	*name;
	Elf_Scn		*is;
	GElf_Shdr	 ish;
	size_t		 indx;
	uint64_t	 oldndx, newndx;
	int		 elferr, sec_flags, reorder;

	/*
	 * Insert a pseudo section that contains the ELF header
	 * and program header. Used as reference for section offset
	 * or load address adjustment.
	 */
	if ((s = calloc(1, sizeof(*s))) == NULL)
		err(EXIT_FAILURE, "calloc failed");
	s->off = 0;
	s->sz = gelf_fsize(ecp->eout, ELF_T_EHDR, 1, EV_CURRENT) +
	    gelf_fsize(ecp->eout, ELF_T_PHDR, ecp->ophnum, EV_CURRENT);
	s->align = 1;
	s->pseudo = 1;
	s->loadable = add_to_inseg_list(ecp, s);
	insert_to_sec_list(ecp, s, 0);

	/* Create internal .shstrtab section. */
	init_shstrtab(ecp);

	if (elf_getshstrndx(ecp->ein, &indx) == 0)
		errx(EXIT_FAILURE, "elf_getshstrndx failed: %s",
		    elf_errmsg(-1));

	reorder = 0;
	is = NULL;
	while ((is = elf_nextscn(ecp->ein, is)) != NULL) {
		if (gelf_getshdr(is, &ish) == NULL)
			errx(EXIT_FAILURE, "gelf_getshdr failed: %s",
			    elf_errmsg(-1));
		if ((name = elf_strptr(ecp->ein, indx, ish.sh_name)) == NULL)
			errx(EXIT_FAILURE, "elf_strptr failed: %s",
			    elf_errmsg(-1));

		/* Skip sections to be removed. */
		if (is_remove_section(ecp, name))
			continue;

		/*
		 * Relocation section need to be remove if the section
		 * it applies will be removed.
		 */
		if (ish.sh_type == SHT_REL || ish.sh_type == SHT_RELA)
			if (ish.sh_info != 0 &&
			    is_remove_reloc_sec(ecp, ish.sh_info))
				continue;

		/*
		 * Section groups should be removed if symbol table will
		 * be removed. (section group's signature stored in symbol
		 * table)
		 */
		if (ish.sh_type == SHT_GROUP && ecp->strip == STRIP_ALL)
			continue;

		/* Get section flags set by user. */
		sec_flags = get_section_flags(ecp, name);

		/* Create internal section object. */
		if (strcmp(name, ".shstrtab") != 0) {
			if ((s = calloc(1, sizeof(*s))) == NULL)
				err(EXIT_FAILURE, "calloc failed");
			s->name		= name;
			s->is		= is;
			s->off		= ish.sh_offset;
			s->sz		= ish.sh_size;
			s->align	= ish.sh_addralign;
			s->type		= ish.sh_type;
			s->flags	= ish.sh_flags;
			s->vma		= ish.sh_addr;

			/*
			 * Search program headers to determine whether section
			 * is loadable, but if user explicitly set section flags
			 * while neither "load" nor "alloc" is set, we make the
			 * section unloadable.
			 *
			 * Sections in relocatable object is loadable if
			 * section flag SHF_ALLOC is set.
			 */
			if (sec_flags &&
			    (sec_flags & (SF_LOAD | SF_ALLOC)) == 0)
				s->loadable = 0;
			else {
				s->loadable = add_to_inseg_list(ecp, s);
				if ((ecp->flags & RELOCATABLE) &&
				    (ish.sh_flags & SHF_ALLOC))
					s->loadable = 1;
			}
		} else {
			/* Assuming .shstrtab is "unloadable". */
			s		= ecp->shstrtab;
			s->off		= ish.sh_offset;
		}

		oldndx = newndx = SHN_UNDEF;
		if (strcmp(name, ".symtab") != 0 &&
		    strcmp(name, ".strtab") != 0) {
			if (!strcmp(name, ".shstrtab")) {
				/*
				 * Add sections specified by --add-section and
				 * gnu debuglink. we want these sections have
				 * smaller index than .shstrtab section.
				 */
				if (ecp->debuglink != NULL)
					add_gnu_debuglink(ecp);
				if (ecp->flags & SEC_ADD)
					insert_sections(ecp);
			}
 			if ((s->os = elf_newscn(ecp->eout)) == NULL)
				errx(EXIT_FAILURE, "elf_newscn failed: %s",
				    elf_errmsg(-1));
			if ((newndx = elf_ndxscn(s->os)) == SHN_UNDEF)
				errx(EXIT_FAILURE, "elf_ndxscn failed: %s",
				    elf_errmsg(-1));
		}
		if ((oldndx = elf_ndxscn(is)) == SHN_UNDEF)
			errx(EXIT_FAILURE, "elf_ndxscn failed: %s",
			    elf_errmsg(-1));
		if (oldndx != SHN_UNDEF && newndx != SHN_UNDEF)
			ecp->secndx[oldndx] = newndx;

		/*
		 * If strip action is STRIP_NONDEBUG(only keep debug),
		 * change sections type of loadable sections and section
		 * groups to SHT_NOBITS, and the content of those sections
		 * will be discarded. However, SHT_NOTE sections should
		 * be kept.
		 */
		if (ecp->strip == STRIP_NONDEBUG) {
			if (((ish.sh_flags & SHF_ALLOC) ||
			    (ish.sh_flags & SHF_GROUP)) &&
			    ish.sh_type != SHT_NOTE)
				s->type = SHT_NOBITS;
		}

		check_section_rename(ecp, s);

		/* create section header based on input object. */
		if (strcmp(name, ".symtab") != 0 &&
		    strcmp(name, ".strtab") != 0 &&
		    strcmp(name, ".shstrtab") != 0) {
			copy_shdr(ecp, s, NULL, 0, sec_flags);
			/*
			 * elfcopy puts .symtab, .strtab and .shstrtab
			 * sections in the end of the output object.
			 * If the input objects have more sections
			 * after any of these 3 sections, the section
			 * table will be reordered. section symbols
			 * should be regenerated for relocations.
			 */
			if (reorder)
				ecp->flags &= ~SYMTAB_INTACT;
		} else
			reorder = 1;

		if (strcmp(name, ".symtab") == 0) {
			ecp->flags |= SYMTAB_EXIST;
			ecp->symtab = s;
		}
		if (strcmp(name, ".strtab") == 0)
			ecp->strtab = s;

		insert_to_sec_list(ecp, s, 0);
	}
	elferr = elf_errno();
	if (elferr != 0)
		errx(EXIT_FAILURE, "elf_nextscn failed: %s",
		    elf_errmsg(elferr));
}