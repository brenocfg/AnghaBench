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
struct statfs {int dummy; } ;
struct mnttab {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int allfs ; 
 int errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gsfs ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statfs2mnttab (int /*<<< orphan*/ *,struct mnttab*) ; 
 int statfs_init () ; 

int
getmntent(FILE *fp, struct mnttab *mp)
{
	struct statfs *sfs;
	int error, nfs;

	nfs = (int)lseek(fileno(fp), 0, SEEK_CUR);
	if (nfs == -1)
		return (errno);
	/* If nfs is 0, we want to refresh out cache. */
	if (nfs == 0 || gsfs == NULL) {
		error = statfs_init();
		if (error != 0)
			return (error);
	}
	if (nfs >= allfs)
		return (-1);
	statfs2mnttab(&gsfs[nfs], mp);
	if (lseek(fileno(fp), 1, SEEK_CUR) == -1)
		return (errno);
	return (0);
}