#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  td_iihash; } ;
typedef  TYPE_1__ tdata_t ;

/* Variables and functions */
 char* CTF_DEFAULT_LABEL ; 
 int CTF_KEEP_STABS ; 
 int /*<<< orphan*/  CTF_LABEL_LASTIDX ; 
 int CTF_USE_DYNSYM ; 
 int EOF ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 void* debug_level ; 
 void* debug_parse ; 
 int dynsym ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_read (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_sig ; 
 int /*<<< orphan*/  iidesc_stats (int /*<<< orphan*/ ) ; 
 char* infile ; 
 int /*<<< orphan*/  merge_into_master (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 char* mktmpname (char*,char*) ; 
 char* optarg ; 
 int optind ; 
 char* outfile ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  set_terminate_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sighold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tdata_label_add (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tdata_new () ; 
 int /*<<< orphan*/  terminate (char*,char*) ; 
 int /*<<< orphan*/  terminate_cleanup ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_ctf (TYPE_1__*,char*,char*,int) ; 

int
main(int argc, char **argv)
{
	tdata_t *filetd, *mstrtd;
	const char *label = NULL;
	int verbose = 0;
	int ignore_non_c = 0;
	int keep_stabs = 0;
	int c;

#ifdef illumos
	sighold(SIGINT);
	sighold(SIGQUIT);
	sighold(SIGTERM);
#endif

	progname = basename(argv[0]);

	if (getenv("CTFCONVERT_DEBUG_LEVEL"))
		debug_level = atoi(getenv("CTFCONVERT_DEBUG_LEVEL"));
	if (getenv("CTFCONVERT_DEBUG_PARSE"))
		debug_parse = atoi(getenv("CTFCONVERT_DEBUG_PARSE"));

	while ((c = getopt(argc, argv, ":l:L:o:givs")) != EOF) {
		switch (c) {
		case 'l':
			label = optarg;
			break;
		case 'L':
			if ((label = getenv(optarg)) == NULL)
				label = CTF_DEFAULT_LABEL;
			break;
		case 'o':
			outfile = optarg;
			break;
		case 's':
			dynsym = CTF_USE_DYNSYM;
			break;
		case 'i':
			ignore_non_c = 1;
			break;
		case 'g':
			keep_stabs = CTF_KEEP_STABS;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage();
			exit(2);
		}
	}

	if (getenv("STRIPSTABS_KEEP_STABS") != NULL)
		keep_stabs = CTF_KEEP_STABS;

	if (argc - optind != 1 || label == NULL) {
		usage();
		exit(2);
	}

	infile = argv[optind];
	if (access(infile, R_OK) != 0)
		terminate("Can't access %s", infile);

	/*
	 * Upon receipt of a signal, we want to clean up and exit.  Our
	 * primary goal during cleanup is to restore the system to a state
	 * such that a subsequent make will eventually cause this command to
	 * be re-run.  If we remove the input file (which we do if we get a
	 * signal and the user didn't specify a separate output file), make
	 * will need to rebuild the input file, and will then need to re-run
	 * ctfconvert, which is what we want.
	 */
	set_terminate_cleanup(terminate_cleanup);

#ifdef illumos
	sigset(SIGINT, handle_sig);
	sigset(SIGQUIT, handle_sig);
	sigset(SIGTERM, handle_sig);
#else
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	signal(SIGTERM, handle_sig);
#endif

	filetd = tdata_new();

	if (!file_read(filetd, infile, ignore_non_c))
		terminate("%s doesn't have type data to convert\n", infile);

	if (verbose)
		iidesc_stats(filetd->td_iihash);

	mstrtd = tdata_new();
	merge_into_master(filetd, mstrtd, NULL, 1);

	tdata_label_add(mstrtd, label, CTF_LABEL_LASTIDX);

	/*
	 * If the user supplied an output file that is different from the
	 * input file, write directly to the output file.  Otherwise, write
	 * to a temporary file, and replace the input file when we're done.
	 */
	if (outfile && strcmp(infile, outfile) != 0) {
		write_ctf(mstrtd, infile, outfile, dynsym | keep_stabs);
	} else {
		char *tmpname = mktmpname(infile, ".ctf");
		write_ctf(mstrtd, infile, tmpname, dynsym | keep_stabs);
		if (rename(tmpname, infile) != 0)
			terminate("Couldn't rename temp file %s", tmpname);
		free(tmpname);
	}

	return (0);
}