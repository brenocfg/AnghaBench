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
struct bsdar {char* progname; int options; char* filename; char mode; int argc; char** argv; int /*<<< orphan*/ * posarg; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int AR_A ; 
 int AR_B ; 
 int AR_BSD ; 
 int AR_C ; 
 int AR_CC ; 
 int AR_D ; 
 int AR_J ; 
 int AR_O ; 
 int AR_S ; 
 int AR_SS ; 
 int AR_TR ; 
 int AR_U ; 
 int AR_V ; 
 int AR_Z ; 
 char* ELFTC_GETPROGNAME () ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
#define  OPTION_HELP 128 
 int /*<<< orphan*/  ar_mode_script (struct bsdar*) ; 
 int ar_read_archive (struct bsdar*,char) ; 
 int ar_write_archive (struct bsdar*,char) ; 
 int /*<<< orphan*/ * basename (char*) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bsdar_usage () ; 
 int /*<<< orphan*/  bsdar_version () ; 
 int /*<<< orphan*/  bsdar_warnc (struct bsdar*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longopts ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct bsdar*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  only_mode (struct bsdar*,char*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  ranlib_usage () ; 
 int /*<<< orphan*/  set_mode (struct bsdar*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

int
main(int argc, char **argv)
{
	struct bsdar	*bsdar, bsdar_storage;
	char		*arcmd, *argv1_saved;
	size_t		 len;
	int		 exitcode, i, opt;

	bsdar = &bsdar_storage;
	memset(bsdar, 0, sizeof(*bsdar));

	exitcode = EXIT_SUCCESS;
	arcmd = argv1_saved = NULL;
	bsdar->output = stdout;

	if ((bsdar->progname = ELFTC_GETPROGNAME()) == NULL)
		bsdar->progname = "ar";

	if (elf_version(EV_CURRENT) == EV_NONE)
		bsdar_errc(bsdar, 0, "ELF library initialization failed: %s",
		    elf_errmsg(-1));

	/*
	 * Act like ranlib if our name ends in "ranlib"; this
	 * accommodates names like "arm-freebsd7.1-ranlib",
	 * "bsdranlib", etc.
	 */
	len = strlen(bsdar->progname);
	if (len >= strlen("ranlib") &&
	    strcmp(bsdar->progname + len - strlen("ranlib"), "ranlib") == 0) {
		while ((opt = getopt_long(argc, argv, "tDUV", longopts,
		    NULL)) != -1) {
			switch(opt) {
			case 't':
				/* Ignored. */
				break;
			case 'D':
				bsdar->options |= AR_D;
				break;
			case 'U':
				bsdar->options &= ~AR_D;
				break;
			case 'V':
				bsdar_version();
				break;
			case OPTION_HELP:
				ranlib_usage();
			default:
				ranlib_usage();
			}
		}
		argv += optind;
		argc -= optind;

		if (*argv == NULL)
			ranlib_usage();

		bsdar->options |= AR_S;
		while ((bsdar->filename = *argv++) != NULL)
			exitcode |= ar_write_archive(bsdar, 's');

		exit(exitcode);
	} else {
		if (argc < 2)
			bsdar_usage();

		/*
		 * Tack on a leading '-', for old-style usage.
		 */
		if (*argv[1] != '-') {
			argv1_saved = argv[1];
			len = strlen(argv[1]) + 2;
			if ((arcmd = malloc(len)) == NULL)
				bsdar_errc(bsdar, errno, "malloc failed");
			(void) snprintf(arcmd, len, "-%s", argv[1]);
			argv[1] = arcmd;
		}
	}

	while ((opt = getopt_long(argc, argv, "abCcdDfF:ijlMmopqrSsTtUuVvxz",
	    longopts, NULL)) != -1) {
		switch(opt) {
		case 'a':
			bsdar->options |= AR_A;
			break;
		case 'b':
		case 'i':
			bsdar->options |= AR_B;
			break;
		case 'C':
			bsdar->options |= AR_CC;
			break;
		case 'c':
			bsdar->options |= AR_C;
			break;
		case 'd':
			set_mode(bsdar, opt);
			break;
		case 'D':
			bsdar->options |= AR_D;
			break;
		case 'F':
			if (!strcasecmp(optarg, "svr4") ||
			    !strcasecmp(optarg, "gnu"))
				bsdar->options &= ~AR_BSD;
			else if (!strcasecmp(optarg, "bsd"))
				bsdar->options |= AR_BSD;
			else
				bsdar_usage();
			break;
		case 'f':
		case 'T':
			bsdar->options |= AR_TR;
			break;
		case 'j':
			/* ignored */
			break;
		case 'l':
			/* ignored, for GNU ar comptibility */
			break;
		case 'M':
			set_mode(bsdar, opt);
			break;
		case 'm':
			set_mode(bsdar, opt);
			break;
		case 'o':
			bsdar->options |= AR_O;
			break;
		case 'p':
			set_mode(bsdar, opt);
			break;
		case 'q':
			set_mode(bsdar, opt);
			break;
		case 'r':
			set_mode(bsdar, opt);
			break;
		case 'S':
			bsdar->options |= AR_SS;
			break;
		case 's':
			bsdar->options |= AR_S;
			break;
		case 't':
			set_mode(bsdar, opt);
			break;
		case 'U':
			bsdar->options &= ~AR_D;
			break;
		case 'u':
			bsdar->options |= AR_U;
			break;
		case 'V':
			bsdar_version();
			break;
		case 'v':
			bsdar->options |= AR_V;
			break;
		case 'x':
			set_mode(bsdar, opt);
			break;
		case 'z':
			/* ignored */
			break;
		case OPTION_HELP:
			bsdar_usage();
		default:
			bsdar_usage();
		}
	}

	/* Restore argv[1] if we had modified it. */
	if (arcmd != NULL) {
		argv[1] = argv1_saved;
		free(arcmd);
		arcmd = argv1_saved = NULL;
	}

	argv += optind;
	argc -= optind;

	if (*argv == NULL && bsdar->mode != 'M')
		bsdar_usage();

	if (bsdar->options & AR_A && bsdar->options & AR_B)
		bsdar_errc(bsdar, 0,
		    "only one of -a and -[bi] options allowed");

	if (bsdar->options & AR_J && bsdar->options & AR_Z)
		bsdar_errc(bsdar, 0,
		    "only one of -j and -z options allowed");

	if (bsdar->options & AR_S && bsdar->options & AR_SS)
		bsdar_errc(bsdar, 0,
		    "only one of -s and -S options allowed");

	if (bsdar->options & (AR_A | AR_B)) {
		if (*argv == NULL)
			bsdar_errc(bsdar, 0,
			    "no position operand specified");
		if ((bsdar->posarg = basename(*argv)) == NULL)
			bsdar_errc(bsdar, errno,
			    "basename failed");
		argc--;
		argv++;
	}

	if (bsdar->options & AR_A)
		only_mode(bsdar, "-a", "mqr");
	if (bsdar->options & AR_B)
		only_mode(bsdar, "-b", "mqr");
	if (bsdar->options & AR_C)
		only_mode(bsdar, "-c", "qr");
	if (bsdar->options & AR_CC)
		only_mode(bsdar, "-C", "x");
	if (bsdar->options & AR_D)
		only_mode(bsdar, "-D", "qr");
	if (bsdar->options & AR_O)
		only_mode(bsdar, "-o", "x");
	if (bsdar->options & AR_SS)
		only_mode(bsdar, "-S", "mqr");
	if (bsdar->options & AR_U)
		only_mode(bsdar, "-u", "qrx");

	if (bsdar->mode == 'M') {
		ar_mode_script(bsdar);
		exit(EXIT_SUCCESS);
	}

	if ((bsdar->filename = *argv) == NULL)
		bsdar_usage();

	bsdar->argc = --argc;
	bsdar->argv = ++argv;

	if ((!bsdar->mode || strchr("ptx", bsdar->mode)) &&
	    bsdar->options & AR_S) {
		exitcode = ar_write_archive(bsdar, 's');
		if (!bsdar->mode)
			exit(exitcode);
	}

	switch(bsdar->mode) {
	case 'd': case 'm': case 'q': case 'r':
		exitcode = ar_write_archive(bsdar, bsdar->mode);
		break;

	case 'p': case 't': case 'x':
		exitcode = ar_read_archive(bsdar, bsdar->mode);
		break;
	default:
		bsdar_usage();
		/* NOTREACHED */
	}

	for (i = 0; i < bsdar->argc; i++) {
		if (bsdar->argv[i] != NULL) {
			bsdar_warnc(bsdar, 0, "%s: not found in archive",
			    bsdar->argv[i]);
			exitcode = EXIT_FAILURE;
		}
	}

	exit(exitcode);
}