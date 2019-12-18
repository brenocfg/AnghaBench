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
typedef  void* time_t ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {scalar_t__ ino; scalar_t__ dev; struct TYPE_4__* fow; void* atime; void* mtime; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ ATDIR ;

/* Variables and functions */
 unsigned int A_TAB_SZ ; 
 TYPE_1__** atab ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

void
add_atdir(char *fname, dev_t dev, ino_t ino, time_t mtime, time_t atime)
{
	ATDIR *pt;
	u_int indx;

	if (atab == NULL)
		return;

	/*
	 * make sure this directory is not already in the table, if so just
	 * return (the older entry always has the correct time). The only
	 * way this will happen is when the same subtree can be traversed by
	 * different args to pax and the -n option is aborting fts out of a
	 * subtree before all the post-order visits have been made).
	 */
	indx = ((unsigned)ino) % A_TAB_SZ;
	if ((pt = atab[indx]) != NULL) {
		while (pt != NULL) {
			if ((pt->ino == ino) && (pt->dev == dev))
				break;
			pt = pt->fow;
		}

		/*
		 * oops, already there. Leave it alone.
		 */
		if (pt != NULL)
			return;
	}

	/*
	 * add it to the front of the hash chain
	 */
	if ((pt = (ATDIR *)malloc(sizeof(ATDIR))) != NULL) {
		if ((pt->name = strdup(fname)) != NULL) {
			pt->dev = dev;
			pt->ino = ino;
			pt->mtime = mtime;
			pt->atime = atime;
			pt->fow = atab[indx];
			atab[indx] = pt;
			return;
		}
		free(pt);
	}

	paxwarn(1, "Directory access time reset table ran out of memory");
	return;
}