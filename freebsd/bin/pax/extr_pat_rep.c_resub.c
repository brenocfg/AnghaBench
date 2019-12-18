#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rm_so; scalar_t__ rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_6__ {int re_nsub; } ;
typedef  TYPE_2__ regex_t ;

/* Variables and functions */
 int l_strncpy (char*,char*,int) ; 

__attribute__((used)) static int
resub(regex_t *rp, regmatch_t *pm, char *orig, char *src, char *dest,
	char *destend)
{
	char *spt;
	char *dpt;
	char c;
	regmatch_t *pmpt;
	int len;
	int subexcnt;

	spt =  src;
	dpt = dest;
	subexcnt = rp->re_nsub;
	while ((dpt < destend) && ((c = *spt++) != '\0')) {
		/*
		 * see if we just have an ordinary replacement character
		 * or we refer to a subexpression.
		 */
		if (c == '&') {
			pmpt = pm;
		} else if ((c == '\\') && (*spt >= '0') && (*spt <= '9')) {
			/*
			 * make sure there is a subexpression as specified
			 */
			if ((len = *spt++ - '0') > subexcnt)
				return(-1);
			pmpt = pm + len;
		} else {
 			/*
			 * Ordinary character, just copy it
			 */
 			if ((c == '\\') && ((*spt == '\\') || (*spt == '&')))
 				c = *spt++;
 			*dpt++ = c;
			continue;
		}

		/*
		 * continue if the subexpression is bogus
		 */
		if ((pmpt->rm_so < 0) || (pmpt->rm_eo < 0) ||
		    ((len = pmpt->rm_eo - pmpt->rm_so) <= 0))
			continue;

		/*
		 * copy the subexpression to the destination.
		 * fail if we run out of space or the match string is damaged
		 */
		if (len > (destend - dpt))
			len = destend - dpt;
		if (l_strncpy(dpt, orig + pmpt->rm_so, len) != len)
			return(-1);
		dpt += len;
	}
	return(dpt - dest);
}