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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  enum op { ____Placeholder_op } op ;
struct TYPE_3__ {char* p_path; char* p_end; char* target_end; } ;

/* Variables and functions */
 int DIR_TO_DNE ; 
 scalar_t__ ENOENT ; 
 int FILE_TO_DIR ; 
 int FILE_TO_FILE ; 
 int FTS_COMFOLLOW ; 
 int FTS_LOGICAL ; 
 int FTS_NOCHDIR ; 
 int FTS_PHYSICAL ; 
 int FTS_XDEV ; 
 int Rflag ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  STRIP_TRAILING_SLASH (TYPE_1__) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy (char**,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fflag ; 
 int getopt (int,char**,char*) ; 
 int iflag ; 
 int lflag ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 void* nflag ; 
 scalar_t__ optind ; 
 int pflag ; 
 int rflag ; 
 int sflag ; 
 int /*<<< orphan*/  siginfo ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 int strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 TYPE_1__ to ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 

int
main(int argc, char *argv[])
{
	struct stat to_stat, tmp_stat;
	enum op type;
	int Hflag, Lflag, ch, fts_options, r, have_trailing_slash;
	char *target;

	fts_options = FTS_NOCHDIR | FTS_PHYSICAL;
	Hflag = Lflag = 0;
	while ((ch = getopt(argc, argv, "HLPRafilnprsvx")) != -1)
		switch (ch) {
		case 'H':
			Hflag = 1;
			Lflag = 0;
			break;
		case 'L':
			Lflag = 1;
			Hflag = 0;
			break;
		case 'P':
			Hflag = Lflag = 0;
			break;
		case 'R':
			Rflag = 1;
			break;
		case 'a':
			pflag = 1;
			Rflag = 1;
			Hflag = Lflag = 0;
			break;
		case 'f':
			fflag = 1;
			iflag = nflag = 0;
			break;
		case 'i':
			iflag = 1;
			fflag = nflag = 0;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'n':
			nflag = 1;
			fflag = iflag = 0;
			break;
		case 'p':
			pflag = 1;
			break;
		case 'r':
			rflag = Lflag = 1;
			Hflag = 0;
			break;
		case 's':
			sflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		case 'x':
			fts_options |= FTS_XDEV;
			break;
		default:
			usage();
			break;
		}
	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	if (Rflag && rflag)
		errx(1, "the -R and -r options may not be specified together");
	if (lflag && sflag)
		errx(1, "the -l and -s options may not be specified together");
	if (rflag)
		Rflag = 1;
	if (Rflag) {
		if (Hflag)
			fts_options |= FTS_COMFOLLOW;
		if (Lflag) {
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
		}
	} else {
		fts_options &= ~FTS_PHYSICAL;
		fts_options |= FTS_LOGICAL | FTS_COMFOLLOW;
	}
	(void)signal(SIGINFO, siginfo);

	/* Save the target base in "to". */
	target = argv[--argc];
	if (strlcpy(to.p_path, target, sizeof(to.p_path)) >= sizeof(to.p_path))
		errx(1, "%s: name too long", target);
	to.p_end = to.p_path + strlen(to.p_path);
	if (to.p_path == to.p_end) {
		*to.p_end++ = '.';
		*to.p_end = 0;
	}
	have_trailing_slash = (to.p_end[-1] == '/');
	if (have_trailing_slash)
		STRIP_TRAILING_SLASH(to);
	to.target_end = to.p_end;

	/* Set end of argument list for fts(3). */
	argv[argc] = NULL;

	/*
	 * Cp has two distinct cases:
	 *
	 * cp [-R] source target
	 * cp [-R] source1 ... sourceN directory
	 *
	 * In both cases, source can be either a file or a directory.
	 *
	 * In (1), the target becomes a copy of the source. That is, if the
	 * source is a file, the target will be a file, and likewise for
	 * directories.
	 *
	 * In (2), the real target is not directory, but "directory/source".
	 */
	r = stat(to.p_path, &to_stat);
	if (r == -1 && errno != ENOENT)
		err(1, "%s", to.p_path);
	if (r == -1 || !S_ISDIR(to_stat.st_mode)) {
		/*
		 * Case (1).  Target is not a directory.
		 */
		if (argc > 1)
			errx(1, "%s is not a directory", to.p_path);

		/*
		 * Need to detect the case:
		 *	cp -R dir foo
		 * Where dir is a directory and foo does not exist, where
		 * we want pathname concatenations turned on but not for
		 * the initial mkdir().
		 */
		if (r == -1) {
			if (Rflag && (Lflag || Hflag))
				stat(*argv, &tmp_stat);
			else
				lstat(*argv, &tmp_stat);

			if (S_ISDIR(tmp_stat.st_mode) && Rflag)
				type = DIR_TO_DNE;
			else
				type = FILE_TO_FILE;
		} else
			type = FILE_TO_FILE;

		if (have_trailing_slash && type == FILE_TO_FILE) {
			if (r == -1) {
				errx(1, "directory %s does not exist",
				    to.p_path);
			} else
				errx(1, "%s is not a directory", to.p_path);
		}
	} else
		/*
		 * Case (2).  Target is a directory.
		 */
		type = FILE_TO_DIR;

	exit (copy(argv, type, fts_options));
}