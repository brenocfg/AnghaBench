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
 int xfs_attr_leaf_entsize_local (int,int) ; 
 int xfs_attr_leaf_entsize_local_max (int) ; 
 int xfs_attr_leaf_entsize_remote (int) ; 

int
xfs_attr_leaf_newentsize(int namelen, int valuelen, int blocksize, int *local)
{
	int size;

	size = xfs_attr_leaf_entsize_local(namelen, valuelen);
	if (size < xfs_attr_leaf_entsize_local_max(blocksize)) {
		if (local) {
			*local = 1;
		}
	} else {
		size = xfs_attr_leaf_entsize_remote(namelen);
		if (local) {
			*local = 0;
		}
	}
	return(size);
}