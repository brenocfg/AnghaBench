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
struct TYPE_3__ {int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  name; struct TYPE_3__* fow; } ;
typedef  TYPE_1__ ATDIR ;

/* Variables and functions */
 int A_TAB_SZ ; 
 TYPE_1__** atab ; 
 int /*<<< orphan*/  set_ftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
atdir_end(void)
{
	ATDIR *pt;
	int i;

	if (atab == NULL)
		return;
	/*
	 * for each non-empty hash table entry reset all the directories
	 * chained there.
	 */
	for (i = 0; i < A_TAB_SZ; ++i) {
		if ((pt = atab[i]) == NULL)
			continue;
		/*
		 * remember to force the times, set_ftime() looks at pmtime
		 * and patime, which only applies to things CREATED by pax,
		 * not read by pax. Read time reset is controlled by -t.
		 */
		for (; pt != NULL; pt = pt->fow)
			set_ftime(pt->name, pt->mtime, pt->atime, 1);
	}
}