#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_7__ {int st_nlink; scalar_t__ st_ino; scalar_t__ st_dev; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ sb; } ;
struct TYPE_8__ {scalar_t__ ino; scalar_t__ dev; struct TYPE_8__* name; struct TYPE_8__* fow; } ;
typedef  TYPE_2__ HRDLNK ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 unsigned int L_TAB_SZ ; 
 scalar_t__ PAX_DIR ; 
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__** ltab ; 

void
purg_lnk(ARCHD *arcn)
{
	HRDLNK *pt;
	HRDLNK **ppt;
	u_int indx;

	if (ltab == NULL)
		return;
	/*
	 * do not bother to look if it could not be in the database
	 */
	if ((arcn->sb.st_nlink <= 1) || (arcn->type == PAX_DIR) ||
	    (arcn->type == PAX_HLK) || (arcn->type == PAX_HRG))
		return;

	/*
	 * find the hash chain for this inode value, if empty return
	 */
	indx = ((unsigned)arcn->sb.st_ino) % L_TAB_SZ;
	if ((pt = ltab[indx]) == NULL)
		return;

	/*
	 * walk down the list looking for the inode/dev pair, unlink and
	 * free if found
	 */
	ppt = &(ltab[indx]);
	while (pt != NULL) {
		if ((pt->ino == arcn->sb.st_ino) &&
		    (pt->dev == arcn->sb.st_dev))
			break;
		ppt = &(pt->fow);
		pt = pt->fow;
	}
	if (pt == NULL)
		return;

	/*
	 * remove and free it
	 */
	*ppt = pt->fow;
	free(pt->name);
	free(pt);
}