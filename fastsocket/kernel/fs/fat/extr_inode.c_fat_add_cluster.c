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
struct inode {int dummy; } ;

/* Variables and functions */
 int fat_alloc_clusters (struct inode*,int*,int) ; 
 int fat_chain_add (struct inode*,int,int) ; 
 int /*<<< orphan*/  fat_free_clusters (struct inode*,int) ; 

__attribute__((used)) static int fat_add_cluster(struct inode *inode)
{
	int err, cluster;

	err = fat_alloc_clusters(inode, &cluster, 1);
	if (err)
		return err;
	/* FIXME: this cluster should be added after data of this
	 * cluster is writed */
	err = fat_chain_add(inode, cluster, 1);
	if (err)
		fat_free_clusters(inode, cluster);
	return err;
}