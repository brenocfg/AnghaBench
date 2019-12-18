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
struct TYPE_7__ {scalar_t__ type; TYPE_1__* pat; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int flgs; char* pend; char* pstr; int plen; struct TYPE_6__* fow; } ;
typedef  TYPE_1__ PATTERN ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int DIR_MTCH ; 
 int MTCH ; 
 scalar_t__ PAX_DIR ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  nflag ; 
 TYPE_1__* pathead ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int
pat_sel(ARCHD *arcn)
{
	PATTERN *pt;
	PATTERN **ppt;
	int len;

	/*
	 * if no patterns just return
	 */
	if ((pathead == NULL) || ((pt = arcn->pat) == NULL))
		return(0);

	/*
	 * when we are NOT limited to a single match per pattern mark the
	 * pattern and return
	 */
	if (!nflag) {
		pt->flgs |= MTCH;
		return(0);
	}

	/*
	 * we reach this point only when we allow a single selected match per
	 * pattern, if the pattern matches a directory and we do not have -d
	 * (dflag) we are done with this pattern. We may also be handed a file
	 * in the subtree of a directory. in that case when we are operating
	 * with -d, this pattern was already selected and we are done
	 */
	if (pt->flgs & DIR_MTCH)
		return(0);

	if (!dflag && ((pt->pend != NULL) || (arcn->type == PAX_DIR))) {
		/*
		 * ok we matched a directory and we are allowing
		 * subtree matches but because of the -n only its children will
		 * match. This is tagged as a DIR_MTCH type.
		 * WATCH IT, the code assumes that pt->pend points
		 * into arcn->name and arcn->name has not been modified.
		 * If not we will have a big mess. Yup this is another kludge
		 */

		/*
		 * if this was a prefix match, remove trailing part of path
		 * so we can copy it. Future matches will be exact prefix match
		 */
		if (pt->pend != NULL)
			*pt->pend = '\0';

		if ((pt->pstr = strdup(arcn->name)) == NULL) {
			paxwarn(1, "Pattern select out of memory");
			if (pt->pend != NULL)
				*pt->pend = '/';
			pt->pend = NULL;
			return(-1);
		}

		/*
		 * put the trailing / back in the source string
		 */
		if (pt->pend != NULL) {
			*pt->pend = '/';
			pt->pend = NULL;
		}
		pt->plen = strlen(pt->pstr);

		/*
		 * strip off any trailing /, this should really never happen
		 */
		len = pt->plen - 1;
		if (*(pt->pstr + len) == '/') {
			*(pt->pstr + len) = '\0';
			pt->plen = len;
		}
		pt->flgs = DIR_MTCH | MTCH;
		arcn->pat = pt;
		return(0);
	}

	/*
	 * we are then done with this pattern, so we delete it from the list
	 * because it can never be used for another match.
	 * Seems kind of strange to do for a -c, but the pax spec is really
	 * vague on the interaction of -c -n and -d. We assume that when -c
	 * and the pattern rejects a member (i.e. it matched it) it is done.
	 * In effect we place the order of the flags as having -c last.
	 */
	pt = pathead;
	ppt = &pathead;
	while ((pt != NULL) && (pt != arcn->pat)) {
		ppt = &(pt->fow);
		pt = pt->fow;
	}

	if (pt == NULL) {
		/*
		 * should never happen....
		 */
		paxwarn(1, "Pattern list inconsistent");
		return(-1);
	}
	*ppt = pt->fow;
	free(pt);
	arcn->pat = NULL;
	return(0);
}