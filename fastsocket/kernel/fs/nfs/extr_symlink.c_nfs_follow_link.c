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
typedef  void page ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_mapping; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  filler_t ;

/* Variables and functions */
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 void* kmap (void*) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,void*) ; 
 int /*<<< orphan*/  nfs_revalidate_mapping (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_symlink_filler ; 
 void* read_cache_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inode*) ; 

__attribute__((used)) static void *nfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct inode *inode = dentry->d_inode;
	struct page *page;
	void *err;

	err = ERR_PTR(nfs_revalidate_mapping(inode, inode->i_mapping));
	if (err)
		goto read_failed;
	page = read_cache_page(&inode->i_data, 0,
				(filler_t *)nfs_symlink_filler, inode);
	if (IS_ERR(page)) {
		err = page;
		goto read_failed;
	}
	nd_set_link(nd, kmap(page));
	return page;

read_failed:
	nd_set_link(nd, err);
	return NULL;
}