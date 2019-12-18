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
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_MMAP_R ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FA_OPEN ; 
#define  OPT_FORMAT 129 
#define  OPT_RADIX 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RADIX_DECIMAL ; 
 int /*<<< orphan*/  RADIX_HEX ; 
 int /*<<< orphan*/  RADIX_OCTAL ; 
 int RETURN_OK ; 
 scalar_t__ STYLE_BERKELEY ; 
 scalar_t__ STYLE_SYSV ; 
 int /*<<< orphan*/  berkeley_totals () ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter_casper () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileargs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileargs_init (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fileargs_open (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int handle_elf (int,char const*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  radix ; 
 int show_totals ; 
 int /*<<< orphan*/  show_version () ; 
 int /*<<< orphan*/  size_longopts ; 
 int /*<<< orphan*/  size_option ; 
 char* strdup (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ style ; 
 int /*<<< orphan*/  tbl_flush () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
main(int argc, char **argv)
{
	cap_rights_t rights;
	fileargs_t *fa;
	int ch, fd, r, rc;
	const char *fn;
	char *defaultfn;

	rc = RETURN_OK;

	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "ELF library initialization failed: %s",
		    elf_errmsg(-1));

	while ((ch = getopt_long(argc, argv, "ABVdhotx", size_longopts,
	    NULL)) != -1)
		switch((char)ch) {
		case 'A':
			style = STYLE_SYSV;
			break;
		case 'B':
			style = STYLE_BERKELEY;
			break;
		case 'V':
			show_version();
			break;
		case 'd':
			radix = RADIX_DECIMAL;
			break;
		case 'o':
			radix = RADIX_OCTAL;
			break;
		case 't':
			show_totals = 1;
			break;
		case 'x':
			radix = RADIX_HEX;
			break;
		case 0:
			switch (size_option) {
			case OPT_FORMAT:
				if (*optarg == 's' || *optarg == 'S')
					style = STYLE_SYSV;
				else if (*optarg == 'b' || *optarg == 'B')
					style = STYLE_BERKELEY;
				else {
					warnx("unrecognized format \"%s\".",
					      optarg);
					usage();
				}
				break;
			case OPT_RADIX:
				r = strtol(optarg, NULL, 10);
				if (r == 8)
					radix = RADIX_OCTAL;
				else if (r == 10)
					radix = RADIX_DECIMAL;
				else if (r == 16)
					radix = RADIX_HEX;
				else {
					warnx("unsupported radix \"%s\".",
					      optarg);
					usage();
				}
				break;
			default:
				err(EXIT_FAILURE, "Error in option handling.");
				/*NOTREACHED*/
			}
			break;
		case 'h':
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	argc -= optind;
	argv += optind;

	if (argc == 0) {
		defaultfn = strdup("a.out");
		if (defaultfn == NULL)
			err(EXIT_FAILURE, "strdup");
		argc = 1;
		argv = &defaultfn;
	} else {
		defaultfn = NULL;
	}

	cap_rights_init(&rights, CAP_FSTAT, CAP_MMAP_R);
	fa = fileargs_init(argc, argv, O_RDONLY, 0, &rights, FA_OPEN);
	if (fa == NULL)
		err(EXIT_FAILURE, "failed to initialize fileargs");

	caph_cache_catpages();
	if (caph_limit_stdio() < 0)
		err(EXIT_FAILURE, "failed to limit stdio rights");
	if (caph_enter_casper() < 0)
		err(EXIT_FAILURE, "failed to enter capability mode");

	for (; argc > 0; argc--, argv++) {
		fn = argv[0];
		fd = fileargs_open(fa, fn);
		if (fd < 0) {
			warn("%s: Failed to open", fn);
			continue;
		}
		rc = handle_elf(fd, fn);
		if (rc != RETURN_OK)
			warnx("%s: File format not recognized", fn);
	}
	if (style == STYLE_BERKELEY) {
		if (show_totals)
			berkeley_totals();
		tbl_flush();
	}
	fileargs_free(fa);
	free(defaultfn);
        return (rc);
}