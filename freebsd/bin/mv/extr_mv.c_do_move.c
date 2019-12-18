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
struct statfs {int /*<<< orphan*/  f_mntonname; } ;
struct stat {int /*<<< orphan*/  st_mode; scalar_t__ st_gid; scalar_t__ st_uid; } ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ EXDEV ; 
 int /*<<< orphan*/  F_OK ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W_OK ; 
 char* YESNO ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int copy (char const*,char const*) ; 
 scalar_t__ errno ; 
 int fastcopy (char const*,char const*,struct stat*) ; 
 int /*<<< orphan*/  fflg ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getchar () ; 
 char* group_from_gid (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ iflg ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int lstat (char const*,struct stat*) ; 
 scalar_t__ nflg ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int /*<<< orphan*/  rename (char const*,char const*) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strmode (int /*<<< orphan*/ ,char*) ; 
 char* user_from_uid (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ vflg ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
do_move(const char *from, const char *to)
{
	struct stat sb;
	int ask, ch, first;
	char modep[15];

	/*
	 * Check access.  If interactive and file exists, ask user if it
	 * should be replaced.  Otherwise if file exists but isn't writable
	 * make sure the user wants to clobber it.
	 */
	if (!fflg && !access(to, F_OK)) {

		/* prompt only if source exist */
	        if (lstat(from, &sb) == -1) {
			warn("%s", from);
			return (1);
		}

#define YESNO "(y/n [n]) "
		ask = 0;
		if (nflg) {
			if (vflg)
				printf("%s not overwritten\n", to);
			return (0);
		} else if (iflg) {
			(void)fprintf(stderr, "overwrite %s? %s", to, YESNO);
			ask = 1;
		} else if (access(to, W_OK) && !stat(to, &sb) && isatty(STDIN_FILENO)) {
			strmode(sb.st_mode, modep);
			(void)fprintf(stderr, "override %s%s%s/%s for %s? %s",
			    modep + 1, modep[9] == ' ' ? "" : " ",
			    user_from_uid((unsigned long)sb.st_uid, 0),
			    group_from_gid((unsigned long)sb.st_gid, 0), to, YESNO);
			ask = 1;
		}
		if (ask) {
			first = ch = getchar();
			while (ch != '\n' && ch != EOF)
				ch = getchar();
			if (first != 'y' && first != 'Y') {
				(void)fprintf(stderr, "not overwritten\n");
				return (0);
			}
		}
	}
	/*
	 * Rename on FreeBSD will fail with EISDIR and ENOTDIR, before failing
	 * with EXDEV.  Therefore, copy() doesn't have to perform the checks
	 * specified in the Step 3 of the POSIX mv specification.
	 */
	if (!rename(from, to)) {
		if (vflg)
			printf("%s -> %s\n", from, to);
		return (0);
	}

	if (errno == EXDEV) {
		struct statfs sfs;
		char path[PATH_MAX];

		/*
		 * If the source is a symbolic link and is on another
		 * filesystem, it can be recreated at the destination.
		 */
		if (lstat(from, &sb) == -1) {
			warn("%s", from);
			return (1);
		}
		if (!S_ISLNK(sb.st_mode)) {
			/* Can't mv(1) a mount point. */
			if (realpath(from, path) == NULL) {
				warn("cannot resolve %s: %s", from, path);
				return (1);
			}
			if (!statfs(path, &sfs) &&
			    !strcmp(path, sfs.f_mntonname)) {
				warnx("cannot rename a mount point");
				return (1);
			}
		}
	} else {
		warn("rename %s to %s", from, to);
		return (1);
	}

	/*
	 * If rename fails because we're trying to cross devices, and
	 * it's a regular file, do the copy internally; otherwise, use
	 * cp and rm.
	 */
	if (lstat(from, &sb)) {
		warn("%s", from);
		return (1);
	}
	return (S_ISREG(sb.st_mode) ?
	    fastcopy(from, to, &sb) : copy(from, to));
}