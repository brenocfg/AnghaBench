#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; } ;
struct TYPE_8__ {TYPE_1__ sb; } ;
struct TYPE_7__ {int flgs; struct TYPE_7__* fow; int /*<<< orphan*/  high_time; int /*<<< orphan*/  low_time; } ;
typedef  TYPE_2__ TIME_RNG ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
#define  CMPBOTH 130 
#define  CMPCTME 129 
#define  CMPMTME 128 
 int HASHIGH ; 
 int HASLOW ; 
 TYPE_2__* trhead ; 

__attribute__((used)) static int
trng_match(ARCHD *arcn)
{
	TIME_RNG *pt;

	/*
	 * have to search down the list one at a time looking for a match.
	 * remember time range limits are inclusive.
	 */
	pt = trhead;
	while (pt != NULL) {
		switch(pt->flgs & CMPBOTH) {
		case CMPBOTH:
			/*
			 * user wants both mtime and ctime checked for this
			 * time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_mtime < pt->low_time) &&
			    (arcn->sb.st_ctime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_mtime > pt->high_time) &&
			    (arcn->sb.st_ctime > pt->high_time))) {
				pt = pt->fow;
				continue;
			}
			break;
		case CMPCTME:
			/*
			 * user wants only ctime checked for this time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_ctime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_ctime > pt->high_time))) {
				pt = pt->fow;
				continue;
			}
			break;
		case CMPMTME:
		default:
			/*
			 * user wants only mtime checked for this time range
			 */
			if (((pt->flgs & HASLOW) &&
			    (arcn->sb.st_mtime < pt->low_time)) ||
			    ((pt->flgs & HASHIGH) &&
			    (arcn->sb.st_mtime > pt->high_time))) {
				pt = pt->fow;
				continue;
			}
			break;
		}
		break;
	}

	if (pt == NULL)
		return(1);
	return(0);
}