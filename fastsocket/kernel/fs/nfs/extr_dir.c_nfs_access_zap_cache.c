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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  access_cache_inode_lru; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_ACL_LRU_SET ; 
 int /*<<< orphan*/  __nfs_access_zap_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_access_free_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_access_lru_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_access_zap_cache(struct inode *inode)
{
	LIST_HEAD(head);

	if (test_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags) == 0)
		return;
	/* Remove from global LRU init */
	spin_lock(&nfs_access_lru_lock);
	if (test_and_clear_bit(NFS_INO_ACL_LRU_SET, &NFS_I(inode)->flags))
		list_del_init(&NFS_I(inode)->access_cache_inode_lru);

	spin_lock(&inode->i_lock);
	__nfs_access_zap_cache(NFS_I(inode), &head);
	spin_unlock(&inode->i_lock);
	spin_unlock(&nfs_access_lru_lock);
	nfs_access_free_list(&head);
}