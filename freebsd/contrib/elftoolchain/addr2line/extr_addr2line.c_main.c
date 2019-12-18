#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  Elf ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_MMAP_R ; 
 int /*<<< orphan*/  DW_DLC_READ ; 
 scalar_t__ DW_DLV_OK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _IOLBF ; 
 int base ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ ) ; 
 int demangle ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_get_elf (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_init (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_section_base (char const*,int /*<<< orphan*/ *,char const*) ; 
 int func ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int inlines ; 
 int /*<<< orphan*/  longopts ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int pretty_print ; 
 int print_addr ; 
 scalar_t__ section_base ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  translate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  version () ; 

int
main(int argc, char **argv)
{
	cap_rights_t rights;
	Elf *e;
	Dwarf_Debug dbg;
	Dwarf_Error de;
	const char *exe, *section;
	char line[1024];
	int fd, i, opt;

	exe = NULL;
	section = NULL;
	while ((opt = getopt_long(argc, argv, "ab:Ce:fij:psHV", longopts,
	    NULL)) != -1) {
		switch (opt) {
		case 'a':
			print_addr = 1;
			break;
		case 'b':
			/* ignored */
			break;
		case 'C':
			demangle = 1;
			break;
		case 'e':
			exe = optarg;
			break;
		case 'f':
			func = 1;
			break;
		case 'i':
			inlines = 1;
			break;
		case 'j':
			section = optarg;
			break;
		case 'p':
			pretty_print = 1;
			break;
		case 's':
			base = 1;
			break;
		case 'H':
			usage();
		case 'V':
			version();
		default:
			usage();
		}
	}

	argv += optind;
	argc -= optind;

	if (exe == NULL)
		exe = "a.out";

	if ((fd = open(exe, O_RDONLY)) < 0)
		err(EXIT_FAILURE, "%s", exe);

	if (caph_rights_limit(fd, cap_rights_init(&rights, CAP_FSTAT,
	    CAP_MMAP_R)) < 0)
		errx(EXIT_FAILURE, "caph_rights_limit");

	caph_cache_catpages();
	if (caph_limit_stdio() < 0)
		errx(EXIT_FAILURE, "failed to limit stdio rights");
	if (caph_enter() < 0)
		errx(EXIT_FAILURE, "failed to enter capability mode");

	if (dwarf_init(fd, DW_DLC_READ, NULL, NULL, &dbg, &de))
		errx(EXIT_FAILURE, "dwarf_init: %s", dwarf_errmsg(de));

	if (dwarf_get_elf(dbg, &e, &de) != DW_DLV_OK)
		errx(EXIT_FAILURE, "dwarf_get_elf: %s", dwarf_errmsg(de));

	if (section)
		find_section_base(exe, e, section);
	else
		section_base = 0;

	if (argc > 0)
		for (i = 0; i < argc; i++)
			translate(dbg, e, argv[i]);
	else {
		setvbuf(stdout, NULL, _IOLBF, 0);
		while (fgets(line, sizeof(line), stdin) != NULL)
			translate(dbg, e, line);
	}

	dwarf_finish(dbg, &de);

	(void) elf_end(e);

	exit(0);
}