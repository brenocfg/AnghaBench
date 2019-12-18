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

/* Variables and functions */
 int /*<<< orphan*/  FTS_COMFOLLOW ; 
 int /*<<< orphan*/  FTS_LOGICAL ; 
 int /*<<< orphan*/  FTS_NOCHDIR ; 
 int /*<<< orphan*/  FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_XDEV ; 
 scalar_t__ Hflag ; 
 scalar_t__ Lflag ; 
 scalar_t__ PAXPATHLEN ; 
 scalar_t__ Xflag ; 
 scalar_t__ atdir_start () ; 
 int /*<<< orphan*/ ** farray ; 
 int /*<<< orphan*/ * fthead ; 
 scalar_t__ ftree_arg () ; 
 int /*<<< orphan*/  ftsopts ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 scalar_t__ tflag ; 

int
ftree_start(void)
{
	/*
	 * Set up the operation mode of fts, open the first file arg. We must
	 * use FTS_NOCHDIR, as the user may have to open multiple archives and
	 * if fts did a chdir off into the boondocks, we may create an archive
	 * volume in a place where the user did not expect to.
	 */
	ftsopts = FTS_NOCHDIR;

	/*
	 * optional user flags that effect file traversal
	 * -H command line symlink follow only (half follow)
	 * -L follow symlinks (logical)
	 * -P do not follow symlinks (physical). This is the default.
	 * -X do not cross over mount points
	 * -t preserve access times on files read.
	 * -n select only the first member of a file tree when a match is found
	 * -d do not extract subtrees rooted at a directory arg.
	 */
	if (Lflag)
		ftsopts |= FTS_LOGICAL;
	else
		ftsopts |= FTS_PHYSICAL;
	if (Hflag)
#	ifdef NET2_FTS
		paxwarn(0, "The -H flag is not supported on this version");
#	else
		ftsopts |= FTS_COMFOLLOW;
#	endif
	if (Xflag)
		ftsopts |= FTS_XDEV;

	if ((fthead == NULL) && ((farray[0] = malloc(PAXPATHLEN+2)) == NULL)) {
		paxwarn(1, "Unable to allocate memory for file name buffer");
		return(-1);
	}

	if (ftree_arg() < 0)
		return(-1);
	if (tflag && (atdir_start() < 0))
		return(-1);
	return(0);
}