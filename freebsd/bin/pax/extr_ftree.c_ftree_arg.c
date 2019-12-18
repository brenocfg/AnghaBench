#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fname; scalar_t__ chflg; struct TYPE_3__* fow; } ;

/* Variables and functions */
 scalar_t__ PAXPATHLEN ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cwdfd ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * farray ; 
 scalar_t__ fchdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ftcur ; 
 TYPE_1__* fthead ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftsopts ; 
 int /*<<< orphan*/ * ftsp ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
ftree_arg(void)
{
	char *pt;

	/*
	 * close off the current file tree
	 */
	if (ftsp != NULL) {
		(void)fts_close(ftsp);
		ftsp = NULL;
	}

	/*
	 * keep looping until we get a valid file tree to process. Stop when we
	 * reach the end of the list (or get an eof on stdin)
	 */
	for(;;) {
		if (fthead == NULL) {
			/*
			 * the user didn't supply any args, get the file trees
			 * to process from stdin;
			 */
			if (fgets(farray[0], PAXPATHLEN+1, stdin) == NULL)
				return(-1);
			if ((pt = strchr(farray[0], '\n')) != NULL)
				*pt = '\0';
		} else {
			/*
			 * the user supplied the file args as arguments to pax
			 */
			if (ftcur == NULL)
				ftcur = fthead;
			else if ((ftcur = ftcur->fow) == NULL)
				return(-1);
			if (ftcur->chflg) {
				/* First fchdir() back... */
				if (fchdir(cwdfd) < 0) {
					syswarn(1, errno,
					  "Can't fchdir to starting directory");
					return(-1);
				}
				if (chdir(ftcur->fname) < 0) {
					syswarn(1, errno, "Can't chdir to %s",
					    ftcur->fname);
					return(-1);
				}
				continue;
			} else
				farray[0] = ftcur->fname;
		}

		/*
		 * Watch it, fts wants the file arg stored in an array of char
		 * ptrs, with the last one a null. We use a two element array
		 * and set farray[0] to point at the buffer with the file name
		 * in it. We cannot pass all the file args to fts at one shot
		 * as we need to keep a handle on which file arg generates what
		 * files (the -n and -d flags need this). If the open is
		 * successful, return a 0.
		 */
		if ((ftsp = fts_open(farray, ftsopts, NULL)) != NULL)
			break;
	}
	return(0);
}