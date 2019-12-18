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
struct spec_name {int dummy; } ;
struct elfdump {int options; char* filename; int /*<<< orphan*/ * archive; int /*<<< orphan*/  flags; int /*<<< orphan*/  snl; int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 void* ED_ALL ; 
 int ED_CHECKSUM ; 
 int ED_DYN ; 
 int ED_EHDR ; 
 int ED_GOT ; 
 int ED_HASH ; 
 int ED_INTERP ; 
 int ED_NOTE ; 
 int ED_PHDR ; 
 int ED_REL ; 
 int ED_SHDR ; 
 int ED_SYMTAB ; 
 int ED_SYMVER ; 
 char* ELFTC_GETPROGNAME () ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  ONLY_ARSYM ; 
 int /*<<< orphan*/  PRINT_ARSYM ; 
 int /*<<< orphan*/  PRINT_FILENAME ; 
 int /*<<< orphan*/  SOLARIS_FMT ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct spec_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_name (struct elfdump*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_print_object (struct elfdump*) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfdump_longopts ; 
 char* elftc_version () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct spec_name* find_name (struct elfdump*,char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct elfdump*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sn_list ; 
 int /*<<< orphan*/  spec_name ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  usage () ; 

int
main(int ac, char **av)
{
	struct elfdump		*ed, ed_storage;
	struct spec_name	*sn;
	int			 ch, i;

	ed = &ed_storage;
	memset(ed, 0, sizeof(*ed));
	STAILQ_INIT(&ed->snl);
	ed->out = stdout;
	while ((ch = getopt_long(ac, av, "acdeiGHhknN:prsSvVw:",
		elfdump_longopts, NULL)) != -1)
		switch (ch) {
		case 'a':
			ed->options = ED_ALL;
			break;
		case 'c':
			ed->options |= ED_SHDR;
			break;
		case 'd':
			ed->options |= ED_DYN;
			break;
		case 'e':
			ed->options |= ED_EHDR;
			break;
		case 'i':
			ed->options |= ED_INTERP;
			break;
		case 'G':
			ed->options |= ED_GOT;
			break;
		case 'h':
			ed->options |= ED_HASH;
			break;
		case 'k':
			ed->options |= ED_CHECKSUM;
			break;
		case 'n':
			ed->options |= ED_NOTE;
			break;
		case 'N':
			add_name(ed, optarg);
			break;
		case 'p':
			ed->options |= ED_PHDR;
			break;
		case 'r':
			ed->options |= ED_REL;
			break;
		case 's':
			ed->options |= ED_SYMTAB;
			break;
		case 'S':
			ed->flags |= SOLARIS_FMT;
			break;
		case 'v':
			ed->options |= ED_SYMVER;
			break;
		case 'V':
			(void) printf("%s (%s)\n", ELFTC_GETPROGNAME(),
			    elftc_version());
			exit(EXIT_SUCCESS);
			break;
		case 'w':
			if ((ed->out = fopen(optarg, "w")) == NULL)
				err(EXIT_FAILURE, "%s", optarg);
			break;
		case '?':
		case 'H':
		default:
			usage();
		}

	ac -= optind;
	av += optind;

	if (ed->options == 0)
		ed->options = ED_ALL;
	sn = NULL;
	if (ed->options & ED_SYMTAB &&
	    (STAILQ_EMPTY(&ed->snl) || (sn = find_name(ed, "ARSYM")) != NULL)) {
		ed->flags |= PRINT_ARSYM;
		if (sn != NULL) {
			STAILQ_REMOVE(&ed->snl, sn, spec_name, sn_list);
			if (STAILQ_EMPTY(&ed->snl))
				ed->flags |= ONLY_ARSYM;
		}
	}
	if (ac == 0)
		usage();
	if (ac > 1)
		ed->flags |= PRINT_FILENAME;
	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "ELF library initialization failed: %s",
		    elf_errmsg(-1));

	for (i = 0; i < ac; i++) {
		ed->filename = av[i];
		ed->archive = NULL;
		elf_print_object(ed);
	}

	exit(EXIT_SUCCESS);
}