#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ nfsnode_t ;

/* Variables and functions */

__attribute__((used)) static void
nfs_node_sort4(nfsnode_t np1, nfsnode_t np2, nfsnode_t np3, nfsnode_t np4, nfsnode_t *list, int *lcntp)
{
	nfsnode_t na[2], nb[2];
	int a, b, i, lcnt;

	/* sort pairs then merge */
	na[0] = (np1 > np2) ? np1 : np2;
	na[1] = (np1 > np2) ? np2 : np1;
	nb[0] = (np3 > np4) ? np3 : np4;
	nb[1] = (np3 > np4) ? np4 : np3;
	for (a = b = i = lcnt = 0; i < 4; i++) {
		if (a >= 2)
			list[lcnt] = nb[b++];
		else if ((b >= 2) || (na[a] >= nb[b]))
			list[lcnt] = na[a++];
		else
			list[lcnt] = nb[b++];
		if ((lcnt <= 0) || (list[lcnt] != list[lcnt-1]))
			lcnt++; /* omit dups */
	}
	if (list[lcnt-1] == NULL)
		lcnt--;
	*lcntp = lcnt;
}