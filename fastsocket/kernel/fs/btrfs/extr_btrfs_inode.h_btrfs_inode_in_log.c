#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_root {scalar_t__ last_log_commit; int /*<<< orphan*/  log_mutex; } ;
struct TYPE_2__ {scalar_t__ logged_trans; scalar_t__ last_sub_trans; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int btrfs_inode_in_log(struct inode *inode, u64 generation)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret = 0;

	mutex_lock(&root->log_mutex);
	if (BTRFS_I(inode)->logged_trans == generation &&
	    BTRFS_I(inode)->last_sub_trans <= root->last_log_commit)
		ret = 1;
	mutex_unlock(&root->log_mutex);
	return ret;
}