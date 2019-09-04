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
typedef  scalar_t__ uid_t ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_3__ {scalar_t__* n_accessuid; int* n_access; } ;

/* Variables and functions */
 int NFS_ACCESS_CACHE_SIZE ; 

int
nfs_node_access_slot(nfsnode_t np, uid_t uid, int add)
{
	int slot;

	for (slot=0; slot < NFS_ACCESS_CACHE_SIZE; slot++)
		if (np->n_accessuid[slot] == uid)
			break;
	if (slot == NFS_ACCESS_CACHE_SIZE) {
		if (!add)
			return (-1);
		slot = np->n_access[NFS_ACCESS_CACHE_SIZE];
		np->n_access[NFS_ACCESS_CACHE_SIZE] = (slot + 1) % NFS_ACCESS_CACHE_SIZE;
	}
	return (slot);
}