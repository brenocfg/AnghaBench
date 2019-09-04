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

/* Variables and functions */
 int /*<<< orphan*/  M_NFSNODE ; 
 int /*<<< orphan*/  desiredvnodes ; 
 scalar_t__ hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_hash_mutex ; 
 int /*<<< orphan*/  nfsnodehash ; 
 scalar_t__ nfsnodehashtbl ; 

void
nfs_nhinit_finish(void)
{
	lck_mtx_lock(nfs_node_hash_mutex);
	if (!nfsnodehashtbl)
		nfsnodehashtbl = hashinit(desiredvnodes, M_NFSNODE, &nfsnodehash);
	lck_mtx_unlock(nfs_node_hash_mutex);
}