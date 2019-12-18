#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int v_fd; int v_dump_fd; int /*<<< orphan*/  v_path; int /*<<< orphan*/  v_size; } ;
typedef  TYPE_1__ vnode_t ;
struct stat64 {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  dumppath ;

/* Variables and functions */
 int FCREAT ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int FREAD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fstat64 (int,struct stat64*) ; 
 int open64 (char*,int,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spa_strdup (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int stat64 (char*,struct stat64*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int umask (int) ; 
 TYPE_1__* umem_zalloc (int,int /*<<< orphan*/ ) ; 
 char* vn_dumpdir ; 

int
vn_open(char *path, int x1, int flags, int mode, vnode_t **vpp, int x2, int x3)
{
	int fd;
	int dump_fd;
	vnode_t *vp;
	int old_umask;
	char realpath[MAXPATHLEN];
	struct stat64 st;

	/*
	 * If we're accessing a real disk from userland, we need to use
	 * the character interface to avoid caching.  This is particularly
	 * important if we're trying to look at a real in-kernel storage
	 * pool from userland, e.g. via zdb, because otherwise we won't
	 * see the changes occurring under the segmap cache.
	 * On the other hand, the stupid character device returns zero
	 * for its size.  So -- gag -- we open the block device to get
	 * its size, and remember it for subsequent VOP_GETATTR().
	 */
	if (strncmp(path, "/dev/", 5) == 0) {
		char *dsk;
		fd = open64(path, O_RDONLY);
		if (fd == -1)
			return (errno);
		if (fstat64(fd, &st) == -1) {
			close(fd);
			return (errno);
		}
		close(fd);
		(void) sprintf(realpath, "%s", path);
		dsk = strstr(path, "/dsk/");
		if (dsk != NULL)
			(void) sprintf(realpath + (dsk - path) + 1, "r%s",
			    dsk + 1);
	} else {
		(void) sprintf(realpath, "%s", path);
		if (!(flags & FCREAT) && stat64(realpath, &st) == -1)
			return (errno);
	}

	if (flags & FCREAT)
		old_umask = umask(0);

	/*
	 * The construct 'flags - FREAD' conveniently maps combinations of
	 * FREAD and FWRITE to the corresponding O_RDONLY, O_WRONLY, and O_RDWR.
	 */
	fd = open64(realpath, flags - FREAD, mode);

	if (flags & FCREAT)
		(void) umask(old_umask);

	if (vn_dumpdir != NULL) {
		char dumppath[MAXPATHLEN];
		(void) snprintf(dumppath, sizeof (dumppath),
		    "%s/%s", vn_dumpdir, basename(realpath));
		dump_fd = open64(dumppath, O_CREAT | O_WRONLY, 0666);
		if (dump_fd == -1)
			return (errno);
	} else {
		dump_fd = -1;
	}

	if (fd == -1)
		return (errno);

	if (fstat64(fd, &st) == -1) {
		close(fd);
		return (errno);
	}

	(void) fcntl(fd, F_SETFD, FD_CLOEXEC);

	*vpp = vp = umem_zalloc(sizeof (vnode_t), UMEM_NOFAIL);

	vp->v_fd = fd;
	vp->v_size = st.st_size;
	vp->v_path = spa_strdup(path);
	vp->v_dump_fd = dump_fd;

	return (0);
}