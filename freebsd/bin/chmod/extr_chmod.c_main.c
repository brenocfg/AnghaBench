#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int mode_t ;
struct TYPE_7__ {scalar_t__ fts_level; int fts_info; char* fts_path; TYPE_1__* fts_statp; int /*<<< orphan*/  fts_accpath; int /*<<< orphan*/  fts_errno; } ;
struct TYPE_6__ {int st_mode; } ;
typedef  TYPE_2__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int ALLPERMS ; 
 int /*<<< orphan*/  AT_FDCWD ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int FTS_COMFOLLOW ; 
#define  FTS_D 132 
#define  FTS_DNR 131 
#define  FTS_DP 130 
#define  FTS_ERR 129 
 int FTS_LOGICAL ; 
#define  FTS_NS 128 
 int FTS_PHYSICAL ; 
 scalar_t__ FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
 int /*<<< orphan*/  SIGINFO ; 
 int S_IFMT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fchmodat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int getmode (int*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ may_have_nfs4acl (TYPE_2__*,int) ; 
 size_t optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* setmode (char*) ; 
 scalar_t__ siginfo ; 
 int /*<<< orphan*/  siginfo_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strmode (int,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	FTS *ftsp;
	FTSENT *p;
	mode_t *set;
	int Hflag, Lflag, Rflag, ch, fflag, fts_options, hflag, rval;
	int vflag;
	char *mode;
	mode_t newmode;

	set = NULL;
	Hflag = Lflag = Rflag = fflag = hflag = vflag = 0;
	while ((ch = getopt(argc, argv, "HLPRXfghorstuvwx")) != -1)
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
		case 'f':
			fflag = 1;
			break;
		case 'h':
			/*
			 * In System V the -h option causes chmod to change
			 * the mode of the symbolic link. 4.4BSD's symbolic
			 * links didn't have modes, so it was an undocumented
			 * noop.  In FreeBSD 3.0, lchmod(2) is introduced and
			 * this option does real work.
			 */
			hflag = 1;
			break;
		/*
		 * XXX
		 * "-[rwx]" are valid mode commands.  If they are the entire
		 * argument, getopt has moved past them, so decrement optind.
		 * Regardless, we're done argument processing.
		 */
		case 'g': case 'o': case 'r': case 's':
		case 't': case 'u': case 'w': case 'X': case 'x':
			if (argv[optind - 1][0] == '-' &&
			    argv[optind - 1][1] == ch &&
			    argv[optind - 1][2] == '\0')
				--optind;
			goto done;
		case 'v':
			vflag++;
			break;
		case '?':
		default:
			usage();
		}
done:	argv += optind;
	argc -= optind;

	if (argc < 2)
		usage();

	(void)signal(SIGINFO, siginfo_handler);

	if (Rflag) {
		if (hflag)
			errx(1, "the -R and -h options may not be "
			    "specified together.");
		if (Lflag) {
			fts_options = FTS_LOGICAL;
		} else {
			fts_options = FTS_PHYSICAL;

			if (Hflag) {
				fts_options |= FTS_COMFOLLOW;
			}
		}
	} else if (hflag) {
		fts_options = FTS_PHYSICAL;
	} else {
		fts_options = FTS_LOGICAL;
	}

	mode = *argv;
	if ((set = setmode(mode)) == NULL)
		errx(1, "invalid file mode: %s", mode);

	if ((ftsp = fts_open(++argv, fts_options, 0)) == NULL)
		err(1, "fts_open");
	for (rval = 0; (p = fts_read(ftsp)) != NULL;) {
		int atflag;

		if ((fts_options & FTS_LOGICAL) ||
		    ((fts_options & FTS_COMFOLLOW) &&
		    p->fts_level == FTS_ROOTLEVEL))
			atflag = 0;
		else
			atflag = AT_SYMLINK_NOFOLLOW;

		switch (p->fts_info) {
		case FTS_D:
			if (!Rflag)
				fts_set(ftsp, p, FTS_SKIP);
			break;
		case FTS_DNR:			/* Warn, chmod. */
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
			rval = 1;
			break;
		case FTS_DP:			/* Already changed at FTS_D. */
			continue;
		case FTS_ERR:			/* Warn, continue. */
		case FTS_NS:
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
			rval = 1;
			continue;
		default:
			break;
		}
		newmode = getmode(set, p->fts_statp->st_mode);
		/*
		 * With NFSv4 ACLs, it is possible that applying a mode
		 * identical to the one computed from an ACL will change
		 * that ACL.
		 */
		if (may_have_nfs4acl(p, hflag) == 0 &&
		    (newmode & ALLPERMS) == (p->fts_statp->st_mode & ALLPERMS))
				continue;
		if (fchmodat(AT_FDCWD, p->fts_accpath, newmode, atflag) == -1
		    && !fflag) {
			warn("%s", p->fts_path);
			rval = 1;
		} else if (vflag || siginfo) {
			(void)printf("%s", p->fts_path);

			if (vflag > 1 || siginfo) {
				char m1[12], m2[12];

				strmode(p->fts_statp->st_mode, m1);
				strmode((p->fts_statp->st_mode &
				    S_IFMT) | newmode, m2);
				(void)printf(": 0%o [%s] -> 0%o [%s]",
				    p->fts_statp->st_mode, m1,
				    (p->fts_statp->st_mode & S_IFMT) |
				    newmode, m2);
			}
			(void)printf("\n");
			siginfo = 0;
		}
	}
	if (errno)
		err(1, "fts_read");
	exit(rval);
}