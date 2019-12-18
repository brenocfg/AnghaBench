#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nfs_renamedata {int /*<<< orphan*/  cred; TYPE_1__* new_dir; TYPE_1__* old_dir; TYPE_2__* new_dentry; TYPE_2__* old_dentry; } ;
struct TYPE_4__ {scalar_t__ d_inode; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (TYPE_2__*) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct nfs_renamedata*) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (scalar_t__) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_async_rename_release(void *calldata)
{
	struct nfs_renamedata	*data = calldata;
	struct super_block *sb = data->old_dir->i_sb;

	if (data->old_dentry->d_inode)
		nfs_mark_for_revalidate(data->old_dentry->d_inode);

	dput(data->old_dentry);
	dput(data->new_dentry);
	iput(data->old_dir);
	iput(data->new_dir);
	nfs_sb_deactive(sb);
	put_rpccred(data->cred);
	kfree(data);
}