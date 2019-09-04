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
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_node_clear_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_sort4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

void
nfs_node_clear_busy4(nfsnode_t np1, nfsnode_t np2, nfsnode_t np3, nfsnode_t np4)
{
	nfsnode_t list[4];
	int lcnt;

	nfs_node_sort4(np1, np2, np3, np4, list, &lcnt);
	while (--lcnt >= 0)
		nfs_node_clear_busy(list[lcnt]);
}