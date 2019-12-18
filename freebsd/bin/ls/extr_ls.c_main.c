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
typedef  scalar_t__ uid_t ;
struct winsize {int ws_col; } ;

/* Variables and functions */
 scalar_t__ COLORFLAG_ALWAYS ; 
 scalar_t__ COLORFLAG_AUTO ; 
 scalar_t__ COLORFLAG_NEVER ; 
#define  COLOR_OPT 128 
 int FTS_COMFOLLOW ; 
 int FTS_LOGICAL ; 
 int FTS_NOSTAT ; 
 int FTS_PHYSICAL ; 
 int FTS_SEEDOT ; 
 int FTS_WHITEOUT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  acccmp ; 
 void* ansi_bgcol ; 
 void* ansi_coloff ; 
 void* ansi_fgcol ; 
 void* attrs_off ; 
 int /*<<< orphan*/  birthcmp ; 
 int blocksize ; 
 scalar_t__ colorflag ; 
 int /*<<< orphan*/  colorquit ; 
 scalar_t__ do_color () ; 
 int /*<<< orphan*/  do_color_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_color_auto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_color_never (int /*<<< orphan*/ *) ; 
 void* enter_bold ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int explicitansi ; 
 int f_accesstime ; 
 int f_birthtime ; 
 int f_color ; 
 int f_flags ; 
 int f_humanval ; 
 int f_inode ; 
 int f_kblocks ; 
 int f_label ; 
 int f_listdir ; 
 int f_listdot ; 
 int f_longform ; 
 int f_noautodot ; 
 int f_nofollow ; 
 int f_nonprint ; 
 int f_nosort ; 
 int f_notabs ; 
 int f_numericonly ; 
 int f_octal ; 
 int f_octal_escape ; 
 int f_recursive ; 
 int f_reversesort ; 
 int f_samesort ; 
 int f_sectime ; 
 int f_singlecol ; 
 int f_size ; 
 int f_sizesort ; 
 int f_slash ; 
 int f_sortacross ; 
 int f_statustime ; 
 int f_stream ; 
 int f_thousands ; 
 int /*<<< orphan*/ * f_timeformat ; 
 int f_timesort ; 
 int f_type ; 
 int f_whiteout ; 
 int /*<<< orphan*/  getbsize (int*,int*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ getuid () ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  long_opts ; 
 int /*<<< orphan*/  modcmp ; 
 int /*<<< orphan*/  namecmp ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parsecolors (char*) ; 
 int /*<<< orphan*/  printcol ; 
 int /*<<< orphan*/  printfcn ; 
 int /*<<< orphan*/  printlong ; 
 int /*<<< orphan*/  printscol ; 
 int /*<<< orphan*/  printstream ; 
 int /*<<< orphan*/  revacccmp ; 
 int /*<<< orphan*/  revbirthcmp ; 
 int /*<<< orphan*/  revmodcmp ; 
 int /*<<< orphan*/  revnamecmp ; 
 int /*<<< orphan*/  revsizecmp ; 
 int /*<<< orphan*/  revstatcmp ; 
 int /*<<< orphan*/  rval ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizecmp ; 
 int /*<<< orphan*/  sortfcn ; 
 int /*<<< orphan*/  statcmp ; 
 int strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int termwidth ; 
 int tgetent (char*,char*) ; 
 void* tgetstr (char*,char**) ; 
 int /*<<< orphan*/  traverse (int,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	static char dot[] = ".", *dotav[] = {dot, NULL};
	struct winsize win;
	int ch, fts_options, notused;
	char *p;
	const char *errstr = NULL;
#ifdef COLORLS
	char termcapbuf[1024];	/* termcap definition buffer */
	char tcapbuf[512];	/* capability buffer */
	char *bp = tcapbuf, *term;
#endif

	(void)setlocale(LC_ALL, "");

	/* Terminal defaults to -Cq, non-terminal defaults to -1. */
	if (isatty(STDOUT_FILENO)) {
		termwidth = 80;
		if ((p = getenv("COLUMNS")) != NULL && *p != '\0')
			termwidth = strtonum(p, 0, INT_MAX, &errstr);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) != -1 &&
		    win.ws_col > 0)
			termwidth = win.ws_col;
		f_nonprint = 1;
	} else {
		f_singlecol = 1;
		/* retrieve environment variable, in case of explicit -C */
		p = getenv("COLUMNS");
		if (p)
			termwidth = strtonum(p, 0, INT_MAX, &errstr);
	}

	if (errstr)
		termwidth = 80;

	fts_options = FTS_PHYSICAL;
	if (getenv("LS_SAMESORT"))
		f_samesort = 1;
	while ((ch = getopt_long(argc, argv,
	    "+1ABCD:FGHILPRSTUWXZabcdfghiklmnopqrstuwxy,", long_opts,
	    NULL)) != -1) {
		switch (ch) {
		/*
		 * The -1, -C, -x and -l options all override each other so
		 * shell aliasing works right.
		 */
		case '1':
			f_singlecol = 1;
			f_longform = 0;
			f_stream = 0;
			break;
		case 'C':
			f_sortacross = f_longform = f_singlecol = 0;
			break;
		case 'l':
			f_longform = 1;
			f_singlecol = 0;
			f_stream = 0;
			break;
		case 'x':
			f_sortacross = 1;
			f_longform = 0;
			f_singlecol = 0;
			break;
		/* The -c, -u, and -U options override each other. */
		case 'c':
			f_statustime = 1;
			f_accesstime = 0;
			f_birthtime = 0;
			break;
		case 'u':
			f_accesstime = 1;
			f_statustime = 0;
			f_birthtime = 0;
			break;
		case 'U':
			f_birthtime = 1;
			f_accesstime = 0;
			f_statustime = 0;
			break;
		case 'f':
			f_nosort = 1;
		       /* FALLTHROUGH */
		case 'a':
			fts_options |= FTS_SEEDOT;
			/* FALLTHROUGH */
		case 'A':
			f_listdot = 1;
			break;
		/* The -t and -S options override each other. */
		case 'S':
			f_sizesort = 1;
			f_timesort = 0;
			break;
		case 't':
			f_timesort = 1;
			f_sizesort = 0;
			break;
		/* Other flags.  Please keep alphabetic. */
		case ',':
			f_thousands = 1;
			break;
		case 'B':
			f_nonprint = 0;
			f_octal = 1;
			f_octal_escape = 0;
			break;
		case 'D':
			f_timeformat = optarg;
			break;
		case 'F':
			f_type = 1;
			f_slash = 0;
			break;
		case 'G':
			setenv("CLICOLOR", "", 1);
			break;
		case 'H':
			fts_options |= FTS_COMFOLLOW;
			f_nofollow = 0;
			break;
		case 'I':
			f_noautodot = 1;
			break;
		case 'L':
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
			f_nofollow = 0;
			break;
		case 'P':
			fts_options &= ~FTS_COMFOLLOW;
			fts_options &= ~FTS_LOGICAL;
			fts_options |= FTS_PHYSICAL;
			f_nofollow = 1;
			break;
		case 'R':
			f_recursive = 1;
			break;
		case 'T':
			f_sectime = 1;
			break;
		case 'W':
			f_whiteout = 1;
			break;
		case 'Z':
			f_label = 1;
			break;
		case 'b':
			f_nonprint = 0;
			f_octal = 0;
			f_octal_escape = 1;
			break;
		/* The -d option turns off the -R option. */
		case 'd':
			f_listdir = 1;
			f_recursive = 0;
			break;
		case 'g':	/* Compatibility with 4.3BSD. */
			break;
		case 'h':
			f_humanval = 1;
			break;
		case 'i':
			f_inode = 1;
			break;
		case 'k':
			f_humanval = 0;
			f_kblocks = 1;
			break;
		case 'm':
			f_stream = 1;
			f_singlecol = 0;
			f_longform = 0;
			break;
		case 'n':
			f_numericonly = 1;
			break;
		case 'o':
			f_flags = 1;
			break;
		case 'p':
			f_slash = 1;
			f_type = 1;
			break;
		case 'q':
			f_nonprint = 1;
			f_octal = 0;
			f_octal_escape = 0;
			break;
		case 'r':
			f_reversesort = 1;
			break;
		case 's':
			f_size = 1;
			break;
		case 'w':
			f_nonprint = 0;
			f_octal = 0;
			f_octal_escape = 0;
			break;
		case 'y':
			f_samesort = 1;
			break;
#ifdef COLORLS
		case COLOR_OPT:
			if (optarg == NULL || do_color_always(optarg))
				colorflag = COLORFLAG_ALWAYS;
			else if (do_color_auto(optarg))
				colorflag = COLORFLAG_AUTO;
			else if (do_color_never(optarg))
				colorflag = COLORFLAG_NEVER;
			else
				errx(2, "unsupported --color value '%s' (must be always, auto, or never)",
				    optarg);
			break;
#endif
		default:
		case '?':
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* Root is -A automatically unless -I. */
	if (!f_listdot && getuid() == (uid_t)0 && !f_noautodot)
		f_listdot = 1;

	/*
	 * Enabling of colours is conditional on the environment in conjunction
	 * with the --color and -G arguments, if supplied.
	 */
	if (do_color()) {
#ifdef COLORLS
		if ((term = getenv("TERM")) != NULL &&
		    tgetent(termcapbuf, term) == 1) {
			ansi_fgcol = tgetstr("AF", &bp);
			ansi_bgcol = tgetstr("AB", &bp);
			attrs_off = tgetstr("me", &bp);
			enter_bold = tgetstr("md", &bp);

			/* To switch colours off use 'op' if
			 * available, otherwise use 'oc', or
			 * don't do colours at all. */
			ansi_coloff = tgetstr("op", &bp);
			if (!ansi_coloff)
				ansi_coloff = tgetstr("oc", &bp);
			if (ansi_fgcol && ansi_bgcol && ansi_coloff)
				f_color = 1;
		} else if (colorflag == COLORFLAG_ALWAYS) {
			/*
			 * If we're *always* doing color but we don't have
			 * a functional TERM supplied, we'll fallback to
			 * outputting raw ANSI sequences.
			 */
			f_color = 1;
			explicitansi = true;
		}
#else
		warnx("color support not compiled in");
#endif /*COLORLS*/
	}

#ifdef COLORLS
	if (f_color) {
		/*
		 * We can't put tabs and color sequences together:
		 * column number will be incremented incorrectly
		 * for "stty oxtabs" mode.
		 */
		f_notabs = 1;
		(void)signal(SIGINT, colorquit);
		(void)signal(SIGQUIT, colorquit);
		parsecolors(getenv("LSCOLORS"));
	}
#endif

	/*
	 * If not -F, -i, -l, -s, -S or -t options, don't require stat
	 * information, unless in color mode in which case we do
	 * need this to determine which colors to display.
	 */
	if (!f_inode && !f_longform && !f_size && !f_timesort &&
	    !f_sizesort && !f_type
#ifdef COLORLS
	    && !f_color
#endif
	    )
		fts_options |= FTS_NOSTAT;

	/*
	 * If not -F, -P, -d or -l options, follow any symbolic links listed on
	 * the command line, unless in color mode in which case we need to
	 * distinguish file type for a symbolic link itself and its target.
	 */
	if (!f_nofollow && !f_longform && !f_listdir && (!f_type || f_slash)
#ifdef COLORLS
	    && !f_color
#endif
	    )
		fts_options |= FTS_COMFOLLOW;

	/*
	 * If -W, show whiteout entries
	 */
#ifdef FTS_WHITEOUT
	if (f_whiteout)
		fts_options |= FTS_WHITEOUT;
#endif

	/* If -i, -l or -s, figure out block size. */
	if (f_inode || f_longform || f_size) {
		if (f_kblocks)
			blocksize = 2;
		else {
			(void)getbsize(&notused, &blocksize);
			blocksize /= 512;
		}
	}
	/* Select a sort function. */
	if (f_reversesort) {
		if (!f_timesort && !f_sizesort)
			sortfcn = revnamecmp;
		else if (f_sizesort)
			sortfcn = revsizecmp;
		else if (f_accesstime)
			sortfcn = revacccmp;
		else if (f_birthtime)
			sortfcn = revbirthcmp;
		else if (f_statustime)
			sortfcn = revstatcmp;
		else		/* Use modification time. */
			sortfcn = revmodcmp;
	} else {
		if (!f_timesort && !f_sizesort)
			sortfcn = namecmp;
		else if (f_sizesort)
			sortfcn = sizecmp;
		else if (f_accesstime)
			sortfcn = acccmp;
		else if (f_birthtime)
			sortfcn = birthcmp;
		else if (f_statustime)
			sortfcn = statcmp;
		else		/* Use modification time. */
			sortfcn = modcmp;
	}

	/* Select a print function. */
	if (f_singlecol)
		printfcn = printscol;
	else if (f_longform)
		printfcn = printlong;
	else if (f_stream)
		printfcn = printstream;
	else
		printfcn = printcol;

	if (argc)
		traverse(argc, argv, fts_options);
	else
		traverse(1, dotav, fts_options);
	exit(rval);
}