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
struct TYPE_3__ {char* str; struct TYPE_3__* link; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  Eflag ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIG_IGN ; 
 scalar_t__ Sflag ; 
 int ac ; 
 int /*<<< orphan*/  alloc (int) ; 
 scalar_t__ append (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  av ; 
 scalar_t__ callsys (int /*<<< orphan*/ ) ; 
 scalar_t__ cflag ; 
 int /*<<< orphan*/  compose (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 char* concat (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errcnt ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 char* exists (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  filename (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  help () ; 
 TYPE_1__* ilist ; 
 char** include ; 
 int /*<<< orphan*/  initinputs () ; 
 scalar_t__ interrupt ; 
 int /*<<< orphan*/  ld ; 
 scalar_t__* llist ; 
 int /*<<< orphan*/  opt (char*) ; 
 int /*<<< orphan*/  option (int /*<<< orphan*/ ) ; 
 char* outfile ; 
 scalar_t__ plist ; 
 char* progname ; 
 int /*<<< orphan*/  rm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmlist ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stringf (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ suffix (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * suffixes ; 
 char* tempdir ; 

main(int argc, char *argv[]) {
	int i, j, nf;
	
	progname = argv[0];
	ac = argc + 50;
	av = alloc(ac*sizeof(char *));
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, interrupt);
	if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
		signal(SIGTERM, interrupt);
#ifdef SIGHUP
	if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
		signal(SIGHUP, interrupt);
#endif
	if (getenv("TMP"))
		tempdir = getenv("TMP");
	else if (getenv("TEMP"))
		tempdir = getenv("TEMP");
	else if (getenv("TMPDIR"))
		tempdir = getenv("TMPDIR");
	assert(tempdir);
	i = strlen(tempdir);
	for (; i > 0 && tempdir[i-1] == '/' || tempdir[i-1] == '\\'; i--)
		tempdir[i-1] = '\0';
	if (argc <= 1) {
		help();
		exit(0);
	}
	plist = append("-D__LCC__", 0);
	initinputs();
	if (getenv("LCCDIR"))
		option(stringf("-lccdir=%s", getenv("LCCDIR")));
	for (nf = 0, i = j = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			if (++i < argc) {
				if (suffix(argv[i], suffixes, 2) >= 0) {
					error("-o would overwrite %s", argv[i]);
					exit(8);
				}
				outfile = argv[i];
				continue;
			} else {
				error("unrecognized option `%s'", argv[i-1]);
				exit(8);
			}
		} else if (strcmp(argv[i], "-target") == 0) {
			if (argv[i+1] && *argv[i+1] != '-')
				i++;
			continue;
		} else if (*argv[i] == '-' && argv[i][1] != 'l') {
			opt(argv[i]);
			continue;
		} else if (*argv[i] != '-' && suffix(argv[i], suffixes, 3) >= 0)
			nf++;
		argv[j++] = argv[i];
	}
	if ((cflag || Sflag) && outfile && nf != 1) {
		fprintf(stderr, "%s: -o %s ignored\n", progname, outfile);
		outfile = 0;
	}
	argv[j] = 0;
	for (i = 0; include[i]; i++)
		plist = append(include[i], plist);
	if (ilist) {
		List b = ilist;
		do {
			b = b->link;
			plist = append(b->str, plist);
		} while (b != ilist);
	}
	ilist = 0;
	for (i = 1; argv[i]; i++)
		if (*argv[i] == '-')
			opt(argv[i]);
		else {
			char *name = exists(argv[i]);
			if (name) {
				if (strcmp(name, argv[i]) != 0
				|| nf > 1 && suffix(name, suffixes, 3) >= 0)
					fprintf(stderr, "%s:\n", name);
				filename(name, 0);
			} else
				error("can't find `%s'", argv[i]);
		}
	if (errcnt == 0 && !Eflag && !Sflag && !cflag && llist[1]) {
		compose(ld, llist[0], llist[1],
			append(outfile ? outfile : concat("a", first(suffixes[4])), 0));
		if (callsys(av))
			errcnt++;
	}
	rm(rmlist);	
	return errcnt ? EXIT_FAILURE : EXIT_SUCCESS;
}