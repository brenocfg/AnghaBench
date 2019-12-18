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
struct TYPE_4__ {int* e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  scalar_t__ Elf_Kind ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_OSABI ; 
 int ELFOSABI_NONE ; 
 int /*<<< orphan*/  ELF_C_RDWR ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_F_LAYOUT ; 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  brandelf_longopts ; 
 int close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 char* elf_errmsg (int) ; 
 scalar_t__ elf_flagelf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int elf_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int elftype (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ gelf_update_ehdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* iselftype (int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printelftypes () ; 
 int /*<<< orphan*/  printversion () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char **argv)
{
	GElf_Ehdr ehdr;
	Elf *elf;
	Elf_Kind kind;
	int type = ELFOSABI_NONE;
	int retval = 0;
	int ch, change = 0, force = 0, listed = 0;

	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "elf_version error");

	while ((ch = getopt_long(argc, argv, "Vf:hlt:v", brandelf_longopts,
		NULL)) != -1)
		switch (ch) {
		case 'f':
			if (change)
				errx(EXIT_FAILURE, "ERROR: the -f option is "
				    "incompatible with the -t option.");
			force = 1;
			type = atoi(optarg);
			if (errno == ERANGE || type < 0 || type > 255) {
				warnx("ERROR: invalid argument to option "
				    "-f: %s", optarg);
				usage();
			}
			break;
		case 'h':
			usage();
			break;
		case 'l':
			printelftypes();
			listed = 1;
			break;
		case 'v':
			/* This flag is ignored. */
			break;
		case 't':
			if (force)
				errx(EXIT_FAILURE, "the -t option is "
				    "incompatible with the -f option.");
			if ((type = elftype(optarg)) == -1) {
				warnx("ERROR: invalid ELF type '%s'", optarg);
				usage();
			}

			change = 1;
			break;
		case 'V':
			printversion();
			break;
		default:
			usage();
	}
	argc -= optind;
	argv += optind;
	if (!argc) {
		if (listed)
			exit(0);
		else {
			warnx("no file(s) specified");
			usage();
		}
	}

	while (argc) {
		int fd;

		elf = NULL;

		if ((fd = open(argv[0], (change || force) ? O_RDWR :
		    O_RDONLY, 0)) < 0) {
			warn("error opening file %s", argv[0]);
			retval = 1;
			goto fail;
		}

		if ((elf = elf_begin(fd, (change || force) ? ELF_C_RDWR :
		    ELF_C_READ, NULL)) == NULL) {
			warnx("elf_begin failed: %s", elf_errmsg(-1));
			retval = 1;
			goto fail;
		}

		if ((kind = elf_kind(elf)) != ELF_K_ELF) {
			if (kind == ELF_K_AR)
				warnx("file '%s' is an archive.", argv[0]);
			else
				warnx("file '%s' is not an ELF file.",
				    argv[0]);
			retval = 1;
			goto fail;
		}

		if (gelf_getehdr(elf, &ehdr) == NULL) {
			warnx("gelf_getehdr: %s", elf_errmsg(-1));
			retval = 1;
			goto fail;
		}

		if (!change && !force) {
			fprintf(stdout,
			    "File '%s' is of brand '%s' (%u).\n",
			    argv[0], iselftype(ehdr.e_ident[EI_OSABI]),
			    ehdr.e_ident[EI_OSABI]);
			if (!iselftype(type)) {
				warnx("ELF ABI Brand '%u' is unknown",
				      type);
				printelftypes();
			}
		} else {

			/*
			 * Keep the existing layout of the ELF object.
			 */
			if (elf_flagelf(elf, ELF_C_SET, ELF_F_LAYOUT) == 0) {
				warnx("elf_flagelf failed: %s",
				    elf_errmsg(-1));
				retval = 1;
				goto fail;
			}

			/*
			 * Update the ABI type.
			 */
			ehdr.e_ident[EI_OSABI] = (unsigned char) type;
			if (gelf_update_ehdr(elf, &ehdr) == 0) {
				warnx("gelf_update_ehdr error: %s",
				    elf_errmsg(-1));
				retval = 1;
				goto fail;
			}

			/*
			 * Write back changes.
			 */
			if (elf_update(elf, ELF_C_WRITE) == -1) {
				warnx("elf_update error: %s", elf_errmsg(-1));
				retval = 1;
				goto fail;
			}
		}
fail:

		if (elf)
			elf_end(elf);

		if (fd >= 0 && close(fd) == -1) {
			warnx("%s: close error", argv[0]);
			retval = 1;
		}

		argc--;
		argv++;
	}

	return (retval);
}