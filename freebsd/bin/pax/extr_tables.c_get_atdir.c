#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  time_t ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {scalar_t__ ino; scalar_t__ dev; struct TYPE_4__* name; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime; struct TYPE_4__* fow; } ;
typedef  TYPE_1__ ATDIR ;

/* Variables and functions */
 unsigned int A_TAB_SZ ; 
 TYPE_1__** atab ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
get_atdir(dev_t dev, ino_t ino, time_t *mtime, time_t *atime)
{
	ATDIR *pt;
	ATDIR **ppt;
	u_int indx;

	if (atab == NULL)
		return(-1);
	/*
	 * hash by inode and search the chain for an inode and device match
	 */
	indx = ((unsigned)ino) % A_TAB_SZ;
	if ((pt = atab[indx]) == NULL)
		return(-1);

	ppt = &(atab[indx]);
	while (pt != NULL) {
		if ((pt->ino == ino) && (pt->dev == dev))
			break;
		/*
		 * no match, go to next one
		 */
		ppt = &(pt->fow);
		pt = pt->fow;
	}

	/*
	 * return if we did not find it.
	 */
	if (pt == NULL)
		return(-1);

	/*
	 * found it. return the times and remove the entry from the table.
	 */
	*ppt = pt->fow;
	*mtime = pt->mtime;
	*atime = pt->atime;
	free(pt->name);
	free(pt);
	return(0);
}