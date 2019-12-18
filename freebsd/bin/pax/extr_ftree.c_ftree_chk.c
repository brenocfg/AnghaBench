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
struct TYPE_3__ {scalar_t__ refcnt; char* fname; scalar_t__ chflg; struct TYPE_3__* fow; } ;
typedef  TYPE_1__ FTREE ;

/* Variables and functions */
 int /*<<< orphan*/  atdir_end () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* fthead ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tflag ; 

void
ftree_chk(void)
{
	FTREE *ft;
	int wban = 0;

	/*
	 * make sure all dir access times were reset.
	 */
	if (tflag)
		atdir_end();

	/*
	 * walk down list and check reference count. Print out those members
	 * that never had a match
	 */
	for (ft = fthead; ft != NULL; ft = ft->fow) {
		if ((ft->refcnt > 0) || ft->chflg)
			continue;
		if (wban == 0) {
			paxwarn(1,"WARNING! These file names were not selected:");
			++wban;
		}
		(void)fprintf(stderr, "%s\n", ft->fname);
	}
}