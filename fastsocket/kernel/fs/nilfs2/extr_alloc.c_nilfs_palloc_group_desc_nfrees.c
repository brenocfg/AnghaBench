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
struct nilfs_palloc_group_desc {int /*<<< orphan*/  pg_nfrees; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_bgl_lock (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
nilfs_palloc_group_desc_nfrees(struct inode *inode, unsigned long group,
			       const struct nilfs_palloc_group_desc *desc)
{
	unsigned long nfree;

	spin_lock(nilfs_mdt_bgl_lock(inode, group));
	nfree = le32_to_cpu(desc->pg_nfrees);
	spin_unlock(nilfs_mdt_bgl_lock(inode, group));
	return nfree;
}