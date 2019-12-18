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
struct timespec {int dummy; } ;
struct stat {int st_mode; scalar_t__ st_uid; scalar_t__ st_gid; scalar_t__ st_flags; struct timespec st_mtim; struct timespec st_atim; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ EPERM ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 scalar_t__ chflags (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ chmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ chown (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ fchflags (int,scalar_t__) ; 
 scalar_t__ fchmod (int,int) ; 
 scalar_t__ fchown (int,scalar_t__,scalar_t__) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ futimens (int,struct timespec*) ; 
 scalar_t__ lchflags (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lchmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lchown (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 TYPE_1__ to ; 
 scalar_t__ utimensat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

int
setfile(struct stat *fs, int fd)
{
	static struct timespec tspec[2];
	struct stat ts;
	int rval, gotstat, islink, fdval;

	rval = 0;
	fdval = fd != -1;
	islink = !fdval && S_ISLNK(fs->st_mode);
	fs->st_mode &= S_ISUID | S_ISGID | S_ISVTX |
	    S_IRWXU | S_IRWXG | S_IRWXO;

	tspec[0] = fs->st_atim;
	tspec[1] = fs->st_mtim;
	if (fdval ? futimens(fd, tspec) : utimensat(AT_FDCWD, to.p_path, tspec,
	    islink ? AT_SYMLINK_NOFOLLOW : 0)) {
		warn("utimensat: %s", to.p_path);
		rval = 1;
	}
	if (fdval ? fstat(fd, &ts) :
	    (islink ? lstat(to.p_path, &ts) : stat(to.p_path, &ts)))
		gotstat = 0;
	else {
		gotstat = 1;
		ts.st_mode &= S_ISUID | S_ISGID | S_ISVTX |
		    S_IRWXU | S_IRWXG | S_IRWXO;
	}
	/*
	 * Changing the ownership probably won't succeed, unless we're root
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid/gid before setting
	 * the mode; current BSD behavior is to remove all setuid bits on
	 * chown.  If chown fails, lose setuid/setgid bits.
	 */
	if (!gotstat || fs->st_uid != ts.st_uid || fs->st_gid != ts.st_gid)
		if (fdval ? fchown(fd, fs->st_uid, fs->st_gid) :
		    (islink ? lchown(to.p_path, fs->st_uid, fs->st_gid) :
		    chown(to.p_path, fs->st_uid, fs->st_gid))) {
			if (errno != EPERM) {
				warn("chown: %s", to.p_path);
				rval = 1;
			}
			fs->st_mode &= ~(S_ISUID | S_ISGID);
		}

	if (!gotstat || fs->st_mode != ts.st_mode)
		if (fdval ? fchmod(fd, fs->st_mode) :
		    (islink ? lchmod(to.p_path, fs->st_mode) :
		    chmod(to.p_path, fs->st_mode))) {
			warn("chmod: %s", to.p_path);
			rval = 1;
		}

	if (!gotstat || fs->st_flags != ts.st_flags)
		if (fdval ?
		    fchflags(fd, fs->st_flags) :
		    (islink ? lchflags(to.p_path, fs->st_flags) :
		    chflags(to.p_path, fs->st_flags))) {
			warn("chflags: %s", to.p_path);
			rval = 1;
		}

	return (rval);
}