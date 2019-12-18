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
struct statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_WAIT ; 
 scalar_t__ checkvfsname (int /*<<< orphan*/ ,char const**) ; 
 size_t getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ nflag ; 
 int statfs (int /*<<< orphan*/ ,struct statfs*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
regetmntinfo(struct statfs **mntbufp, long mntsize, const char **vfslist)
{
	int error, i, j;
	struct statfs *mntbuf;

	if (vfslist == NULL)
		return (nflag ? mntsize : getmntinfo(mntbufp, MNT_WAIT));

	mntbuf = *mntbufp;
	for (j = 0, i = 0; i < mntsize; i++) {
		if (checkvfsname(mntbuf[i].f_fstypename, vfslist))
			continue;
		/*
		 * XXX statfs(2) can fail for various reasons. It may be
		 * possible that the user does not have access to the
		 * pathname, if this happens, we will fall back on
		 * "stale" filesystem statistics.
		 */
		error = statfs(mntbuf[i].f_mntonname, &mntbuf[j]);
		if (nflag || error < 0)
			if (i != j) {
				if (error < 0)
					xo_warnx("%s stats possibly stale",
					    mntbuf[i].f_mntonname);
				mntbuf[j] = mntbuf[i];
			}
		j++;
	}
	return (j);
}