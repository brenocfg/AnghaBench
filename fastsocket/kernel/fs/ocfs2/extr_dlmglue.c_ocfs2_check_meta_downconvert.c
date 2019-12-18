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
struct ocfs2_lock_res {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int ocfs2_ci_checkpointed (int /*<<< orphan*/ ,struct ocfs2_lock_res*,int) ; 
 struct inode* ocfs2_lock_res_inode (struct ocfs2_lock_res*) ; 

__attribute__((used)) static int ocfs2_check_meta_downconvert(struct ocfs2_lock_res *lockres,
					int new_level)
{
	struct inode *inode = ocfs2_lock_res_inode(lockres);

	return ocfs2_ci_checkpointed(INODE_CACHE(inode), lockres, new_level);
}