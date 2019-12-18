#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; TYPE_1__* pat; } ;
struct TYPE_6__ {int flgs; size_t plen; struct TYPE_6__* fow; int /*<<< orphan*/  pend; int /*<<< orphan*/  pstr; } ;
typedef  TYPE_1__ PATTERN ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int DIR_MTCH ; 
 scalar_t__ cflag ; 
 scalar_t__ fn_match (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nflag ; 
 scalar_t__ pat_sel (TYPE_2__*) ; 
 TYPE_1__* pathead ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,size_t) ; 

int
pat_match(ARCHD *arcn)
{
	PATTERN *pt;

	arcn->pat = NULL;

	/*
	 * if there are no more patterns and we have -n (and not -c) we are
	 * done. otherwise with no patterns to match, matches all
	 */
	if (pathead == NULL) {
		if (nflag && !cflag)
			return(-1);
		return(0);
	}

	/*
	 * have to search down the list one at a time looking for a match.
	 */
	pt = pathead;
	while (pt != NULL) {
		/*
		 * check for a file name match unless we have DIR_MTCH set in
		 * this pattern then we want a prefix match
		 */
		if (pt->flgs & DIR_MTCH) {
			/*
			 * this pattern was matched before to a directory
			 * as we must have -n set for this (but not -d). We can
			 * only match CHILDREN of that directory so we must use
			 * an exact prefix match (no wildcards).
			 */
			if ((arcn->name[pt->plen] == '/') &&
			    (strncmp(pt->pstr, arcn->name, pt->plen) == 0))
				break;
		} else if (fn_match(pt->pstr, arcn->name, &pt->pend) == 0)
			break;
		pt = pt->fow;
	}

	/*
	 * return the result, remember that cflag (-c) inverts the sense of a
	 * match
	 */
	if (pt == NULL)
		return(cflag ? 0 : 1);

	/*
	 * We had a match, now when we invert the sense (-c) we reject this
	 * member. However we have to tag the pattern a being successful, (in a
	 * match, not in selecting an archive member) so we call pat_sel() here.
	 */
	arcn->pat = pt;
	if (!cflag)
		return(0);

	if (pat_sel(arcn) < 0)
		return(-1);
	arcn->pat = NULL;
	return(1);
}