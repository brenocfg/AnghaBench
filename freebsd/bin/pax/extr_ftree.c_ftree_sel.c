#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int refcnt; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_SKIP ; 
 scalar_t__ PAX_DIR ; 
 int /*<<< orphan*/  dflag ; 
 TYPE_3__* ftcur ; 
 int /*<<< orphan*/ * ftent ; 
 int ftree_skip ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftsp ; 
 scalar_t__ nflag ; 

void
ftree_sel(ARCHD *arcn)
{
	/*
	 * set reference bit for this pattern. This linked list is only used
	 * when file trees are supplied pax as args. The list is not used when
	 * the trees are read from stdin.
	 */
	if (ftcur != NULL)
		ftcur->refcnt = 1;

	/*
	 * if -n we are done with this arg, force a skip to the next arg when
	 * pax asks for the next file in next_file().
	 * if -d we tell fts only to match the directory (if the arg is a dir)
	 * and not the entire file tree rooted at that point.
	 */
	if (nflag)
		ftree_skip = 1;

	if (!dflag || (arcn->type != PAX_DIR))
		return;

	if (ftent != NULL)
		(void)fts_set(ftsp, ftent, FTS_SKIP);
}