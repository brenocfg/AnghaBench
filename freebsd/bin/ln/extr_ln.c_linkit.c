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
typedef  int /*<<< orphan*/  wbuf ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  bbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_FOLLOW ; 
 int /*<<< orphan*/  EISDIR ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int EOF ; 
 scalar_t__ Fflag ; 
 int PATH_MAX ; 
 scalar_t__ Pflag ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* basename (char*) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getchar () ; 
 int /*<<< orphan*/  hflag ; 
 scalar_t__ iflag ; 
 scalar_t__ linkat (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int linkch ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char const*) ; 
 scalar_t__ rmdir (char const*) ; 
 scalar_t__ samedirent (char const*,char const*) ; 
 scalar_t__ sflag ; 
 scalar_t__ snprintf (char*,int,char*,char const*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlcpy (char*,char const*,int) ; 
 scalar_t__ stub1 (char const*,struct stat*) ; 
 scalar_t__ symlink (char const*,char const*) ; 
 scalar_t__ unlink (char const*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 
 scalar_t__ wflag ; 

__attribute__((used)) static int
linkit(const char *source, const char *target, int isdir)
{
	struct stat sb;
	const char *p;
	int ch, exists, first;
	char path[PATH_MAX];
	char wbuf[PATH_MAX];
	char bbuf[PATH_MAX];

	if (!sflag) {
		/* If source doesn't exist, quit now. */
		if ((Pflag ? lstat : stat)(source, &sb)) {
			warn("%s", source);
			return (1);
		}
		/* Only symbolic links to directories. */
		if (S_ISDIR(sb.st_mode)) {
			errno = EISDIR;
			warn("%s", source);
			return (1);
		}
	}

	/*
	 * If the target is a directory (and not a symlink if hflag),
	 * append the source's name, unless Fflag is set.
	 */
	if (!Fflag && (isdir ||
	    (lstat(target, &sb) == 0 && S_ISDIR(sb.st_mode)) ||
	    (!hflag && stat(target, &sb) == 0 && S_ISDIR(sb.st_mode)))) {
		if (strlcpy(bbuf, source, sizeof(bbuf)) >= sizeof(bbuf) ||
		    (p = basename(bbuf)) == NULL ||
		    snprintf(path, sizeof(path), "%s/%s", target, p) >=
		    (ssize_t)sizeof(path)) {
			errno = ENAMETOOLONG;
			warn("%s", source);
			return (1);
		}
		target = path;
	}

	/*
	 * If the link source doesn't exist, and a symbolic link was
	 * requested, and -w was specified, give a warning.
	 */
	if (sflag && wflag) {
		if (*source == '/') {
			/* Absolute link source. */
			if (stat(source, &sb) != 0)
				 warn("warning: %s inaccessible", source);
		} else {
			/*
			 * Relative symlink source.  Try to construct the
			 * absolute path of the source, by appending `source'
			 * to the parent directory of the target.
			 */
			strlcpy(bbuf, target, sizeof(bbuf));
			p = dirname(bbuf);
			if (p != NULL) {
				(void)snprintf(wbuf, sizeof(wbuf), "%s/%s",
						p, source);
				if (stat(wbuf, &sb) != 0)
					warn("warning: %s", source);
			}
		}
	}

	/*
	 * If the file exists, first check it is not the same directory entry.
	 */
	exists = !lstat(target, &sb);
	if (exists) {
		if (!sflag && samedirent(source, target)) {
			warnx("%s and %s are the same directory entry",
			    source, target);
			return (1);
		}
	}
	/*
	 * Then unlink it forcibly if -f was specified
	 * and interactively if -i was specified.
	 */
	if (fflag && exists) {
		if (Fflag && S_ISDIR(sb.st_mode)) {
			if (rmdir(target)) {
				warn("%s", target);
				return (1);
			}
		} else if (unlink(target)) {
			warn("%s", target);
			return (1);
		}
	} else if (iflag && exists) {
		fflush(stdout);
		fprintf(stderr, "replace %s? ", target);

		first = ch = getchar();
		while(ch != '\n' && ch != EOF)
			ch = getchar();
		if (first != 'y' && first != 'Y') {
			fprintf(stderr, "not replaced\n");
			return (1);
		}

		if (Fflag && S_ISDIR(sb.st_mode)) {
			if (rmdir(target)) {
				warn("%s", target);
				return (1);
			}
		} else if (unlink(target)) {
			warn("%s", target);
			return (1);
		}
	}

	/* Attempt the link. */
	if (sflag ? symlink(source, target) :
	    linkat(AT_FDCWD, source, AT_FDCWD, target,
	    Pflag ? 0 : AT_SYMLINK_FOLLOW)) {
		warn("%s", target);
		return (1);
	}
	if (vflag)
		(void)printf("%s %c> %s\n", target, linkch, source);
	return (0);
}