#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  totalbuf ;
struct statfs {char* f_mntonname; int f_flags; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_bsize; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct maxwidths {char* f_mntonname; int f_flags; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_bsize; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  maxwidths ;
typedef  int /*<<< orphan*/  errmsg ;
struct TYPE_2__ {char* fspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MNAMELEN ; 
 int MNT_IGNORE ; 
 int MNT_NOEXEC ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int MNT_RDONLY ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int Tflag ; 
 int /*<<< orphan*/  UNITS_2 ; 
 int /*<<< orphan*/  UNITS_SI ; 
 int /*<<< orphan*/  addstat (struct statfs*,struct statfs*) ; 
 int aflag ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 int /*<<< orphan*/  build_iovec_argf (struct iovec**,int*,char*,char*,char const*) ; 
 int cflag ; 
 scalar_t__ checkvfsname (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_iovec (struct iovec**,int*) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 char* getmntpt (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hflag ; 
 int iflag ; 
 int /*<<< orphan*/  kflag ; 
 int lflag ; 
 int /*<<< orphan*/  long_options ; 
 char* makenetvfslist () ; 
 char** makevfslist (char*) ; 
 struct statfs* malloc (int) ; 
 TYPE_1__ mdev ; 
 int /*<<< orphan*/  memset (struct statfs*,int /*<<< orphan*/ ,int) ; 
 char* mkdtemp (char*) ; 
 int nflag ; 
 scalar_t__ nmount (struct iovec*,int,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  prtstat (struct statfs*,struct statfs*) ; 
 int regetmntinfo (struct statfs**,int,char const**) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int thousands ; 
 int /*<<< orphan*/  unmount (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_maxwidths (struct statfs*,struct statfs*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_warn (char*,...) ; 
 int /*<<< orphan*/  xo_warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	struct stat stbuf;
	struct statfs statfsbuf, totalbuf;
	struct maxwidths maxwidths;
	struct statfs *mntbuf;
#ifdef MOUNT_CHAR_DEVS
	struct iovec *iov = NULL;
#endif
	const char *fstype;
#ifdef MOUNT_CHAR_DEVS
	char *mntpath;
	char errmsg[255] = {0};
#endif
	char *mntpt;
	const char **vfslist;
	int i, mntsize;
	int ch, rv;
#ifdef MOUNT_CHAR_DEVS
	int iovlen = 0;
#endif

	fstype = "ufs";
	(void)setlocale(LC_ALL, "");
	memset(&maxwidths, 0, sizeof(maxwidths));
	memset(&totalbuf, 0, sizeof(totalbuf));
	totalbuf.f_bsize = DEV_BSIZE;
	strlcpy(totalbuf.f_mntfromname, "total", MNAMELEN);
	vfslist = NULL;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	while ((ch = getopt_long(argc, argv, "+abcgHhiklmnPt:T,", long_options,
	    NULL)) != -1)
		switch (ch) {
		case 'a':
			aflag = 1;
			break;
		case 'b':
				/* FALLTHROUGH */
		case 'P':
			/*
			 * POSIX specifically discusses the behavior of
			 * both -k and -P. It states that the blocksize should
			 * be set to 1024. Thus, if this occurs, simply break
			 * rather than clobbering the old blocksize.
			 */
			if (kflag)
				break;
			setenv("BLOCKSIZE", "512", 1);
			hflag = 0;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'g':
			setenv("BLOCKSIZE", "1g", 1);
			hflag = 0;
			break;
		case 'H':
			hflag = UNITS_SI;
			break;
		case 'h':
			hflag = UNITS_2;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'k':
			kflag++;
			setenv("BLOCKSIZE", "1024", 1);
			hflag = 0;
			break;
		case 'l':
			/* Ignore duplicate -l */
			if (lflag)
				break;
			if (vfslist != NULL)
				xo_errx(1, "-l and -t are mutually exclusive.");
			vfslist = makevfslist(makenetvfslist());
			lflag = 1;
			break;
		case 'm':
			setenv("BLOCKSIZE", "1m", 1);
			hflag = 0;
			break;
		case 'n':
			nflag = 1;
			break;
		case 't':
			if (lflag)
				xo_errx(1, "-l and -t are mutually exclusive.");
			if (vfslist != NULL)
				xo_errx(1, "only one -t option may be specified");
			fstype = optarg;
			vfslist = makevfslist(optarg);
			break;
		case 'T':
			Tflag = 1;
			break;
		case ',':
			thousands = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	rv = 0;
	if (!*argv) {
		/* everything (modulo -t) */
		mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
		mntsize = regetmntinfo(&mntbuf, mntsize, vfslist);
	} else {
		/* just the filesystems specified on the command line */
		mntbuf = malloc(argc * sizeof(*mntbuf));
		if (mntbuf == NULL)
			xo_err(1, "malloc()");
		mntsize = 0;
		/* continued in for loop below */
	}

	xo_open_container("storage-system-information");
	xo_open_list("filesystem");

	/* iterate through specified filesystems */
	for (; *argv; argv++) {
		if (stat(*argv, &stbuf) < 0) {
			if ((mntpt = getmntpt(*argv)) == NULL) {
				xo_warn("%s", *argv);
				rv = 1;
				continue;
			}
		} else if (S_ISCHR(stbuf.st_mode)) {
			if ((mntpt = getmntpt(*argv)) == NULL) {
#ifdef MOUNT_CHAR_DEVS
				xo_warnx(
				    "df on unmounted devices is deprecated");
				mdev.fspec = *argv;
				mntpath = strdup("/tmp/df.XXXXXX");
				if (mntpath == NULL) {
					xo_warn("strdup failed");
					rv = 1;
					continue;
				}
				mntpt = mkdtemp(mntpath);
				if (mntpt == NULL) {
					xo_warn("mkdtemp(\"%s\") failed", mntpath);
					rv = 1;
					free(mntpath);
					continue;
				}
				if (iov != NULL)
					free_iovec(&iov, &iovlen);
				build_iovec_argf(&iov, &iovlen, "fstype", "%s",
				    fstype);
				build_iovec_argf(&iov, &iovlen, "fspath", "%s",
				    mntpath);
				build_iovec_argf(&iov, &iovlen, "from", "%s",
				    *argv);
				build_iovec(&iov, &iovlen, "errmsg", errmsg,
				    sizeof(errmsg));
				if (nmount(iov, iovlen,
				    MNT_RDONLY|MNT_NOEXEC) < 0) {
					if (errmsg[0])
						xo_warn("%s: %s", *argv,
						    errmsg);
					else
						xo_warn("%s", *argv);
					rv = 1;
					(void)rmdir(mntpt);
					free(mntpath);
					continue;
				} else if (statfs(mntpt, &statfsbuf) == 0) {
					statfsbuf.f_mntonname[0] = '\0';
					prtstat(&statfsbuf, &maxwidths);
					if (cflag)
						addstat(&totalbuf, &statfsbuf);
				} else {
					xo_warn("%s", *argv);
					rv = 1;
				}
				(void)unmount(mntpt, 0);
				(void)rmdir(mntpt);
				free(mntpath);
				continue;
#else
				xo_warnx("%s: not mounted", *argv);
				rv = 1;
				continue;
#endif
			}
		} else
			mntpt = *argv;

		/*
		 * Statfs does not take a `wait' flag, so we cannot
		 * implement nflag here.
		 */
		if (statfs(mntpt, &statfsbuf) < 0) {
			xo_warn("%s", mntpt);
			rv = 1;
			continue;
		}

		/*
		 * Check to make sure the arguments we've been given are
		 * satisfied.  Return an error if we have been asked to
		 * list a mount point that does not match the other args
		 * we've been given (-l, -t, etc.).
		 */
		if (checkvfsname(statfsbuf.f_fstypename, vfslist)) {
			rv = 1;
			continue;
		}

		/* the user asked for it, so ignore the ignore flag */
		statfsbuf.f_flags &= ~MNT_IGNORE;

		/* add to list */
		mntbuf[mntsize++] = statfsbuf;
	}

	memset(&maxwidths, 0, sizeof(maxwidths));
	for (i = 0; i < mntsize; i++) {
		if (aflag || (mntbuf[i].f_flags & MNT_IGNORE) == 0) {
			update_maxwidths(&maxwidths, &mntbuf[i]);
			if (cflag)
				addstat(&totalbuf, &mntbuf[i]);
		}
	}
	for (i = 0; i < mntsize; i++)
		if (aflag || (mntbuf[i].f_flags & MNT_IGNORE) == 0)
			prtstat(&mntbuf[i], &maxwidths);

	xo_close_list("filesystem");

	if (cflag)
		prtstat(&totalbuf, &maxwidths);

	xo_close_container("storage-system-information");
	xo_finish();
	exit(rv);
}