#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_9__ {int st_nlink; scalar_t__ st_ino; scalar_t__ st_dev; } ;
struct TYPE_11__ {scalar_t__ type; size_t ln_nlen; char* ln_name; TYPE_1__ sb; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {scalar_t__ ino; scalar_t__ dev; int nlink; struct TYPE_10__* fow; struct TYPE_10__* name; } ;
typedef  TYPE_2__ HRDLNK ;
typedef  TYPE_3__ ARCHD ;

/* Variables and functions */
 unsigned int L_TAB_SZ ; 
 scalar_t__ PAX_DIR ; 
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ PAX_REG ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 size_t l_strncpy (char*,TYPE_2__*,int) ; 
 TYPE_2__** ltab ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 TYPE_2__* strdup (int /*<<< orphan*/ ) ; 

int
chk_lnk(ARCHD *arcn)
{
	HRDLNK *pt;
	HRDLNK **ppt;
	u_int indx;

	if (ltab == NULL)
		return(-1);
	/*
	 * ignore those nodes that cannot have hard links
	 */
	if ((arcn->type == PAX_DIR) || (arcn->sb.st_nlink <= 1))
		return(0);

	/*
	 * hash inode number and look for this file
	 */
	indx = ((unsigned)arcn->sb.st_ino) % L_TAB_SZ;
	if ((pt = ltab[indx]) != NULL) {
		/*
		 * it's hash chain in not empty, walk down looking for it
		 */
		ppt = &(ltab[indx]);
		while (pt != NULL) {
			if ((pt->ino == arcn->sb.st_ino) &&
			    (pt->dev == arcn->sb.st_dev))
				break;
			ppt = &(pt->fow);
			pt = pt->fow;
		}

		if (pt != NULL) {
			/*
			 * found a link. set the node type and copy in the
			 * name of the file it is to link to. we need to
			 * handle hardlinks to regular files differently than
			 * other links.
			 */
			arcn->ln_nlen = l_strncpy(arcn->ln_name, pt->name,
				sizeof(arcn->ln_name) - 1);
			arcn->ln_name[arcn->ln_nlen] = '\0';
			if (arcn->type == PAX_REG)
				arcn->type = PAX_HRG;
			else
				arcn->type = PAX_HLK;

			/*
			 * if we have found all the links to this file, remove
			 * it from the database
			 */
			if (--pt->nlink <= 1) {
				*ppt = pt->fow;
				free(pt->name);
				free(pt);
			}
			return(1);
		}
	}

	/*
	 * we never saw this file before. It has links so we add it to the
	 * front of this hash chain
	 */
	if ((pt = (HRDLNK *)malloc(sizeof(HRDLNK))) != NULL) {
		if ((pt->name = strdup(arcn->name)) != NULL) {
			pt->dev = arcn->sb.st_dev;
			pt->ino = arcn->sb.st_ino;
			pt->nlink = arcn->sb.st_nlink;
			pt->fow = ltab[indx];
			ltab[indx] = pt;
			return(0);
		}
		free(pt);
	}

	paxwarn(1, "Hard link table out of memory");
	return(-1);
}