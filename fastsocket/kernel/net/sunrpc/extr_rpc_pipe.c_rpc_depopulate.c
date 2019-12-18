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
struct rpc_filelist {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  __rpc_depopulate (struct dentry*,struct rpc_filelist const*,int,int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpc_depopulate(struct dentry *parent,
			   const struct rpc_filelist *files,
			   int start, int eof)
{
	struct inode *dir = parent->d_inode;

	mutex_lock_nested(&dir->i_mutex, I_MUTEX_CHILD);
	__rpc_depopulate(parent, files, start, eof);
	mutex_unlock(&dir->i_mutex);
}