#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; int st_size; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {char* p_path; } ;
struct TYPE_4__ {char* fts_path; struct stat* fts_statp; } ;
typedef  TYPE_1__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE_MAX ; 
 size_t BUFSIZE_SMALL ; 
 int EOF ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int MAXPHYS ; 
 size_t MIN (int /*<<< orphan*/ ,int) ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ PHYSPAGES_THRESHOLD ; 
 int /*<<< orphan*/  PROT_READ ; 
 int S_ISGID ; 
 scalar_t__ S_ISREG (int) ; 
 int S_ISUID ; 
 char* YESNO ; 
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 scalar_t__ close (int) ; 
 int cp_pct (scalar_t__,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getchar () ; 
 scalar_t__ iflag ; 
 scalar_t__ info ; 
 scalar_t__ lflag ; 
 scalar_t__ link (char*,char*) ; 
 char* malloc (size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ munmap (char*,size_t) ; 
 scalar_t__ nflag ; 
 int open (char*,int,int) ; 
 scalar_t__ pflag ; 
 scalar_t__ preserve_fd_acls (int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int,char*,size_t) ; 
 scalar_t__ setfile (struct stat*,int) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ symlink (char*,char*) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 TYPE_2__ to ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 scalar_t__ write (int,char*,size_t) ; 

int
copy_file(const FTSENT *entp, int dne)
{
	static char *buf = NULL;
	static size_t bufsize;
	struct stat *fs;
	ssize_t wcount;
	size_t wresid;
	off_t wtotal;
	int ch, checkch, from_fd, rcount, rval, to_fd;
	char *bufp;
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
	char *p;
#endif

	from_fd = to_fd = -1;
	if (!lflag && !sflag &&
	    (from_fd = open(entp->fts_path, O_RDONLY, 0)) == -1) {
		warn("%s", entp->fts_path);
		return (1);
	}

	fs = entp->fts_statp;

	/*
	 * If the file exists and we're interactive, verify with the user.
	 * If the file DNE, set the mode to be the from file, minus setuid
	 * bits, modified by the umask; arguably wrong, but it makes copying
	 * executables work right and it's been that way forever.  (The
	 * other choice is 666 or'ed with the execute bits on the from file
	 * modified by the umask.)
	 */
	if (!dne) {
#define YESNO "(y/n [n]) "
		if (nflag) {
			if (vflag)
				printf("%s not overwritten\n", to.p_path);
			rval = 1;
			goto done;
		} else if (iflag) {
			(void)fprintf(stderr, "overwrite %s? %s", 
			    to.p_path, YESNO);
			checkch = ch = getchar();
			while (ch != '\n' && ch != EOF)
				ch = getchar();
			if (checkch != 'y' && checkch != 'Y') {
				(void)fprintf(stderr, "not overwritten\n");
				rval = 1;
				goto done;
			}
		}

		if (fflag) {
			/*
			 * Remove existing destination file name create a new
			 * file.
			 */
			(void)unlink(to.p_path);
			if (!lflag && !sflag) {
				to_fd = open(to.p_path,
				    O_WRONLY | O_TRUNC | O_CREAT,
				    fs->st_mode & ~(S_ISUID | S_ISGID));
			}
		} else if (!lflag && !sflag) {
			/* Overwrite existing destination file name. */
			to_fd = open(to.p_path, O_WRONLY | O_TRUNC, 0);
		}
	} else if (!lflag && !sflag) {
		to_fd = open(to.p_path, O_WRONLY | O_TRUNC | O_CREAT,
		    fs->st_mode & ~(S_ISUID | S_ISGID));
	}

	if (!lflag && !sflag && to_fd == -1) {
		warn("%s", to.p_path);
		rval = 1;
		goto done;
	}

	rval = 0;

	if (!lflag && !sflag) {
		/*
		 * Mmap and write if less than 8M (the limit is so we don't
		 * totally trash memory on big files.  This is really a minor
		 * hack, but it wins some CPU back.
		 * Some filesystems, such as smbnetfs, don't support mmap,
		 * so this is a best-effort attempt.
		 */
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
		if (S_ISREG(fs->st_mode) && fs->st_size > 0 &&
		    fs->st_size <= 8 * 1024 * 1024 &&
		    (p = mmap(NULL, (size_t)fs->st_size, PROT_READ,
		    MAP_SHARED, from_fd, (off_t)0)) != MAP_FAILED) {
			wtotal = 0;
			for (bufp = p, wresid = fs->st_size; ;
			    bufp += wcount, wresid -= (size_t)wcount) {
				wcount = write(to_fd, bufp, wresid);
				if (wcount <= 0)
					break;
				wtotal += wcount;
				if (info) {
					info = 0;
					(void)fprintf(stderr,
					    "%s -> %s %3d%%\n",
					    entp->fts_path, to.p_path,
					    cp_pct(wtotal, fs->st_size));
				}
				if (wcount >= (ssize_t)wresid)
					break;
			}
			if (wcount != (ssize_t)wresid) {
				warn("%s", to.p_path);
				rval = 1;
			}
			/* Some systems don't unmap on close(2). */
			if (munmap(p, fs->st_size) < 0) {
				warn("%s", entp->fts_path);
				rval = 1;
			}
		} else
#endif
		{
			if (buf == NULL) {
				/*
				 * Note that buf and bufsize are static. If
				 * malloc() fails, it will fail at the start
				 * and not copy only some files. 
				 */ 
				if (sysconf(_SC_PHYS_PAGES) > 
				    PHYSPAGES_THRESHOLD)
					bufsize = MIN(BUFSIZE_MAX, MAXPHYS * 8);
				else
					bufsize = BUFSIZE_SMALL;
				buf = malloc(bufsize);
				if (buf == NULL)
					err(1, "Not enough memory");
			}
			wtotal = 0;
			while ((rcount = read(from_fd, buf, bufsize)) > 0) {
				for (bufp = buf, wresid = rcount; ;
				    bufp += wcount, wresid -= wcount) {
					wcount = write(to_fd, bufp, wresid);
					if (wcount <= 0)
						break;
					wtotal += wcount;
					if (info) {
						info = 0;
						(void)fprintf(stderr,
						    "%s -> %s %3d%%\n",
						    entp->fts_path, to.p_path,
						    cp_pct(wtotal, fs->st_size));
					}
					if (wcount >= (ssize_t)wresid)
						break;
				}
				if (wcount != (ssize_t)wresid) {
					warn("%s", to.p_path);
					rval = 1;
					break;
				}
			}
			if (rcount < 0) {
				warn("%s", entp->fts_path);
				rval = 1;
			}
		}
	} else if (lflag) {
		if (link(entp->fts_path, to.p_path)) {
			warn("%s", to.p_path);
			rval = 1;
		}
	} else if (sflag) {
		if (symlink(entp->fts_path, to.p_path)) {
			warn("%s", to.p_path);
			rval = 1;
		}
	}

	/*
	 * Don't remove the target even after an error.  The target might
	 * not be a regular file, or its attributes might be important,
	 * or its contents might be irreplaceable.  It would only be safe
	 * to remove it if we created it and its length is 0.
	 */

	if (!lflag && !sflag) {
		if (pflag && setfile(fs, to_fd))
			rval = 1;
		if (pflag && preserve_fd_acls(from_fd, to_fd) != 0)
			rval = 1;
		if (close(to_fd)) {
			warn("%s", to.p_path);
			rval = 1;
		}
	}

done:
	if (from_fd != -1)
		(void)close(from_fd);
	return (rval);
}